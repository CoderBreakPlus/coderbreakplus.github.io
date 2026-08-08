// created time: 2026-08-08
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
	ll ans=1, base=a%mod;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }
const int N = 5000000;
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

int n,m,l,x;

struct Frac{
	int x,y;
	Frac(){ x=0,y=1; }
	Frac(int X){ x=X,y=1; }
	Frac(int X,int Y){ x=X,y=Y; }
};
inline Frac operator+ (const Frac &A, const Frac &B){
	return Frac(((ull)A.x*B.y+(ull)A.y*B.x)%mod,(ull)A.y*B.y%mod);
}
inline Frac operator* (const Frac &A, const Frac &B){
	return Frac((ull)A.x*B.x%mod,(ull)A.y*B.y%mod);
}
void procedure(){
	n=read(),m=read(),l=read(),x=read();

	int prod=(ull)n*m%mod*l%mod;
	int W=min({n,m,l});

	int cf=1;
	Frac Ans;
	for(int k=1;k<x;k++)
		cf=(ull)cf*((prod+(ull)(-n+k+mod)*(m-k)%mod*(l-k))%mod)%mod;
	for(int k=x;k<=W;k++){
		cf=(ull)cf*((prod+(ull)(-n+k+mod)*(m-k)%mod*(l-k))%mod)%mod;
		int tmp=(ull)perm(n,k)*perm(m,k)%mod*perm(l,k)%mod;
		if((k-x)&1)
			tmp=(ull)tmp*(mod-binom(k,x))%mod;
		else
			tmp=(ull)tmp*binom(k,x)%mod;
		Ans=Ans+Frac(tmp,cf);
	}
	printf("%llu\n",(ull)Ans.x*INV(Ans.y)%mod);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	math_init();
	while(T--) procedure();
	return 0;
}