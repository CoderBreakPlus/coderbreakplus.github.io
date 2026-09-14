// created time: 2026-09-14 18:43:36
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcount
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void addmod(T &x){ if(x >= mod) x -= mod; }
const ll mod = (1ll<<50);

#define u128 __uint128_t
inline ll qpow(ll a,ll b,ll m){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=(u128)ans*base%m;
		base=(u128)base*base%m; b>>=1;
	}
	return ans;
}

ll n,a[200005],b[200005],c[200005],fac[200005],inv[200005];

void procedure(){
	n=read();
	fac[0]=inv[0]=1;
	for(int i=1;i<=n;i++){
		int v=i/(i&-i);
		fac[i]=(u128)fac[i-1]*v%mod;
		inv[i]=(u128)inv[i-1]*qpow(v,mod/2-1,mod)%mod;
	}
	for(int i=0;i<=n;i++) a[i]=(u128)(read()<<popcnt(i))*inv[i]%mod;
	for(int i=0;i<=n;i++) b[i]=(u128)(read()<<popcnt(i))*inv[i]%mod;

	for(int i=0;i<=n;i++)
		for(int j=0;i+j<=n;j++)
			c[i+j]=(c[i+j]+(u128)a[i]*b[j])%mod;

	ll m=(1ull<<32)-1;
	for(int i=0;i<=n;i++){
		ll tmp=(u128)(c[i]>>popcnt(i))*fac[i]%mod;
		printf("%lld ",tmp&m);
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