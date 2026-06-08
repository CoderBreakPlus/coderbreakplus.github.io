// created time: 2026-06-08 08:34:36
// 单位根反演
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+9, w[3] = {1,115381398,884618610};
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

int h,m,k,f[3][3];

void procedure(){
	h=read(),m=read(),k=read()+1;

	for(int i:{0,1,2})for(int j:{0,1,2}){
		if((i+j)%3==0){
			f[i][j]=k;
			continue;
		}
		for(int t=0;t<k%3;t++){
			addmod(f[i][j]+=w[(i+j)*t%3]);
		}
	}

	int ans=0;
	for(int h0=0;h0<=h;h0++){
		for(int h1=0;h0+h1<=h;h1++){
			int h2=h-h0-h1;
			int cf=(ull)fac[h]*inv[h0]%mod*inv[h1]%mod*inv[h2]%mod,val=0;
			for(int w:{0,1,2})
				val=(val+qpow(f[0][w],h0)*qpow(f[1][w],h1)%mod*qpow(f[2][w],h2))%mod;
			ans=(ans+(ull)cf*qpow(val,m))%mod;
		}
	}
	printf("%llu\n",(ull)ans*qpow(INV(3),h+m)%mod);
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