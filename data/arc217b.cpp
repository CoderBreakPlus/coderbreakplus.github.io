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
const int N = 1000000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

ll n,k,a[1000005],pos[1000005],pw[1000005];
// ll f[200005],s[200005];

ll fc(ll x){ if(x<0)return 0;return fac[x];}
void procedure(){
	n=read(),k=read();
	for(ll i=1;i<=n;i++) pos[i]=0;
	for(ll i=1;i<=k;i++) a[i]=read(),pos[a[i]]=1;

	ll ans=1ull*fc(n-k)*(pw[n]-1)%mod;

	ll mx=0;
	for(ll i=1;i<=k;i++){
		if(mx<a[i]) ans=(ans+1ull*(mod-fc(n-k))*pw[a[i]-1])%mod,mx=a[i];
	}

	for(ll i=n;i>=1;i--){
		if(pos[i]) break;
		if(!pos[i])
		ans=(ans+1ull*(mod-pw[i-1])*binom(n-k,n-i+1)%mod*fc(n-i)%mod*fc(n-k-(n-i+1)))%mod;
	}
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif

	// for(ll i=2;i<=2e5;i++){
	// 	addmod(f[i]=s[i-1]+(i-1));
	// 	addmod(s[i]=s[i-1]+f[i]);
	// }

	pw[0]=1;
	for(ll i=1;i<=1e6;i++) addmod(pw[i]=pw[i-1]*2);
	// for(ll i=1;i<=10;i++)printf("%lld ",f[i]);puts("");
	ll T=read();
	math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}