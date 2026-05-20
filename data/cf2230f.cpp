// created time: 2026-05-20 19:22:48
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
const int B = 17;
int n=1,q,fa[200005];
vector<int>E[200005];
int dp[200005][B+1],dp2[200005][B+1],tim[200005];
int ans[200005];

void dfs1(int x){
	dp[x][1]=tim[x];
	for(auto y:E[x])dfs1(y);
	for(int i=2;i<=B;i++){
		int mn=q+1, mn2=q+1;
		for(auto y:E[x])
			if(dp[y][i-1]<mn)mn2=mn,mn=dp[y][i-1];
			else chkmin(mn2,dp[y][i-1]);
		dp[x][i]=mn2;
	}
}
void dfs2(int x){
	for(auto y:E[x]) dp2[y][1]=tim[x];
	for(int i=2;i<=B;i++){
		multiset<int>S = {q+1,q+1};
		if(fa[x]) S.emplace(dp2[x][i-1]);
		for(auto y:E[x]) S.emplace(dp[y][i-1]);

		for(auto y:E[x]){
			S.erase(S.find(dp[y][i-1]));
			dp2[y][i] = *next(S.begin());
			S.emplace(dp[y][i-1]);
		}
	}
	for(auto y:E[x])dfs2(y);
}

void procedure(){
	q=read();
	for(int i=1;i<=q;i++){
		fa[++n]=read();
		tim[n]=i;
		E[fa[n]].pb(n);
	}
	dfs1(1);
	dfs2(1);

	ans[0]=1;
	for(int x=1;x<=n;x++){
		for(int i=2;i<=B;i++){
			int mn=q+1, mn2=q+1;
			if(fa[x]) mn=dp2[x][i-1];

			for(auto y:E[x])
				if(dp[y][i-1]<mn)mn2=mn,mn=dp[y][i-1];
				else chkmin(mn2,dp[y][i-1]);
			chkmax(ans[mn2],i);
		}
	}
	for(int i=1;i<=q;i++) chkmax(ans[i],ans[i-1]),printf("%d ",ans[i]);
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