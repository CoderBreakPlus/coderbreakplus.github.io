#include"path.h"
#include<bits/stdc++.h>
using namespace std;

namespace Euler{
using ll=long long;
const int N=200005,mod=998244353,groups=3,levels=20;
mt19937 rng;

// 一条边 e 对应一个 Treap 结点，两个半边的编号为 2e、2e+1。
// ver[p] 是半边所在的顶点，mate[p] 是同一顶点处与它配对的半边。
// 沿着 p -> mate[p^1] 前进，就能走出维护的路径或回路。
// 每个点最多保留一个未配对半边 unmatched[v]，故查询时只剩回路。
// p 是当前边的出发半边，first、last 是整段路径两端的半边。
// h、rh 分别记录正向、反向行走时每条边起点的哈希。
struct Node{
	int l=0,r=0,fa=0,sz=0,p=0,first=0,last=0,h=0,rh=0;
	unsigned pri=0;
	bool rev=false;
};
struct Sketch{
	int a[groups][levels]={};
	void operator^=(const Sketch &b){
		for(int j=0;j<groups;j++)for(int i=0;i<levels;i++)a[j][i]^=b.a[j][i];
	}
};
Node t[N];
Sketch value[N],sum[N],vertex_sum[N];
int height[N*2][groups];
vector<int>adj[N];
int ver[N*2],mate[N*2],pos[N*2],unmatched[N],pw[N];
int roots[N],where[N],mark[N],nodes[N],recent[64];
map<pair<int,int>,int>edge_id;
int tot,stamp,root_count,recent_count;

pair<int,int>key(int u,int v){return {min(u,v),max(u,v)};}
int representative(int v){return adj[v].empty()?0:adj[v][0];}
int getroot(int x){while(t[x].fa)x=t[x].fa;return x;}

// 第 i 层以约 2^(-i) 的概率保留一个半边编号，三组各自采样。
// height 在半边创建时生成，此后重复异或同一个编号就能撤销它。
void toggle(Sketch &s,int p){
	for(int j=0;j<groups;j++)for(int i=0;i<=height[p][j];i++)s.a[j][i]^=p;
}
void pull_sum(int x){
	int l=t[x].l,r=t[x].r;
	for(int j=0;j<groups;j++)for(int i=0;i<levels;i++)
		sum[x].a[j][i]=sum[l].a[j][i]^sum[r].a[j][i]^value[x].a[j][i];
}
void pull(int x){
	int l=t[x].l,r=t[x].r;
	t[x].sz=t[l].sz+t[r].sz+1;
	t[x].first=l?t[l].first:t[x].p;
	t[x].last=r?t[r].last:(t[x].p^1);
	t[x].h=(t[l].h+(ll)ver[t[x].p]*pw[t[l].sz]+(ll)t[r].h*pw[t[l].sz+1])%mod;
	t[x].rh=(t[r].rh+(ll)ver[t[x].p^1]*pw[t[r].sz]+(ll)t[l].rh*pw[t[r].sz+1])%mod;
	pull_sum(x);
	if(l)t[l].fa=x;
	if(r)t[r].fa=x;
}
void reverse(int x){
	if(!x)return;
	swap(t[x].l,t[x].r);swap(t[x].first,t[x].last);swap(t[x].h,t[x].rh);
	t[x].p^=1;t[x].rev^=1;
}
void push(int x){
	if(t[x].rev){reverse(t[x].l);reverse(t[x].r);t[x].rev=false;}
}
int merge(int x,int y){
	if(!x||!y){int r=x+y;if(r)t[r].fa=0;return r;}
	if(t[x].pri<t[y].pri){
		push(x);t[x].r=merge(t[x].r,y);pull(x);t[x].fa=0;return x;
	}
	push(y);t[y].l=merge(x,t[y].l);pull(y);t[y].fa=0;return y;
}
// 常规 FHQ split：前 k 条边归 a，其余归 b。
void split(int x,int k,int &a,int &b){
	if(!x){a=b=0;return;}
	push(x);
	if(t[t[x].l].sz>=k){b=x;split(t[x].l,k,a,t[x].l);pull(b);}
	else{a=x;split(t[x].r,k-t[t[x].l].sz-1,t[x].r,b);pull(a);}
	if(a)t[a].fa=0;
	if(b)t[b].fa=0;
}
void push_path(int x){
	if(t[x].fa)push_path(t[x].fa);
	push(x);
}
int getrank(int x){
	push_path(x);
	int k=t[t[x].l].sz+1;
	while(t[x].fa){
		int f=t[x].fa;
		if(t[f].r==x)k+=t[t[f].l].sz+1;
		x=f;
	}
	return k;
}
// 采样异或与顺序无关，更新它时不必下传翻转标记。
void refresh(int x){for(;x;x=t[x].fa)pull_sum(x);}
void insert_root(int x){if(x){where[x]=root_count;roots[root_count++]=x;}}
void erase_root(int x){
	int i=where[x],y=roots[--root_count];roots[i]=y;where[y]=i;
}

// 两个裸露半边在同一顶点处接起来：不同路径合并，同一路径闭合。
void join(int p,int q){
	int x=getroot(p>>1),y=getroot(q>>1);
	mate[p]=q;mate[q]=p;
	if(x==y)return;
	erase_root(x);erase_root(y);
	if(t[x].last!=p)reverse(x);
	if(t[y].first!=q)reverse(y);
	insert_root(merge(x,y));
}
void expose(int p){
	if(!p)return;
	int v=ver[p],q=unmatched[v];
	if(q){unmatched[v]=0;join(p,q);}
	else unmatched[v]=p;
}

// 寻找公共顶点用的辅助图：每个半边 p 连接到该顶点的代表半边 h。
// 将编号 p 分别异或到 p、h 所属的边结点上，内部辅助边就会抵消。
// vertex_sum[v] 汇总 v 的全部半边，代表被删时可整体交给新代表。
void attach(int p){
	int v=ver[p],h=representative(v);
	if(!h)h=p;
	pos[p]=adj[v].size();adj[v].push_back(p);
	toggle(vertex_sum[v],p);toggle(value[p>>1],p);toggle(value[h>>1],p);
	refresh(h>>1);
}
void detach(int p){
	int v=ver[p],h=representative(v),last=adj[v].back();
	// 用末尾元素填补空位，O(1) 删除邻接表中的半边。
	adj[v][pos[p]]=last;pos[last]=pos[p];adj[v].pop_back();
	toggle(vertex_sum[v],p);
	if(h!=p){toggle(value[h>>1],p);refresh(h>>1);}
	else if((h=representative(v))){value[h>>1]^=vertex_sum[v];refresh(h>>1);}
}

// 将闭合回路反向、旋转，使其从半边 p 出发。
int rotate(int p){
	int x=p>>1,r=getroot(x),k=getrank(x),a,b;
	if(t[x].p!=p){reverse(r);k=t[r].sz-k+1;}
	split(r,k-1,a,b);
	return merge(b,a);
}
void splice(int p,int q){
	int a=mate[p],b=mate[q];
	erase_root(getroot(p>>1));erase_root(getroot(q>>1));
	int x=rotate(p),y=rotate(q);
	mate[p]=b;mate[b]=p;mate[q]=a;mate[a]=q;
	insert_root(merge(x,y));
}
bool crossing(int p,int r){
	if(p<2||p>2*tot+1||!ver[p])return false;
	int x=getroot(p>>1),y=getroot(representative(ver[p])>>1);
	return x!=y&&(x==r||y==r);
}
int remember(int p){
	recent[recent_count++%64]=p;return p;
}
int find_crossing(int r){
	for(int i=levels-1;i>=0;i--)for(int j=0;j<groups;j++){
		int p=sum[r].a[j][i];
		if(crossing(p,r))return p;
	}
	// 保留最近找到的连接，避免相同分割反复触发扫描。
	for(int i=max(0,recent_count-64);i<recent_count;i++){
		int p=recent[i%64];
		if(crossing(p,r))return p;
	}
	// 采样失败则精确扫描。随机性只影响时间，不影响答案正确性。
	++stamp;int cnt=1;nodes[0]=r;
	for(int i=0;i<cnt;i++){
		int x=nodes[i];mark[x]=stamp;
		if(t[x].l)nodes[cnt++]=t[x].l;
		if(t[x].r)nodes[cnt++]=t[x].r;
	}
	for(int i=0;i<cnt;i++)for(int p=nodes[i]*2;p<=nodes[i]*2+1;p++){
		int v=ver[p],h=representative(v);
		if(mark[h>>1]!=stamp)return remember(p);
		if(p==h)for(int q:adj[v])if(mark[q>>1]!=stamp)return remember(q);
	}
	assert(false);return 0;
}
}

void init(int n,int q){
	using namespace Euler;
	tot=stamp=root_count=recent_count=0;
	rng.seed(chrono::steady_clock::now().time_since_epoch().count());
	fill(t,t+q+1,Node());fill(value,value+q+1,Sketch());fill(sum,sum+q+1,Sketch());
	fill(ver,ver+2*q+2,0);fill(mate,mate+2*q+2,0);fill(mark,mark+q+1,0);
	for(int i=0;i<=n;i++){vertex_sum[i]=Sketch();unmatched[i]=0;adj[i].clear();}
	pw[0]=1;
	for(int i=1;i<=q+1;i++)pw[i]=(ll)pw[i-1]*100%mod;
	edge_id.clear();
}
void add(int u,int v){
	using namespace Euler;
	int x=++tot,p=x*2;edge_id[key(u,v)]=x;
	ver[p]=u;ver[p+1]=v;t[x].p=p;t[x].pri=rng();
	for(int s=p;s<=p+1;s++)for(int j=0;j<groups;j++){
		int h=0;
		while(h+1<levels&&!(rng()&1))h++;
		height[s][j]=h;
	}
	attach(p);attach(p+1);pull(x);insert_root(x);
	expose(p);expose(p+1);
}
void del(int u,int v){
	using namespace Euler;
	auto it=edge_id.find(key(u,v));int x=it->second;edge_id.erase(it);
	int p=x*2,a=mate[p],b=mate[p+1],r=getroot(x),k=getrank(x),left,right;
	bool closed=mate[t[r].first]==t[r].last;
	erase_root(r);
	split(r,k-1,left,right);split(right,1,x,right);
	// 闭合回路 A,e,B 删除 e 后成为 B,A；开放路径则拆成 A 和 B。
	if(closed)insert_root(merge(right,left));
	else{insert_root(left);insert_root(right);}
	if(a)mate[a]=0;else unmatched[ver[p]]=0;
	if(b)mate[b]=0;else unmatched[ver[p+1]]=0;
	mate[p]=mate[p+1]=0;
	detach(p);detach(p+1);
	expose(a);expose(b);ver[p]=ver[p+1]=0;
}
int query(){
	using namespace Euler;
	// 查询时所有点度数为偶数，所有路径都已闭合，只需拼接各个回路。
	while(root_count>1){
		int r=roots[root_count-1],s=roots[root_count-2];
		if(t[s].sz<t[r].sz)r=s;
		int p=find_crossing(r);splice(p,representative(ver[p]));
	}
	int r=roots[0];
	// h 只存每条边的起点，还需补上最后一个顶点。
	return (t[r].h+(ll)ver[t[r].last]*pw[t[r].sz])%mod;
}
vector<int> query_path(){
	using namespace Euler;
	int r=roots[0],p=t[r].first;
	vector<int>ans(t[r].sz+1);
	for(int &v:ans){v=ver[p];p=mate[p^1];}
	return ans;
}
