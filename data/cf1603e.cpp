// created time: 2026-04-29 16:09:08
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline ll init(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	return 0xfaded;
}
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull operator ()(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
};
int faded = init();
int n = read();
const int mod = read();
const ull DD = 8ull * mod * mod;

void fuckit(ull &W){ if(W >= DD) W -= DD; }

FastMod Mod = FastMod(mod);

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

const int B=18, N=200, M=3500;
ull f[M+5][N+5],g[M+5][N+5];

void procedure(){
	int ans=0;
	for(int mn=max(1,n+1-B);mn<=n+1;mn++){
		memset(f,0,sizeof(f));
		for(int i=1;i<=mn&&i<=n;i++)f[0][i]=inv[i];

		for(int w=mn+1;w<=n+1;w++){
			memset(g,0,sizeof(g));
			for(int i=0;i<=M;i++)
				for(int j=1;j<=n;j++){
					if(!f[i][j])continue;
					f[i][j]=Mod(f[i][j]);
					int ii=i+j;
					g[ii][j]+=f[i][j];
					for(int k=1;j+k<=n;k++){
						if((j+k)*w-ii<=mn*w){
							fuckit(g[ii][j+k]+=f[i][j]*inv[k]);
						}
					}
				}
			memcpy(f,g,sizeof(f));
		}
		int out=0;
		for(int i=0;i<=M;i++)out=Mod(out+f[i][n]);
		addmod(ans+=out);
	}
	printf("%d\n",(ull)ans*fac[n]%mod);
}
int main(){
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}