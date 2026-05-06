// created time: 2026-05-05 12:12:17
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

ll n,dp[25][2],a[25];

void procedure(){
	n=read();
	for(ll i=0;i<20;i++)a[i]=n%10,n/=10;

	memset(dp,0x3f,sizeof(dp));
	dp[20][0]=0;
	for(ll i=20;i>=1;i--){
		dp[i-1][0]=min(dp[i-1][0],dp[i][0]+a[i-1]);
		dp[i-1][1]=min(dp[i-1][1],dp[i][0]+a[i-1]+1);

		dp[i-1][1]=min(dp[i-1][1],dp[i][1]+9-a[i-1]);
		dp[i-1][0]=min(dp[i-1][0],dp[i][1]+10-a[i-1]);
	}
	printf("%lld\n",dp[0][0]);
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