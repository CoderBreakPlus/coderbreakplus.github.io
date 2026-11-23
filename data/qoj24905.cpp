// created time: 2026-11-23 08:30:33
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
const int M=1e8;
int n,w[200005],ff[200005],cnt,sz[200005],son[200005],val[200005],m;
vector<int>E[200005];

#define mid ((l+r)>>1)
struct Tree{
	int lc,rc,sz;
}t[M];
void pushup(int p){ t[p].sz=t[t[p].lc].sz+t[t[p].rc].sz; }
int merge(int x,int y,int l,int r){
	if(!x||!y) return x^y;
	int p=++cnt;
	if(l==r){
		t[p].sz=t[x].sz+t[y].sz;
	}else{
		t[p].lc=merge(t[x].lc,t[y].lc,l,mid);
		t[p].rc=merge(t[x].rc,t[y].rc,mid+1,r);
		pushup(p);
	}
	return p;
}
void update(int b,int &p,int l,int r,int x,int v){
	p=++cnt;
	t[p]=t[b],t[p].sz+=v;
	if(l==r)return;
	if(x<=mid)update(t[b].lc,t[p].lc,l,mid,x,v);
	else update(t[b].rc,t[p].rc,mid+1,r,x,v);
}
int query(int p,int l,int r){
	if(l==r)return l;
	if(t[t[p].rc].sz)return query(t[p].rc,mid+1,r);
	else return query(t[p].lc,l,mid);
}
int query(int p,int p2,int l,int r){
	if(l==r)return l;
	if(t[t[p].rc].sz>t[t[p2].rc].sz)return query(t[p].rc,t[p2].rc,mid+1,r);
	else return query(t[p].lc,t[p2].lc,l,mid);
}
struct Info{
	int rt,rt2,op;
	ll ans,ans2;
	void push(const Info &B){
		ans+=B.ans2;
		rt=merge(rt,B.rt2,0,m);
	}
	void resolve(int x){
		ans2=ans;
		if(!w[x]){
			op=query(rt,0,m);
			if(op){
				ans2+=val[op];
				update(rt,rt2,0,m,op,-1);
			}else
				rt2=rt;
		}else{
			update(rt,rt2,0,m,w[x],1);
		}
	}
}f[200005],g[200005];
void dfs(int x,int fa){
	for(int y:E[x])if(y!=fa){
		dfs(y,x);
		f[x].push(f[y]);
	}
	f[x].resolve(x);
}
void inv_edge(int x,int y){
	g[y]=g[x];
	if(!w[y]){
		g[y].ans-=val[f[y].op];
		update(g[y].rt,g[y].rt,0,m,f[y].op,1);
	}else{
		update(g[y].rt,g[y].rt,0,m,w[y],-1);
	}
	if(!w[x]){	
		int op=query(g[x].rt,f[y].rt2,0,m);
		if(op){
			g[y].ans+=val[op];
			update(g[y].rt,g[y].rt,0,m,op,-1);
		}
	}else{
		update(g[y].rt,g[y].rt,0,m,w[x],1);
	}
	g[y].resolve(y);
}
void dfs2(int x,int fa){
	for(int y:E[x])if(y!=fa){
		inv_edge(x,y);
		dfs2(y,x);
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		w[i]=read();
		if(w[i])val[++m]=w[i];
	}
	sort(val+1,val+m+1);
	for(int i=1;i<=n;i++){
		if(w[i])
		w[i]=lower_bound(val+1,val+m+1,w[i])-val;
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}	
	dfs(1,0);
	g[1]=f[1];
	dfs2(1,0);
	for(int i=1;i<=n;i++)
		printf("%lld ",g[i].ans2);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}