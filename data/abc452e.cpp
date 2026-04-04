#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };

ll n,m,a[500005],b[500005];

void procedure(){
	n=read(),m=read();
	ll sum=0;
	for(ll i=1;i<=n;i++)a[i]=read(),sum=(sum+1ull*i*a[i])%mod;

	for(ll i=1;i<=n;i++)addmod(a[i]+=a[i-1]);
	for(ll i=1;i<=m;i++)b[i]=read();

	ll ans=0;
	for(ll j=1;j<=m;j++){
		ll ret=0;
		
		for(ll i=0;i<=n;i+=j)
			ret=(ret+1ull*(-a[min(n,i+j-1)]+(i?a[i-1]:0)+mod)*(i/j))%mod;

		ret=(1ull*ret*j+sum)%mod;
		ans=(ans+1ull*ret*b[j])%mod;
	}
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}