// created time: 2026-08-29 10:46:58
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

int n,a,f[5005][5005];

inline void upd(int &a,ull b){ a=(a+b)%mod; }
const int N = 10000000;
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

void procedure(){
	n=read(),a=read();
	f[0][0]=1;
	for(int i=0;i<a;i++){
		for(int j=0;j<=i;j++){
			upd(f[i+1][j+1], (ull)f[i][j]*(j+1));
			addmod(f[i+1][j]+=mod-f[i][j]);
		}
	}

	int ans=0;
	for(int j=1;j<=a;j++)
		upd(ans, (ull)f[a][j] * fac[j+n-a-1] % mod * inv[j-1]);

	for(int i=0;i<a;i++)
		for(int j=0;j<=i;j++){
			f[i][j]=(ull)f[i][j]*fac[a-i-1]%mod*inv[j-1]%mod;
		}

	for(int i=1;i<a;i++)
		for(int j=0;j<=i;j++)
			addmod(f[i][j]+=f[i-1][j]);

	for(int i=1;i<=a;i++)
		for(int j=1;j<i;j++){
			int tot=0;
			upd(tot, (ull)inv[a-i] % mod * fac[n+j-i-1]);
			upd(ans, (ull)f[i-1][j] * tot);
		}

	printf("%d\n", ans);
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