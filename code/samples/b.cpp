// created time: 2026-11-07 08:33:44
#include<bits/stdc++.h>
#include"tree.h"
#ifdef LOCAL
#include"grader.cpp"
#endif

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

vector<int>E[1000005];
int dep[1000005],sz[1000005],mxs[1000005],wh;

void findcent(int x,int fa){
	sz[x]=1,mxs[x]=0;
	for(int y:E[x])if(y!=fa){
		findcent(y,x);
		sz[x]+=sz[y];chkmax(mxs[x],sz[y]);
	}
	chkmax(mxs[x],wh-sz[x]);
}
const int B=19;
int dfn[1000005],out[1000005],seq[1000005],tim;
ll ans[1000005];

void dfs(int x,int fa){
	seq[++tim]=x; dfn[x]=tim;
	for(int y:E[x])if(y!=fa&&!vis[y]){
		dep[y]=dep[x]+1;
		dfs(y,x);
	}
	out[x]=tim;
}
int buc[1<<B];

void count(int l,int r,int out){
	for(int k=B;k>=1;k--){
		for(int i=l;i<=r;i++)buc[dep[seq[i]]&((1<<k)-1)]++;
		for(int i=l;i<=r;i++)ans[seq[i]]+=buc[(-dep[seq[i]])&((1<<k)-1)];
		for(int i=l;i<=r;i++)buc[dep[seq[i]]&((1<<k)-1)]--;
	}
}
void solve(int x){
	vis[x]=1,dep[x]=tim=0;
	dfs(x,0);
	count(dfn[x],out[x],1);
	count(dfn[x],dfn[x],-1);
	for(int y:E[x])if(!vis[y])
		count(dfn[y],out[y],-1);
	int cur=wh;
	for(int y:E[x])if(!vis[y]){
		if(sz[y]<cur)wh=sz[y]; else wh=cur-sz[x];
		rt=0,findcent(y,x);
		solve(rt);
	}
}
int choose_vertex(int cid,int n,const vector<int>&u,const vector<int>&v){
	for(int i=1;i<=n;i++)E[i].clear(),ans[i]=0;
	for(int i=0;i<n-1;i++)
		E[u[i]].pb(v[i]),E[v[i]].pb(u[i]);
	mxs[0]=n,rt=0,findcent(1,0);
	solve(rt);
	int ret=1;
	for(int i=2;i<=n;i++)if(ans[i]<ans[ret])ret=i;
	return ret;
}