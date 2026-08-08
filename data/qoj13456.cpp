// created time: 2026-08-07
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int mod;
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
// why i can only 60p
const int N = 500000;
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
int n,f[1005],g[1005],ans[1005];
const ull SB = 9e18;
void procedure(){

	n=read(),mod=read();
	math_init();

	for(int c=0;c<n;c++){
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		int limit=n-c;
		f[0]=fac[n];

		for(int i=1;i<=n;i++){
			ull s=0;
			for(int j=1;j<=i;j+=limit){
				s+=(ull)f[i-j]*inv[j]%mod;
				if(s>SB)s%=mod;
			}
			for(int j=limit;j<=i;j+=limit){
				s+=(ull)f[i-j]*(mod-inv[j])%mod;
				if(s>SB)s%=mod;
			}
			f[i]=s%mod;
		}

		addmod(ans[c]=fac[n]+mod-f[n]);
	}
	for(int i=0;i<n;i++)printf("%d\n",ans[i]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	while(T--) procedure();
	return 0;
}