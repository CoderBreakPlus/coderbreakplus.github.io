// created time: 2026-05-20 15:01:38
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

int n,V,c[1055],w[1055],dfn[1055],fa[1055],vis[1055],seq[1055],son[1055],sz[1055],qz[1055],tim;
vector<int>E[1055];

ll f[1<<10][6005],g[1<<10][6005];
bitset<1<<10>bf,bg;

void dfs(int x,int fa){
	sz[x]=1; ::fa[x]=fa;
	son[x]=0;
	for(auto y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]]) son[x]=y;
	}
}
void dfs2(int x){
	dfn[x]=++tim,seq[tim]=x;
	for(auto y:E[x]){
		if(y==fa[x]||y==son[x])continue;
		qz[y]=qz[x]+1,dfs2(y);
	}
	if(son[x]){
		qz[son[x]]=qz[x];
		vis[son[x]]=1;
		dfs2(son[x]);
	}
}
void procedure(){
	n=read(),V=read(),tim=0;
	for(int i=1;i<=n;i++) c[i]=read(),w[i]=read(),E[i].clear(),fa[i]=vis[i]=0;

	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	dfs2(1);
	for(int i=0;i<2;i++)memset(f[i],0xc0,sizeof(ll)*(V+1));
	bf.reset();bf[0]=bf[1]=1;
	f[1][c[1]]=w[1],f[0][0]=0;
	for(int i=1;i<n;i++){
		int x=seq[i],y=seq[i+1];
		bg.reset();
		for(int j=bf._Find_first();j<(1<<qz[x]+1);j=bf._Find_next(j)){
			int t=(j>>(qz[x]+1-qz[y]-vis[y]))&1;
			int s=j>>(qz[x]+1-qz[y]);
			for(int o=0;o<2-t;o++){
				if(!bg[s<<1|o]){
					bg[s<<1|o]=1;
					memset(g[s<<1|o],0xc0,sizeof(ll)*(V+1));
				}
				for(int k=o*c[y];k<=V;k++)
					chkmax(g[s<<1|o][k],f[j][k-o*c[y]]+o*w[y]);
			}
		}
		swap(bf,bg);
		for(int j=bf._Find_first();j<(1<<qz[y]+1);j=bf._Find_next(j))
			memcpy(f[j],g[j],sizeof(ll)*(V+1));
	}
	ll ans=0;
	for(int i=0;i<(1<<qz[seq[n]]+1);i++)
		for(int j=0;j<=V;j++)chkmax(ans,f[i][j]);
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}