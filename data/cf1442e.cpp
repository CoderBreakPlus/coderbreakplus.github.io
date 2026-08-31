// created time: 2026-08-31 19:10:39
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

int n,a[200005];
vector<int>E[200005];

int dp[200005][3],Mid;

void dfs(int x,int fa){
	dp[x][1]=dp[x][2]=0;

	for(int y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
		for(int o:{1,2}){
			int sub=min(dp[y][1]+(o!=1), dp[y][2]+(o!=2));
			if(dp[x][o]+sub<=Mid) chkmax(dp[x][o],sub);
			else dp[x][o]=1e9;
		}
	}

	if(a[x]==1)dp[x][2]=1e9;
	if(a[x]==2)dp[x][1]=1e9;
}
bool check(){
	dfs(1,0);
	return dp[1][1]<=n||dp[1][2]<=n;
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)
		a[i]=read(),E[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	int L=0,R=n,Ans=n+1;
	while(L<=R){
		Mid=(L+R)>>1;
		if(check())Ans=Mid,R=Mid-1;
		else L=Mid+1;
	}
	printf("%d\n", (Ans+3)/2);
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