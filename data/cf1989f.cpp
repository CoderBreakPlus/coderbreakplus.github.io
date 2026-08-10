#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void addmod(T &x){ if(x >= mod) x -= mod; }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,m,q;
int fa[400005],sz[400005],u[200005],v[200005];

int find(int x){ if(x!=fa[x]) fa[x]=find(fa[x]); return fa[x]; }
ll W(int x){ if(x>1) return (ll)x*x; return 0;}
ll ans;

void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y) return;
	ans-=W(sz[x])+W(sz[y]);
	sz[x]+=sz[y],fa[y]=x;
	ans+=W(sz[x]);
}
int dfn[400005],low[400005],stk[400005],col[400005],vis[400005],tim,tp;

vector<int>G[400005];
void tarjan(int x){
	low[x]=dfn[x]=++tim,vis[x]=1;
	stk[++tp]=x;
	for(int y:G[x]){
		if(!dfn[y]){
			tarjan(y);
			low[x]=min(low[x],low[y]);
		}else if(vis[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		do{
			int u=stk[tp];
			col[u]=x, vis[u]=0;
		}while(stk[tp--]!=x);
	}
}
void solve(int l,int r,vector<tuple<int,int,int>>E){
	if(l==r){
		for(auto [t,u,v]: E) merge(u,v);
		if(r<=q) printf("%lld ",ans);
		return;
	}
	int mid=(l+r)>>1; tim=0;
	vector<tuple<int,int,int>>ls,rs;
	for(auto &[t,u,v]:E) 
		if(t<=mid) G[u=find(u)].pb(v=find(v));

	for(auto [t,u,v]:E)
		if(t<=mid){
			if(!dfn[u]) tarjan(u);
			if(col[u]==col[v]) ls.pb(t,u,v);
			else rs.pb(t,u,v);
		}else rs.pb(t,u,v);

	tim=0;
	for(auto [t,u,v]: E)
		if(t<=mid){
			dfn[u]=dfn[v]=0;
			G[u].clear(),G[v].clear();
		}
	solve(l,mid,ls);
	solve(mid+1,r,rs);
}
void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;

	vector<tuple<int,int,int>>E;
	for(int x=1;x<=q;x++){
		int i=read(),j=read()+n; 
		char s[5]; scanf("%s",s);
		if(s[0]=='R') E.pb(x,i,j);
		else E.pb(x,j,i);
	}
	solve(1,q+1,E);
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