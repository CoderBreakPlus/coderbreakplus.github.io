// created time: 2026-10-04 15:17:09
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
namespace polynomial {

using std::vector;
using ull = unsigned long long;

#ifdef LOCAL
#define POLYNOMIAL_DEBUG
#endif

#ifdef POLYNOMIAL_DEBUG
#define ASSERT(...) assert(__VA_ARGS__)
#else
#define ASSERT(...)
#endif

constexpr int mod = 998244353, G = 3, invG = 332748118, Mn = 23, M = 1 << Mn;

int pow_w[M << 1], pow_iw[M << 1], inv[M + 1], fac[M + 1], ifac[M + 1];

template <typename _Tp>
static inline void addmod(_Tp &x) {
	if (x >= mod) {
		x -= mod;
	}
}

static constexpr inline int qpow(int a, int b) {
	int res = 1;
	while (b) {
		if (b & 1) {
			res = (ull)res * a % mod;
		}
		a = (ull)a * a % mod;
		b >>= 1;
	}
	return res;
}

static constexpr inline int qinv(int a) {
	return qpow(a, mod - 2);
}

struct initializer {
	initializer() {
		int w = qpow(G, mod >> Mn), iw = qpow(invG, mod >> Mn);
		pow_w[M] = pow_iw[M] = 1;
		for (int j = M + 1; j < M << 1; ++j) {
			pow_w[j] = (ull)pow_w[j - 1] * w % mod;
			pow_iw[j] = (ull)pow_iw[j - 1] * iw % mod;
		}
		for (int j = M - 1; ~j; --j) {
			pow_w[j] = pow_w[j << 1];
			pow_iw[j] = pow_iw[j << 1];
		}
		fac[0] = 1;
		for (int i = 1; i <= M; ++i) {
			fac[i] = (ull)fac[i - 1] * i % mod;
		}
		ifac[M] = qinv(fac[M]);
		for (int i = M; i; --i) {
			ifac[i - 1] = (ull)ifac[i] * i % mod;
			inv[i] = (ull)ifac[i] * fac[i - 1] % mod;
		}
	}
} initializer;

inline void NTT_DIF(vector<int> &a) {
	ASSERT(a.size() && a.size() <= M);
	ASSERT((a.size() & (a.size() - 1)) == 0);
	int len = a.size();
	for (int i = len >> 1; i; i >>= 1) {
		int *c = pow_w + (i << 1);
		for (int j = 0; j < len; j += i << 1) {
			int *p = a.data() + j, *q = p + i;
			for (int k = 0; k < i; ++k) {
				int s = p[k], t = q[k];
				addmod(p[k] = s + t);
				q[k] = (ull)(s + mod - t) * c[k] % mod;
			}
		}
	}
}

inline void NTT_DIT(vector<int> &a) {
	ASSERT(a.size() && a.size() <= M);
	ASSERT((a.size() & (a.size() - 1)) == 0);
	int len = a.size();
	for (int i = 1; i < len; i <<= 1) {
		int *c = pow_iw + (i << 1);
		for (int j = 0; j < len; j += i << 1) {
			int *p = a.data() + j, *q = p + i;
			for (int k = 0; k < i; ++k) {
				int s = p[k], t = (ull)q[k] * c[k] % mod;
				addmod(p[k] = s + t);
				addmod(q[k] = s + mod - t);
			}
		}
	}
	for (int &x : a) {
		x = (ull)x * inv[len] % mod;
	}
}

struct poly {
	vector<int> p;

	poly(size_t b = 0) { p = vector<int>(b); }
	poly(const vector<int> &p) : p(p) {}
	poly(const std::initializer_list<int> &p) : p(p) {}

	inline void clear() { p.clear(); }
	inline void resize(size_t b, int v = 0) { ASSERT(0 <= v && v < mod); p.resize(b, v); }
	inline size_t size() const { return p.size(); }
	inline void shrink_to_fit() { p.shrink_to_fit(); }

	inline int &operator[](size_t b) { ASSERT(b < size()); return p[b]; }
	inline const int &operator[](size_t b) const { ASSERT(b < size()); return p[b]; }

	inline void print(const std::string &sep = " ", const std::string &end = "\n") const {
		for (int i = 0; i < (int)size(); ++i) {
			if (i) {
				std::cout << sep;
			}
			std::cout << p[i];
		}
		std::cout << end;
	}

	inline poly ogf2egf() const;
	inline poly egf2ogf() const;
	inline poly derivative() const;
	inline poly integral() const;

	inline poly square() const;
	inline poly inverse() const;
	inline poly inverse(size_t b) const;
	inline poly log() const;
	inline poly log(size_t b) const;
	inline poly exp() const;
	inline poly exp(size_t b) const;
	inline poly pow(int k) const;
	inline poly pow(int k, size_t b) const;
};

inline poly &operator+=(poly &a, const poly &b) {
	if (a.size() < b.size()) {
		a.resize(b.size());
	}
	for (int i = 0; i < (int)b.size(); ++i) {
		addmod(a[i] += b[i]);
	}
	return a;
}

inline poly operator+(poly a, const poly &b) {
	return a += b;
}

inline poly &operator-=(poly &a, const poly &b) {
	if (a.size() < b.size()) {
		a.resize(b.size());
	}
	for (int i = 0; i < (int)b.size(); ++i) {
		addmod(a[i] += mod - b[i]);
	}
	return a;
}

inline poly operator-(poly a, const poly &b) {
	return a -= b;
}

inline poly &operator*=(poly &a, poly b) {
	ASSERT(a.size() > 0 && b.size() > 0);
	int n = a.size() + b.size() - 1, len = 1 << (31 ^ __builtin_clz((n << 1) - 1));
	a.resize(len), b.resize(len);
	NTT_DIF(a.p), NTT_DIF(b.p);
	for (int i = 0; i < len; ++i) {
		a[i] = (ull)a[i] * b[i] % mod;
	}
	NTT_DIT(a.p);
	a.resize(n);
	return a;
}

inline poly operator*(poly a, const poly &b) {
	return a *= b;
}

inline poly &operator*=(poly &a, int k) {
	ASSERT(0 <= k && k < mod);
	for (int i = 0; i < (int)a.size(); ++i) {
		a[i] = (ull)a[i] * k % mod;
	}
	return a;
}

inline poly operator*(poly a, int k) {
	return a *= k;
}

inline poly &operator<<=(poly &a, size_t b) {
	a.p.insert(a.p.begin(), b, 0);
	return a;
}

inline poly operator<<(poly a, size_t b) {
	return a <<= b;
}

inline poly &operator>>=(poly &a, size_t b) {
	if (b >= a.size()) {
		a.clear();
	} else {
		a.p.erase(a.p.begin(), a.p.begin() + b);
	}
	return a;
}

inline poly operator>>(poly a, size_t b) {
	return a >>= b;
}

inline poly poly::ogf2egf() const {
	ASSERT(size() <= M);
	poly a(size());
	for (int i = 0; i < (int)size(); ++i) {
		a[i] = (ull)a[i] * ifac[i] % mod;
	}
	return a;
}

inline poly poly::egf2ogf() const {
	ASSERT(size() <= M);
	poly a(size());
	for (int i = 0; i < (int)size(); ++i) {
		a[i] = (ull)a[i] * fac[i] % mod;
	}
	return a;
}

inline poly poly::derivative() const {
	ASSERT(size());
	poly a(size() - 1);
	for (int i = 1; i < (int)size(); ++i) {
		a[i - 1] = (ull)p[i] * i % mod;
	}
	return a;
}

inline poly poly::integral() const {
	ASSERT(size() <= M - 1);
	poly a(size() + 1);
	for (int i = 0; i < (int)size(); ++i) {
		a[i + 1] = (ull)p[i] * inv[i + 1] % mod;
	}
	return a;
}

inline poly poly::square() const {
	ASSERT(size());
	int n = (size() << 1) - 1, len = 1 << (31 ^ __builtin_clz((n << 1) - 1));
	vector<int> a = p;
	a.resize(len);
	NTT_DIF(a);
	for (int i = 0; i < len; ++i) {
		a[i] = (ull)a[i] * a[i] % mod;
	}
	NTT_DIT(a);
	a.resize(n);
	return a;
}

inline poly poly::inverse() const {
	ASSERT(size() && p[0]);
	poly a({qinv(p[0])});
	for (int m = 1; m < (int)size(); m <<= 1) {
		int n = std::min(m << 1, (int)size());
		int len = 1 << (32 - __builtin_clz(n + (m << 1) - 3));
		a.resize(len);
		poly b(n);
		for (int i = 0; i < n; ++i) {
			b[i] = p[i];
		}
		b.resize(len);
		NTT_DIF(a.p);
		NTT_DIF(b.p);
		for (int i = 0; i < len; ++i) {
			int t = (ull)a[i] * b[i] % mod;
			a[i] = (ull)a[i] * (mod + 2 - t) % mod;
		}
		NTT_DIT(a.p);
		a.resize(n);
	}
	return a;
}

inline poly poly::inverse(size_t b) const {
	poly a = p;
	a.resize(b);
	return a.inverse();
}

inline poly poly::log() const {
	ASSERT(size() && p[0] == 1);
	poly a = derivative() * inverse();
	a.resize(size() - 1);
	return a.integral();
}

inline poly poly::log(size_t b) const {
	poly a = p;
	a.resize(b);
	return a.log();
}

inline poly poly::exp() const {
	ASSERT(size());
	ASSERT(size() <= M);
	ASSERT(p[0] == 0);
	int n = size();
	if (n == 1) {
		return {1};
	}
	poly b({1, p[1]}), c({1}), z1, z2({1, 1});
	for (int m = 2; m < n; m <<= 1) {
		poly y = b;
		y.resize(m << 1);
		NTT_DIF(y.p);
		z1 = z2;
		poly z(m);
		for (int i = 0; i < m; ++i) {
			z[i] = (ull)y[i] * z1[i] % mod;
		}
		NTT_DIT(z.p);
		for (int i = 0; i < (m >> 1); ++i) {
			z[i] = 0;
		}
		NTT_DIF(z.p);
		for (int i = 0; i < m; ++i) {
			z[i] = (ull)z[i] * (z1[i] ? mod - z1[i] : 0) % mod;
		}
		NTT_DIT(z.p);
		int oldc = c.size();
		c.resize(m);
		for (int i = oldc; i < m; ++i) {
			c[i] = z[i];
		}
		z2 = c;
		z2.resize(m << 1);
		NTT_DIF(z2.p);
		poly x(std::min(n, m));
		for (int i = 0; i < (int)x.size(); ++i) {
			x[i] = p[i];
		}
		x = x.derivative();
		x.resize(m);
		NTT_DIF(x.p);
		for (int i = 0; i < m; ++i) {
			x[i] = (ull)x[i] * y[i] % mod;
		}
		NTT_DIT(x.p);
		poly db = b.derivative();
		for (int i = 0; i < m - 1; ++i) {
			x[i] -= db[i];
			if (x[i] < 0) {
				x[i] += mod;
			}
		}
		x.resize(m << 1);
		for (int i = 0; i < m - 1; ++i) {
			x[m + i] = x[i];
			x[i] = 0;
		}
		NTT_DIF(x.p);
		for (int i = 0; i < (m << 1); ++i) {
			x[i] = (ull)x[i] * z2[i] % mod;
		}
		NTT_DIT(x.p);
		x.resize((m << 1) - 1);
		x = x.integral();
		for (int i = m; i < std::min(n, m << 1); ++i) {
			addmod(x[i] += p[i]);
		}
		for (int i = 0; i < m; ++i) {
			x[i] = 0;
		}
		NTT_DIF(x.p);
		for (int i = 0; i < (m << 1); ++i) {
			x[i] = (ull)x[i] * y[i] % mod;
		}
		NTT_DIT(x.p);
		int oldb = b.size();
		b.resize(std::min(n, m << 1));
		for (int i = oldb; i < (int)b.size(); ++i) {
			b[i] = x[i];
		}
	}
	b.resize(n);
	return b;
}

inline poly poly::exp(size_t b) const {
	poly a = p;
	a.resize(b);
	return a.exp();
}

inline poly poly::pow(int k) const {
	ASSERT(size() && p[0] == 1);
	ASSERT(0 <= k && k < mod);
	return (log() * k).exp();
}

inline poly poly::pow(int k, size_t b) const {
	poly a = p;
	a.resize(b);
	return a.pow(k);
}

} // namespace polynomial

using polynomial::poly;
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

int n,k;

poly dp,f,h,tmp,tmp2;
void upd(int &a,ull b){ a=(a+b)%mod; }

void procedure(){
	n=read(),k=read();
	dp.resize(n+1,0),f.resize(n+1,0),h.resize(n+1,0),tmp.resize(n+1,0);
	for(int j=1;2*j<n;j++)tmp[2*j]=((j&1)?binom(k+j,2*j):mod-binom(k+j,2*j));
	dp[1]=k+1;
	for(int i=2;i<=n;i++)
		dp[i]=(((i-1)/2)&1)?(mod-binom(k+1+(i-1)/2,i)):binom(k+1+(i-1)/2,i);
	dp=dp*(((poly){1}-tmp).inverse(n+1));

	tmp.clear();tmp.resize(n+1,0); tmp2=tmp;
	for(int i=1;2*i<=n;i++)
		tmp[i]=(ull)((i&1)?mod-dp[2*i+1]:dp[2*i+1])*inv[i-1]%mod;
	for(int j=0;2*j<=n;j++)
		tmp2[j]=(ull)inv[j];

	tmp=tmp*tmp2;

	for(int j=1;2*j+1<=n;j++)
		f[2*j+1]=(ull)tmp[j]*fac[j-1]%mod;

	f[1]=k+1;
	// f.print();
	f=(poly){1}-f;
	f=f.inverse(n+1);
	// f.print();

	tmp.clear();tmp.resize(n+1,0);
	for(int i=1;2*i<=n;i++)
		tmp[i]=(ull)((i&1)?mod-dp[2*i]:dp[2*i])*inv[i-1]%mod;

	tmp=tmp*tmp2;

	for(int j=1;2*j<=n;j++)
		h[2*j]=(ull)tmp[j]*fac[j-1]%mod;

	h[0]=1;
	// h.print();
	poly now=h*f*h;

	int ans=now[n];
	
	if(n&1){
		for(int i=1;2*i-1<=n;i++){
			ull v;
			if(i==1) v=mod-k;
			else v=(i&1)?mod-dp[2*i-1]:dp[2*i-1];
			int j=(n-2*i+1)/2;
			upd(ans, v*binom(j+i-1,i-1));
		}
	}
	printf("%d\n",ans);
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