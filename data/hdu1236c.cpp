// created time: 2026-08-13 15:25:42
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
const int NN = 500000;
int fac[NN+5],inv[NN+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=NN;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[NN]=qpow(fac[NN],mod-2);
	for(int i=NN-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

const int B = 800, N = 1e5;
int f[B+5][N+5],g[N+5];

int n,q,ans[N+5];

int calc(int x,int k){
	if(k<=B)
		return f[k][x];

	int ret=0;
	for(int j=0;1+j*k<=x;j++)
		addmod(ret+=binom(x-1-j*k+j,j));

	return ret;
}
void procedure(){
	n=read(),q=read();

	for(int i=1;i<=n;i++){
		ans[i]=1;
		for(int j=1;1+(j-1)*i<=n;j++)
			addmod(ans[i]+=binom(n-1-(j-1)*i+j,j));
	}
	while(q--){
		int x=read(),k=read();
		printf("%llu\n", (ans[k]+(ull)(mod-calc(x,k))*calc(n-x+1,k))%mod);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	math_init();

	for(int i=1;i<=B;i++){
		// dec>=i
		f[i][0]=1;
		for(int j=1;j<=N;j++){
			f[i][j]=1;
			if(j-i>=1) f[i][j]+=g[j-i];
			addmod(f[i][j]);
			addmod(g[j]=g[j-1]+f[i][j]);
		}	
	}
	ll T=read();
	while(T--) procedure();
	return 0;
}