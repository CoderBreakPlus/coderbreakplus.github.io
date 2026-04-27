// created time: 2026-04-27 15:22:41
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
namespace grader_namespace {
using namespace std;
using ll = long long;
using ull = unsigned long long;
using i128 = __int128_t;
using u128 = __uint128_t;
bool Mbe;
constexpr int N = 1 << 21, mod = 998244353;
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


int n,k,a[500005],b[500005];
char s[500005];

int p[500005],q[500005];
void procedure(){
	n=read(),k=read();
	scanf("%s",s+1);
	int ok=0;
	for(int i=1;i<n;i++){
		if((s[i]=='0')!=(s[i+1]=='0'))ok+=s[i]+s[i+1]-'0'-'0';
	}
	for(int i=1;i<=n;i++)b[i]=ok;
	
	for(int w=1;w<=n;w++){
		for(int i=w;i<n;i+=w){
			if((s[i]=='0')!=(s[i+1]=='0'))b[w]-=s[i]+s[i+1]-'0'-'0';
		}
	}

	// for(int i=1;i<=n;i++)cout<<b[i]<<" ";cout<<endl;

	for(int i=0;i<=n;i++)p[i]=q[i]=0;
	for(int i=1;i<=n;i++){
		if(s[i]=='0')p[i]=1;else q[n-i]=s[i]-'0';
	}
	fastmul(p,q,a,n);
	for(int i=1;i<=n;i++)b[i]+=a[n-i];

	for(int i=0;i<=n;i++)p[i]=q[i]=0;
	for(int i=1;i<=n;i++){
		if(s[i]!='0')p[i]=s[i]-'0';else q[n-i]=1;
	}
	fastmul(p,q,a,n);
	for(int i=1;i<=n;i++)b[i]+=a[n-i];
	// for(int i=1;i<=n;i++)cout<<b[i]<<" ";cout<<endl;
	
	sort(b+1,b+n+1);
	printf("%d\n",b[n-k+1]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}