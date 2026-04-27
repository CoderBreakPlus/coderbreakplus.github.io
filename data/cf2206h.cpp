// created time: 2026-04-27 14:51:32
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

ll n,a[200005];

void procedure(){
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	ll ret=0;
	for(ll i=2;i<=n;i++)ret+=max(a[i]-a[i-1],a[i-1]-a[i]);

	ll ok=0;
	for(ll i=2;i<=n;i++)
		if(a[i]!=a[i-1]) ok=__gcd(ok,max(a[i]-a[i-1],a[i-1]-a[i]));
	ok*=2;

	ll mn = a[1];
	if(ok){
		for(ll i=2;i<=n;i++){
			ll v1 = a[1], v2 = 2*a[i]-a[1];
			mn = min(mn, (v1%ok+ok-1)%ok+1);
			mn = min(mn, (v2%ok+ok-1)%ok+1);
		}
	}else{
		for(ll i=2;i<=n;i++)
			if(2*a[i]>a[1])
			mn = min(mn, 2*a[i]-a[1]);
	}
	printf("%lld\n",mn+ret);
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