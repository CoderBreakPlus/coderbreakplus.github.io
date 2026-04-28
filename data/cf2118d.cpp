// created time: 2026-04-28 18:41:56
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

ll n,m,dp[200005];
vector<pair<ll,ll>>vec[200005];

void procedure(){
	n=read(),m=read();
	ll v0=1;
	while(n--){
		ll l=read(),r=read(),p=read(),q=read();
		ll s1=p*INV(q)%mod;
		ll s0=(mod+1-s1)%mod;
		v0=v0*s0%mod;
		vec[r].pb(l,s1*INV(s0)%mod);
	}	
	dp[0]=1;
	for(ll i=1;i<=m;i++){
		for(auto [j,v]:vec[i])dp[i]=(dp[i]+dp[j-1]*v)%mod;
	}
	printf("%lld\n",dp[m]*v0%mod);
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