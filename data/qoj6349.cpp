// created time: 2026-06-15 14:52:54
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll

using u32 = unsigned int;
using u64 = unsigned long long;
using u128 = __uint128_t;

// 题目提供的 Barrett 约减模板
struct Barrett {
	u64 b, m;
	Barrett() : b(), m() {}
	Barrett(u64 _b) : b(_b), m(-1ULL / _b) {}
	u32 reduce(u64 x) {
		u64 q = (u64)((u128(m) * x) >> 64), r = x - q * b;
		return r - b * (r >= b);
	}
} BA;

int n,mod;
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

inline int get_g(int P) {
	int temp = P - 1;
	vector<int> primes;
	for (int i = 2; i * i <= temp; i++) {
		if (temp % i == 0) {
			primes.pb(i);
			while (temp % i == 0) temp /= i;
		}
	}
	if (temp > 1) primes.pb(temp);
	
	for (int g = 2; g < P; g++) {
		bool ok = true;
		for (int q : primes) {
			if (qpow(g, (P - 1) / q) == 1) {
				ok = false;
				break;
			}
		}
		if (ok) return g;
	}
	return 0;
}

const int N = 50000;
int fac[N+5],inv[N+5],iv[N+5];
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

const int M = 32768;
int rev_pos[M], W[M];

void ntt_init(int G) {
	int wn = qpow(G, (mod - 1) / M);
	W[M / 2] = 1;
	for(int i = M / 2 + 1; i < M; i++) W[i] = BA.reduce((ull)W[i - 1] * wn);
	for(int i = M / 2 - 1; i > 0; i--) W[i] = W[i << 1];
	for(int i = 0; i < M; i++) {
		rev_pos[i] = (rev_pos[i >> 1] >> 1) | ((i & 1) ? (M >> 1) : 0);
	}
}

inline void ntt(int *a, int len, int type) {
	for(int i = 0; i < len; i++) if(i < rev_pos[i]) swap(a[i], a[rev_pos[i]]);
	for(int step = 2; step <= len; step <<= 1) {
		int mid = step >> 1;
		for(int i = 0; i < len; i += step) {
			for(int j = 0; j < mid; j++) {
				int x = a[i + j];
				int y = BA.reduce((ull)W[mid + j] * a[i + j + mid]);
				a[i + j] = x + y >= mod ? x + y - mod : x + y;
				a[i + j + mid] = x >= y ? x - y : x - y + mod;
			}
		}
	}
	if(type == -1) {
		reverse(a + 1, a + len);
		int inv_n = INV(len);
		for(int i = 0; i < len; i++) a[i] = BA.reduce((ull)a[i] * inv_n);
	}
}

int f[255][M];
int valF[255][M], valP[M];
int YA[130][M], XB[128][M];

void procedure(){
	n=read(),mod=read();
	BA = Barrett(mod);
	math_init();

	int G = get_g(mod);
	ntt_init(G);
	
	for(int i=1;i<=n*(n+1)/2;i++)
		iv[i]=(ull)inv[i]*fac[i-1]%mod;
	
	int w0 = qpow(G, (mod - 1) / M);
	int cur_w = 1;
	vector<int> X(M), Y(M);
	for(int k=0; k<M; k++) {
		X[k] = cur_w;
		Y[k] = (mod + 1 - cur_w) % mod;
		cur_w = BA.reduce((ull)cur_w * w0);
	}

	for(int k=0; k<M; k++){
		int p_Y = 1;
		for(int B=0; B<128; B++){
			XB[B][k] = BA.reduce((ull)X[k] * p_Y);
			p_Y = BA.reduce((ull)p_Y * Y[k]);
		}
		int Y_128 = p_Y;
		int p_Y128 = 1;
		for(int A=0; A<130; A++){
			YA[A][k] = p_Y128;
			p_Y128 = BA.reduce((ull)p_Y128 * Y_128);
		}
	}

	f[0][0]=1;
	for(int k=0; k<M; k++) valF[0][k]=1;

	for(int i=1; i<=n; i++){
		for(int k=0; k<M; k++) valP[k]=0;

		for(int p=0; p<=(i-1)/2; p++){
			int q = i-1-p;
			int tot = (p+1)*(q+1)-1;
			int A = tot >> 7, B = tot & 127;
			bool is_mid = (p == q);

			for(int k=0; k<M; k++){
				int term = BA.reduce((ull)YA[A][k] * XB[B][k]);
				int mult1 = BA.reduce((ull)valF[p][k] * valF[q][k]);
				int add = BA.reduce((ull)term * mult1);
				if(!is_mid){
					add += add;
					if(add >= mod) add -= mod;
				}
				valP[k] += add;
				if(valP[k] >= mod) valP[k] -= mod;
			}
		}

		ntt(valP, M, -1);

		f[i][0] = 0;
		int max_deg = i*(i+1)/2;
		for(int l=1; l<=max_deg; l++){
			f[i][l] = BA.reduce((ull)valP[l] * iv[l]);
		}
		for(int l=max_deg+1; l<M; l++) f[i][l] = 0;

		for(int k=0; k<M; k++) valF[i][k] = f[i][k];
		ntt(valF[i], M, 1);
	}

	for(int n=2;n<=::n;n++){
		int ret=0;
		for(int j=0;j<=n*(n-1)/2;j++) addmod(ret+=f[n-1][j]);
		printf("%d\n",(int)((ull)ret*fac[n]%mod*((mod+1)/2)%mod));
	}
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