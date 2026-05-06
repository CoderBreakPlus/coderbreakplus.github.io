// created time: 2026-05-05 16:10:03
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
const int N = 305, M = 1e5;
int n,q,v[N];
ll dp[M+5];

void procedure(){
	n=read(),q=read();
	memset(dp,0xc0,sizeof(dp));
	dp[0]=0;
	for(int i=1;i<=n;i++){
		v[i]=read();
		for(int j=i;j<=M;j++)
			dp[j]=max(dp[j],dp[j-i]+v[i]);
	}

	while(q--){
		ll ans=-1e18;
		int w=read();
		for(int i=1;i<=n;i++){
			int red=max(0, (w-M+i-1)/i);
			ans=max(ans, dp[w-red*i]+(ll)v[i]*red);
		}
		printf("%lld\n",ans);
	}
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