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
const int N = 8000000;
int fac[N+5],inv[N+5],iv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(int i=1;i<=N;i++) iv[i]=(ull)inv[i]*fac[i-1]%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}
int n,ans;

const int c[5] = {INV(24),INV(6),INV(4),INV(6),INV(24)};
inline void upd(int &a, ull b){ a=(a+b)%mod; }

struct Node{
	int f[8000005],n;
	void init(int N){
		n=N;
		f[0]=qpow(c[0],n);
		for(int i=1;i<=2*n;i++){
			f[i]=((ull)(n-i+1+mod)*c[1]%mod*f[i-1]+(ull)(2*n-i+2)*c[2]%mod*(i>=2?f[i-2]:0))%mod*iv[i]%mod*24%mod;
		}
	}
	int q(int x){
		if(x>2*n||x<0) return 0;
		return f[x];
	}
}F[4];

int fk[2000005];
int yyz(int x){
	if(x>n-4||x<0) return 0;
	return fk[x];
}
void procedure(){
	n=read();
	if(n<=4){
		puts("0");
		return;
	}

	fk[0]=qpow(c[0],n-4);
	int tmp=c[1]*INV(c[0])%mod;
	for(int i=1;i<=n-4;i++) fk[i]=(ull)fk[i-1]*tmp%mod;
	for(int i=0;i<=n-4;i++) fk[i]=(ull)fk[i]*binom(n-4,i)%mod;

	int all = fac[4*n]*qpow(INV(24),n)%mod;
	ans=all;
	for(int i=0;i<4;i++)F[i].init(n-i);
	// (1/24 + 1/6 x + 1/4 x^2)

	// cout<<"all="<<all<<endl;
	for(int x=1;x<=4*n;x++){
		int ret0=0,ret1=0,ret2=0,ret3=0,ret4=0;
		// 0 个刻子

		int cf=(ull)fac[x]*fac[4*n-x]%mod;
		upd(ret0, (ull)cf*F[0].q(x));

		// 1 个刻子

		int cf1=(ull)cf*binom(n,1)%mod;
		for(int i:{3,4}){
			int s=i;
			int v=(ull)cf1*c[i]%mod;
			upd(ret1, (ull)v*F[1].q(x-s));
		}

		// 2 个刻子

		int cf2=(ull)cf*binom(n,2)%mod;
		for(int i:{3,4})for(int j:{3,4}){
			int s=i+j;
			int v=(ull)cf2*c[i]%mod*c[j]%mod;
			upd(ret2, (ull)v*F[2].q(x-s));
		}

		// 3 个刻子

		int cf3=(ull)cf*binom(n,3)%mod;
		for(int i:{3,4})for(int j:{3,4})for(int k:{3,4}){
			int s=i+j+k;
			int v=(ull)cf3*c[i]%mod*c[j]%mod*c[k]%mod;
			upd(ret3, (ull)v*F[3].q(x-s));
		}

		// 4 个刻子

		int cf4=(ull)cf*binom(n,4)%mod;
		for(int i:{3,4})for(int j:{3,4})for(int k:{3,4})for(int l:{3,4}){
			int s=i+j+k+l;
			int v=(ull)cf4*c[i]%mod*c[j]%mod*c[k]%mod*c[l]%mod;
			upd(ret4, (ull)v*yyz(x-s));
		}

		ans=(0ull+ans+ret0+ret1+ret2+ret3+ret4)%mod;
	}
	// cout<<"ans="<<ans<<endl;
	printf("%lld\n",ans*INV(all)%mod);
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