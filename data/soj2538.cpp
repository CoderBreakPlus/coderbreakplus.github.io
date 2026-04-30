// created time: 2026-04-16 11:17:28
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
namespace grader_namespace {
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
bool Mbe;
constexpr int N = 1 << 22, mod = 998244353;
inline void add(int& x, int y) { x += y, x >= mod && (x -= mod); }
inline void sub(int& x, int y) { x -= y, x < 0 && (x += mod); }
inline int sum(int x, int y) { return x += y, x >= mod ? x - mod : x; }
inline int dif(int x, int y) { return x -= y, x < 0 ? x + mod : x; }
inline int neg(int x) { return x ? mod - x : 0; }
int qpow(int x, int y) {
	int ret = 1;
	for (; y; y >>= 1, x = (ll)x * x % mod)
	if (y & 1) ret = (ll)ret * x % mod;
	return ret;
}
namespace poly {
constexpr int g = 3, inv2 = (mod + 1) >> 1;
int pwg[N], inv[N];
inline int lg2(int x) { return x ? 31 - __builtin_clz(x) : -1; }
inline int getsz(int n) { return n ? 1 << (lg2(n - 1) + 1) : 0; }
void init() {
	inv[0] = inv[1] = 1;
	for (int i = 2; i < N; ++i)
	inv[i] = (ll)inv[mod % i] * (mod - mod / i) % mod;
	for (int h = 2; h <= N; h <<= 1) {
	int gn = qpow(g, (mod - 1) / h);
	pwg[h >> 1] = 1;
	for (int i = (h >> 1) + 1; i < h; ++i) pwg[i] = (ll)pwg[i - 1] * gn % mod;
	}
}
void dft(vector<int>& f) {
	int n = f.size();
	for (int h = n; h >= 2; h >>= 1) {
	for (int i = 0, p = h >> 1; i < n; i += h) {
		for (int j = i; j < i + p; ++j) {
		int u = f[j], v = f[j + p];
		f[j] = sum(u, v), f[j + p] = (ll)pwg[j - i + p] * dif(u, v) % mod;
		}
	}
	}
}
void idft(vector<int>& f) {
	int n = f.size();
	for (int h = 2; h <= n; h <<= 1) {
	for (int i = 0, p = h >> 1; i < n; i += h) {
		for (int j = i; j < i + p; ++j) {
		int t = (ll)pwg[j - i + p] * f[j + p] % mod;
		f[j + p] = dif(f[j], t), add(f[j], t);
		}
	}
	}
	reverse(f.begin() + 1, f.end());
	for (int i = 0, k = qpow(n, mod - 2); i < n; ++i) f[i] = (ll)f[i] * k % mod;
}
struct poly_t : vector<int> {
	using vector<int>::vector;
#define a (*this)
	poly_t mul_xn(int n) const {
	auto b = a;
	return b.insert(b.begin(), n, 0), b;
	}
	poly_t mod_xn(int n) const {
	if (n >= (int)size()) return a;
	return poly_t({a.begin(), a.begin() + n});
	}
	poly_t div_xn(int n) const {
	if (n >= (int)size()) return {};
	return poly_t({a.begin() + n, a.end()});
	}
	poly_t operator-() const {
	auto b = a;
	for (auto& it : b) it = neg(it);
	return b;
	}
	poly_t& operator+=(const poly_t& rhs) {
	if (size() < rhs.size()) resize(rhs.size());
	for (int i = 0; i < (int)rhs.size(); ++i) add(a[i], rhs[i]);
	return a;
	}
	poly_t& operator-=(const poly_t& rhs) {
	if (size() < rhs.size()) resize(rhs.size());
	for (int i = 0; i < (int)rhs.size(); ++i) sub(a[i], rhs[i]);
	return a;
	}
	poly_t& operator*=(poly_t rhs) {
	if (!size() || !rhs.size()) return a = {};
	int n = size() + rhs.size() - 1, sz = getsz(n);
	if (size() < 20 || rhs.size() < 20) {
		poly_t ret(n);
		for (int i = 0; i < (int)size(); ++i)
		for (int j = 0; j < (int)rhs.size(); ++j)
			ret[i + j] = (ret[i + j] + (ll)a[i] * rhs[j]) % mod;
		return a = ret;
	} else {
		resize(sz), rhs.resize(sz), dft(a), dft(rhs);
		for (int i = 0; i < sz; ++i) a[i] = (ll)a[i] * rhs[i] % mod;
		return idft(a), resize(n), a;
	}
	}
	friend poly_t operator+(poly_t lhs, const poly_t& rhs) { return lhs += rhs; }
	friend poly_t operator-(poly_t lhs, const poly_t& rhs) { return lhs -= rhs; }
	friend poly_t operator*(poly_t lhs, const poly_t& rhs) { return lhs *= rhs; }
	poly_t derivation() const {
	if (empty()) return {};
	poly_t ret(size() - 1);
	for (int i = 1; i < (int)size(); ++i) ret[i - 1] = (ll)i * a[i] % mod;
	return ret;
	}
	poly_t integral() const {
	if (empty()) return {0};
	poly_t ret(size() + 1);
	for (int i = 0; i < (int)size(); ++i) ret[i + 1] = (ll)inv[i + 1] * a[i] % mod;
	return ret;
	}
	poly_t inverse(int n) const {
	n = getsz(n);
	poly_t ret{qpow(a[0], mod - 2)};
	for (int k = 2; k <= n; k <<= 1)
		ret *= (poly_t{2} - ret * mod_xn(k)).mod_xn(k);
	return ret.mod_xn(n);
	}
	poly_t log(int n) const {
	assert(a[0] == 1);
	return (derivation() * inverse(n)).integral().mod_xn(n);
	}
	poly_t exp(int n) const {
	assert(a[0] == 0), n = getsz(n);
	poly_t ret{1};
	for (int k = 2; k <= n; k <<= 1)
		ret *= (poly_t{1} - ret.log(k) + mod_xn(k));
	return ret.mod_xn(n);
	}
#undef a
};
struct _ { _() { init(); }} __;
} // namespace poly
using poly::poly_t;
} // namespace grader_namespace

void fastmul(int *a, int *b, int *c, int n) {
	using namespace grader_namespace;
	poly_t f = poly_t{a, a + n + 1} * poly_t{b, b + n + 1};
	copy(f.begin(), f.begin() + n + 1, c);
}

void fastexp(int *a, int *b, int n) {
	using namespace grader_namespace;
	poly_t f = poly_t{a, a + n + 1}.exp(n + 1);
	copy(f.begin(), f.begin() + n + 1, b);
}

void fastln(int *a, int *b, int n) {
	using namespace grader_namespace;
	poly_t f = poly_t{a, a + n + 1}.log(n + 1);
	copy(f.begin(), f.begin() + n + 1, b);
}

void fastinv(int *a, int *b, int n) {
	using namespace grader_namespace;
	poly_t f = poly_t{a, a + n + 1}.inverse(n + 1);
	copy(f.begin(), f.begin() + n + 1, b);
}
int n,m,a[200005],b[200005];

// 用于封装二维多项式的结构体
struct Poly2D {
	int Dx, Dy; // x 的最大可能次数为 Dx, y 的最大可能次数为 Dy
	vector<int> data;
	
	int get(int i, int j) const{
		if (i > Dx || j > Dy) return 0;
		return data[i * (Dy + 1) + j];
	}
	
	void set(int i, int j, int val) {
		data[i * (Dy + 1) + j] = val;
	}
};
// 核心的二元多项式乘法，降维压位成一维
Poly2D multiply(const Poly2D& A, const Poly2D& B, int limit_x, int limit_y) {
	int max_Dy = A.Dy + B.Dy;
	int K = max_Dy + 1; // 压位步长，确保不会发生 y 的跨界进位
	int max_Dx = A.Dx + B.Dx;
	if (max_Dx > limit_x) max_Dx = limit_x;
	
	// req_n 是压位后的一维多项式最高需要保留的次数
	int req_n = max_Dx * K + min(max_Dy, limit_y);
	
	vector<int> flat_A(req_n + 1, 0);
	for (int i = 0; i <= A.Dx; ++i) {
		for (int j = 0; j <= A.Dy; ++j) {
			if (i * K + j <= req_n) {
				flat_A[i * K + j] = A.get(i, j);
			}
		}
	}
	
	vector<int> flat_B(req_n + 1, 0);
	for (int i = 0; i <= B.Dx; ++i) {
		for (int j = 0; j <= B.Dy; ++j) {
			if (i * K + j <= req_n) {
				flat_B[i * K + j] = B.get(i, j);
			}
		}
	}
	
	vector<int> flat_C(req_n + 1, 0);
	// 直接调用提供的 1D fastmul 接口
	fastmul(flat_A.data(), flat_B.data(), flat_C.data(), req_n);
	
	Poly2D C;
	C.Dx = max_Dx;
	C.Dy = min(max_Dy, limit_y);
	C.data.assign((C.Dx + 1) * (C.Dy + 1), 0);
	
	for (int i = 0; i <= C.Dx; ++i) {
		for (int j = 0; j <= C.Dy; ++j) {
			if (i * K + j <= req_n) {
				C.set(i, j, flat_C[i * K + j]);
			}
		}
	}
	return C;
}

// 主算法接口
void get_coefficients(int n, int *F, int *ans) {
	// 初始化 P(x, y) = 1
	Poly2D P;
	P.Dx = 0; P.Dy = 0;
	P.data = {1};
	
	// 初始化 Q(x, y) = 1 - y F(x)
	Poly2D Q;
	Q.Dx = n; Q.Dy = 1;
	Q.data.assign((n + 1) * 2, 0);
	Q.set(0, 0, 1);
	for (int i = 1; i <= n; ++i) {
		// F[i] 前带负号，加上模数转换为正数
		Q.set(i, 1, (mod - F[i] % mod) % mod);
	}
	
	int curr_N = n;
	
	// Bostan-Mori 核心倍增循环
	while (curr_N > 0) {
		// 构造 Q(-x, y)
		Poly2D Q_neg = Q;
		for (int i = 1; i <= Q.Dx; i += 2) {
			for (int j = 0; j <= Q.Dy; ++j) {
				int val = Q.get(i, j);
				if (val > 0) Q_neg.set(i, j, mod - val);
			}
		}
		
		// V(x, y) = P(x, y) * Q(-x, y)
		Poly2D V = multiply(P, Q_neg, curr_N, n);
		// W(x, y) = Q(x, y) * Q(-x, y)
		Poly2D W = multiply(Q, Q_neg, curr_N, n);
		
		int next_N = curr_N / 2;
		int rem = curr_N % 2; // 判断提取奇数项还是偶数项
		
		// 提取 P 的下一层 (根据当前要求的 N 是奇是偶)
		Poly2D next_P;
		next_P.Dx = next_N;
		next_P.Dy = V.Dy;
		next_P.data.assign((next_P.Dx + 1) * (next_P.Dy + 1), 0);
		
		for (int i = rem; i <= V.Dx; i += 2) {
			for (int j = 0; j <= V.Dy; ++j) {
				next_P.set(i / 2, j, V.get(i, j));
			}
		}
		P = next_P;
		
		// 提取 Q 的下一层 (Q(x)Q(-x) 一定只包含偶数次项)
		Poly2D next_Q;
		next_Q.Dx = next_N;
		next_Q.Dy = W.Dy;
		next_Q.data.assign((next_Q.Dx + 1) * (next_Q.Dy + 1), 0);
		
		for (int i = 0; i <= W.Dx; i += 2) {
			for (int j = 0; j <= W.Dy; ++j) {
				next_Q.set(i / 2, j, W.get(i, j));
			}
		}
		Q = next_Q;
		
		curr_N = next_N;
	}
	
	// 当 curr_N 归零时，相当于求 [x^0] P(x,y)/Q(x,y)。
	// 由于 F[0]=0，可以严谨证明任何时刻的 Q(0, y) 都恒为 1，
	// 所以答案矩阵就直接存在了最后的 P(0, y) 中。
	for (int i = 1; i <= n; ++i) {
		ans[i] = P.get(0, i);
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read();
	get_coefficients(n,a,b);
	for(int i=1;i<=n;i++) printf("%d ",b[i]);
	puts("");
}
int main(){
	// #ifdef LOCAL
	// 	assert(freopen("test10.in","r",stdin));
	// 	assert(freopen("test10.ans","w",stdout));
	// #endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}