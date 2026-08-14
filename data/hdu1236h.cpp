// created time: 2026-08-13 15:57:06
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

int dp[2005][2005],dis[2005][2005],sz[2005],dfn[2005],tim;
int n,mx;
vector<int>E[2005];
vector<pair<int,int>>vec;
void dfs(int x,int fa,int rt){
	for(int y:E[x]){
		if(y==fa)continue;
		chkmax(mx,dis[rt][y]=dis[rt][x]+1);
		dfs(y,x,rt);
	}
}

void dfs(int x,int fa){
	sz[x]=1; dfn[x]=++tim;
	for(int y:E[x]){
		if(y==fa)continue;
		dfs(y,x); sz[x]+=sz[y];
	}
}

int calc(int x,int y){
	if(dfn[x]>dfn[y])swap(x,y);
	if(dfn[x]<=dfn[y]&&dfn[y]<dfn[x]+sz[x]) {
		int ok=0;
		for(int z:E[x]) 
			if(1+dis[z][y]==dis[x][y])ok=n-sz[z];
		return ok*sz[y];
	}else
		return sz[x]*sz[y];
}
void procedure(){
	n=read(),mx=tim=0;
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) dp[i][j]=dis[i][j]=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	for(int i=1;i<=n;i++) dfs(i,0,i);
	dfs(1,0);

	if(mx==n-1) printf("%d ",2*n-1);
	else printf("%d ",n+1);

	vec.clear();
	for(int i=1;i<=n;i++)
		for(int j=i;j<=n;j++) vec.pb(i,j);

	sort(vec.begin(),vec.end(),[&](pair<int,int> A,pair<int,int> B){
		auto [p,q]=A; auto [u,v]=B;
		return dis[p][q]<dis[u][v];
	});
	
	int ans=0;
	for(auto [i,j]: vec){
		if(i==j){
			dp[i][j]+=n;
			for(int p:E[i])for(int q:E[i])
				if(p<q)dp[i][j]+=calc(p,q);
		}else{
			dp[i][j]+=calc(i,j);
		}
		chkmax(ans,dp[i][j]);
		for(int k:E[i])if(dis[k][j]-1==dis[i][j]){
			if(k<j)chkmax(dp[k][j],dp[i][j]);
			else chkmax(dp[j][k],dp[i][j]);
		}
		for(int k:E[j])if(dis[k][i]-1==dis[j][i]){
			if(k<i)chkmax(dp[k][i],dp[i][j]);
			else chkmax(dp[i][k],dp[i][j]);
		}
	}
	printf("%d\n",ans);
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