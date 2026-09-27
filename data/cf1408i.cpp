// created time: 2026-09-27 19:51:44
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
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
const int N = 100000;
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
int n,k,c,f[2][20][1<<16],a[1<<16],bas;

int lowbit(int x){ return x&-x; }
void upd(int &a,ull b){ a=(a+b)%mod; }

void procedure(){
	n=read(),k=read(),c=read();
	for(int i=1;i<=n;i++) a[i]=read();
	sort(a+1,a+n+1,[](int x,int y){
		return lowbit(x>>4)<lowbit(y>>4);
	});
	
	f[0][0][0]=1;
	for(int i=1,o=1;i<=n;i++,o^=1){
		int d=a[i]-(a[i]&15),x=a[i]-d+lowbit(d);
		bas^=d-lowbit(d); d=max(4,(d?__builtin_ctz(d):0)+1);

		for(int j=0;j<=k;j++)
			memset(f[o][j],0,sizeof(int)<<d);
		for(int j=0;j<=k;j++)
			for(int s=0;s<(1<<d);s++)if(f[o^1][j][s])
			for(int r=0;j+r<=k;r++)
				upd(f[o][j+r][s^(x-r)], (ull)f[o^1][j][s]*inv[r]);
	}
	int coef=(ull)fac[k]*qpow(n,mod-1-k)%mod;

	for(int s=0;s<(1<<c);s++)printf("%llu ",(ull)coef*f[n&1][k][s^bas]%mod);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}