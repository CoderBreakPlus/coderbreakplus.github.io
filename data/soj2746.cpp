// created time: 2026-11-16 12:47:57
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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
const int N=1000000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=(ull)fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=(ull)inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return (ull)fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return (ull)fac[x]*inv[x-y]%mod;
}
int m,a[1000005],mu[1000005],n;

void procedure(){
	m=read();
	int d=0,ans=0;
	for(int i=1;i<=m;i++)n+=(a[i]=read()),d=__gcd(d,a[i]);

	for(int i=1;i<=d;i++)if(d%i==0){
		int cf=fac[n/i];
		for(int j=1;j<=m;j++)
			cf=(ull)cf*inv[a[j]/i]%mod;
		// cout<<"i="<<i<<" cf="<<cf<<endl;
		// cout<<"mu="<<mu[i]<<endl;
		ans=(ans+(ull)(mu[i]+mod)*cf)%mod;
	}
	ans=(ull)ans*INV(n)%mod;
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	mu[1]=1;
	// for(int i=n;i>=1;i--)
	// 	for(int j=2*i;j<=n;j+=i)
	// 		mu[j]+=mu[i];
	for(int i=1;i<=N;i++)
		for(int j=2*i;j<=N;j+=i)
			mu[j]-=mu[i];
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}