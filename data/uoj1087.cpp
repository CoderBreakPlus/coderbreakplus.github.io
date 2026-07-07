// created time: 2026-07-06 14:24:55
#include"shuffle.h"
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

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int n,fa[1005],vis[1005];
int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]); return fa[x]; }
vector<int>cur;
vector<pair<int,int>>E[1005];

void add(int u,int v,int i){
	E[u].pb(v,i),E[v].pb(u,i);
}

int mxs[1005],sz[1005],rt,wh;

void findcent(int x,int fa){
	sz[x]=1,mxs[x]=0;
	for(auto [y,i]:E[x]){
		if(vis[y]||y==fa) continue;
		flip(i);
		findcent(y,x);sz[x]+=sz[y];
		chkmax(mxs[x],sz[y]);
	}
	chkmax(mxs[x],wh-sz[x]);
	if(mxs[x]<mxs[rt])rt=x;
}

int bel[1005],deg[1005],ff[1005],fi[1005];

int que[1005],tl;
void dfs(int x,int fa,int fid,int c){
	bel[x]=c,deg[x]=0;
	ff[x]=fa,fi[x]=fid;
	for(auto [y,w]:E[x]){
		if(y==fa||vis[y])continue;
		dfs(y,x,w,c);
		deg[x]++;
	}
	if(!deg[x]) que[++tl]=x;
}
void solve(int x){
	tl=0; bel[x]=x, vis[x]=1;

	for(auto [y,i]:E[x]){
		if(vis[y]) continue;
		dfs(y,x,i,y);
	}

	// cout<<"x="<<x<<endl;
	while(tl){
		// for(int i=1;i<=n;i++)cout<<cur[i-1]<<" "; cout<<endl;
		for(int i=1;i<=tl;i++){
			int u=que[i];
			if(bel[cur[u-1]]!=bel[u])continue;

			if(fi[u]) flip(fi[u]); // cut from root
			if(u==x||--deg[ff[u]]) swap(que[i],que[tl]),tl--;
			else que[i]=ff[u];

			i--;
		}
		if(tl) cur=shuffle(x);
	}
	// for(int i=1;i<=n;i++) cout<<cur[i-1]<<" "; cout<<endl;

	int cur=wh;
	for(auto [y,i]:E[x]){
		if(vis[y]) continue;
		if(sz[y]>sz[x]) wh=cur-sz[x];
		else wh=sz[y];

		// cout<<"y="<<y<<endl;
		rt=0,findcent(y,x); solve(rt);
	}
}
void solve(int n,int m,vector<pair<int,int>>e,vector<int>p){
	::n=n; cur=p;
	for(int i=1;i<=n;i++)fa[i]=i;
	for(int i=1;i<=m;i++){
		auto [u,v]=e[i-1];
		if(find(u)==find(v))continue;
		fa[find(u)]=find(v),add(u,v,i);
	}
	mxs[rt=0]=wh=n; findcent(1,0);
	// cout<<"rt="<<rt<<" mxs="<<mxs[rt]<<endl;
	solve(rt);
}