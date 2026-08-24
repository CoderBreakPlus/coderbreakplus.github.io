// created time: 2026-08-24 08:26:53
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<int,pair<int,int>> P3;
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

int n,m,a,b,fa[75],sz[75],ord[75],idx;
vector<int>E[75],G[75];

int find(int x){
	if(x!=fa[x])fa[x]=find(fa[x]);
	return fa[x];
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	fa[x]=y,sz[y]+=sz[x];
}
int dp[1<<17][75],vis[1<<17][75];

int sta(int x){ return ord[find(x)] ? (1<<ord[find(x)]-1) : 0; }
void procedure(){
	n=read(),m=read(),a=read(),b=read();
	for(int i=1;i<=n;i++) fa[i]=i,sz[i]=1;

	for(int i=1;i<=m;i++){
		int u=read(),v=read(),c=read();
		if(c==a) merge(u,v),G[u].pb(v),G[v].pb(u);
		else E[u].pb(v),E[v].pb(u);
	}
	for(int i=1;i<=n;i++)
		if(find(i)==i){
			if(sz[i]>=4)ord[i]=++idx; 
		}
	priority_queue<P3,vector<P3>,greater<P3>>Q;
	memset(dp,0x3f,sizeof(dp));
	dp[sta(1)][1]=0;
	Q.push({0,{sta(1),1}});

	while(!Q.empty()){
		auto [i,x]=Q.top().se; Q.pop();
		if(vis[i][x])continue;vis[i][x]=1;
		for(int y:G[x])if(dp[i][y]>dp[i][x]+a){
			dp[i][y]=dp[i][x]+a;
			Q.push({dp[i][y],{i,y}});
		}
		for(int y:E[x]){
			if(find(y)==find(x))continue;
			int j=i;
			if(j&sta(y))continue;j|=sta(y);
			if(dp[j][y]>dp[i][x]+b){
				dp[j][y]=dp[i][x]+b;
				Q.push({dp[j][y],{j,y}});
			}
		}
	}
	for(int i=1;i<=n;i++){
		int out=2e9;
		for(int j=0;j<(1<<idx);j++)chkmin(out,dp[j][i]);
		printf("%d ",out);
	}
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