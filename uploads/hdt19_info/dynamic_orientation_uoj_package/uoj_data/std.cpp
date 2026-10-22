#include "path.h"
#include <bits/stdc++.h>
using namespace std;

namespace Orientation{
const int N=200005,mod=998244353;
struct Node{
	int l=0,r=0,fa=0,sz=0,p=0,first=0,last=0,sum=0,h=0;
	unsigned pri=0;
	bool rev=false;
}t[N];
int ver[N*2],mate[N*2],unmatched[N],pw[N],tot,answer;
map<pair<int,int>,int> edge_id;
mt19937 rng;

// 边 i 的两个半边是 2i、2i+1，前者在较小端点。
// p 表示这条边的出发半边，mate 表示同一顶点处的半边配对。
void pull(int x){
	int l=t[x].l,r=t[x].r;
	t[x].sz=t[l].sz+t[r].sz+1;
	t[x].first=l?t[l].first:t[x].p;
	t[x].last=r?t[r].last:(t[x].p^1);
	t[x].sum=((long long)t[l].sum+t[r].sum+pw[x])%mod;
	t[x].h=((long long)t[l].h+t[r].h+((t[x].p&1)?0:pw[x]))%mod;
	if(l)t[l].fa=x;
	if(r)t[r].fa=x;
}
// 只修改结点信息；下传懒标记时不能再次修改全局答案。
void reverse(int x){
	if(!x)return;
	swap(t[x].l,t[x].r);swap(t[x].first,t[x].last);
	t[x].p^=1;t[x].rev^=1;
	t[x].h=(t[x].sum-t[x].h+mod)%mod;
}
void push(int x){
	if(t[x].rev){reverse(t[x].l);reverse(t[x].r);t[x].rev=false;}
}
// 真正反向一整条路径，更新全局哈希。
void flip(int x){
	answer=(answer+(long long)t[x].sum-2LL*t[x].h+2LL*mod)%mod;
	reverse(x);
}
int merge(int x,int y){
	if(!x||!y){int r=x+y;if(r)t[r].fa=0;return r;}
	if(t[x].pri<t[y].pri){
		push(x);t[x].r=merge(t[x].r,y);pull(x);t[x].fa=0;return x;
	}
	push(y);t[y].l=merge(x,t[y].l);pull(y);t[y].fa=0;return y;
}
void split(int x,int k,int &a,int &b){
	if(!x){a=b=0;return;}
	push(x);
	if(t[t[x].l].sz>=k){b=x;split(t[x].l,k,a,t[x].l);pull(b);}
	else{a=x;split(t[x].r,k-t[t[x].l].sz-1,t[x].r,b);pull(a);}
	if(a)t[a].fa=0;
	if(b)t[b].fa=0;
}
int getroot(int x){while(t[x].fa)x=t[x].fa;return x;}
void push_path(int x){if(t[x].fa)push_path(t[x].fa);push(x);}
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
void join(int p,int q){
	int x=getroot(p>>1),y=getroot(q>>1);
	mate[p]=q;mate[q]=p;
	if(x==y)return; // 同一条路径的两个端点配对，成为回路。
	if(t[x].last!=p)flip(x);
	if(t[y].first!=q)flip(y);
	merge(x,y);
}
void expose(int p){
	if(!p)return;
	int v=ver[p],q=unmatched[v];
	if(q){unmatched[v]=0;join(p,q);}
	else unmatched[v]=p;
}
void collect(int x,vector<int> &s){
	if(!x)return;
	push(x);collect(t[x].l,s);
	if(!(t[x].p&1))s.push_back(x);
	collect(t[x].r,s);
}
}

void init(int n,int q){
	using namespace Orientation;
	tot=answer=0;edge_id.clear();
	fill(t,t+q+1,Node());fill(ver,ver+2*q+2,0);
	fill(mate,mate+2*q+2,0);fill(unmatched,unmatched+n+1,0);
	pw[0]=1;
	for(int i=1;i<=q;i++)pw[i]=2LL*pw[i-1]%mod;
	rng.seed(chrono::steady_clock::now().time_since_epoch().count());
}
void add(int u,int v,int i){
	using namespace Orientation;
	tot=i;edge_id[{u,v}]=i;
	int p=2*i;ver[p]=u;ver[p+1]=v;
	t[i].p=p;t[i].pri=rng();pull(i);
	answer=(answer+pw[i])%mod;
	expose(p);expose(p+1);
}
void del(int u,int v){
	using namespace Orientation;
	auto it=edge_id.find({u,v});int x=it->second;edge_id.erase(it);
	int p=2*x,a=mate[p],b=mate[p+1],r=getroot(x),k=getrank(x),left,right;
	bool closed=mate[t[r].first]==t[r].last;
	split(r,k-1,left,right);split(right,1,x,right);
	// 回路 A,e,B 删边后变成 B,A；开放路径则成为 A 和 B。
	if(closed)merge(right,left);
	answer=(answer-t[x].h+mod)%mod;
	if(a)mate[a]=0;else unmatched[u]=0;
	if(b)mate[b]=0;else unmatched[v]=0;
	mate[p]=mate[p+1]=0;
	expose(a);expose(b);ver[p]=ver[p+1]=0;
}
int query(){return Orientation::answer;}
vector<int> query_path(){
	using namespace Orientation;
	vector<int>s;s.reserve(edge_id.size());
	for(int i=1;i<=tot;i++)if(ver[2*i]&&!t[i].fa)collect(i,s);
	return s;
}
