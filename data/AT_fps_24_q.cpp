// created time: 2026-08-12 16:52:43
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

namespace Poly {

typedef unsigned long long ull;
const int mod = 998244353, G = 3, GI = 332748118;

namespace math {
  mt19937_64 rng(chrono::steady_clock().now().time_since_epoch().count());
  uniform_int_distribution<int> uid(0, mod - 1);

  int I;

  struct Complex {
    int a, b;

    Complex() {}
    Complex(int a, int b): a(a), b(b) {}

    inline Complex operator*(const Complex &rhs) const {
      return Complex(((ull)a * rhs.a + (ull)b * rhs.b % mod * I) % mod, ((ull)a * rhs.b + (ull)b * rhs.a) % mod);
    }
  };

  inline Complex qpow(Complex a, int b) { Complex res(1, 0); while (b) {
    if (b & 1) { res = res * a; } a = a * a; b >>= 1; } return res; }

  inline int qpow(int a, int b) { int res = 1; while (b) {
    if (b & 1) { res = (ull)res * a % mod; } a = (ull)a * a % mod; b >>= 1; } return res; }

  inline bool check(int a) {
    return qpow(a, (mod - 1) >> 1) != mod - 1;
  }

  inline int modsqrt(int a) {
    int b = 0;
    I = 0;
    while (check(I)) {
      b = uid(rng);
      I = ((ull)b * b - a + mod) % mod;
    }
    int res = qpow(Complex(b, 1), (mod + 1) >> 1).a;
    return min(res, mod - res);
  }
}

static vector<int> ninv = vector<int> {0, 1};

class poly {
private:
  vector<int> data;

public:
  inline void print(string sep = " ", string end = "\n") const {
    for (int i = 0; i < (int)data.size(); ++i) {
      cout << data[i];
      if (i != (int)data.size() - 1) {
        cout << sep;
      }
    }
    cout << end;
  }

  poly(const size_t &len = size_t(0)) { data = vector<int> (len); }
  poly(const vector<int> &a) { data = a; }

  inline void clear() { data.clear(); }
  inline void resize(const size_t &len, const int &val = 0) { data.resize(len, val); }
  inline size_t size() const { return data.size(); }

  inline int &operator[](const size_t &b) { return data[b]; }
  inline const int &operator[](const size_t &b) const { return data[b]; }

  inline poly operator*(const poly &h) const;
  inline poly &operator*=(const poly &h);
  inline poly operator*(const int &h) const;
  inline poly &operator*=(const int &h);
  inline poly operator/(const int &h) const;
  inline poly &operator/=(const int &h);
  inline poly operator/(const poly &h) const;
  inline poly &operator/=(const poly &h);
  inline poly operator%(const poly &h) const;
  inline poly &operator%=(const poly &h);
  inline poly operator+(const poly &h) const;
  inline poly &operator+=(const poly &h);
  inline poly operator-(const poly &h) const;
  inline poly &operator-=(const poly &h);
  inline poly operator<<(const size_t &b) const;
  inline poly &operator<<=(const size_t &b);
  inline poly operator>>(const size_t &b) const;
  inline poly &operator>>=(const size_t &b);

  inline bool operator==(const poly &h) const;
  inline bool operator!=(const poly &h) const;

  inline poly ogf2egf() const;
  inline poly egf2ogf() const;
  inline poly square() const;
  inline poly square(const size_t &b) const;
  inline poly inv() const;
  inline poly inv(const size_t &b) const;
  inline poly rev() const;
  inline poly rev(const size_t &b) const;
  inline poly Der() const;
  inline poly Der(const size_t &b) const;
  inline poly Int() const;
  inline poly Int(const size_t &b) const;
  inline poly log() const;
  inline poly log(const size_t &b) const;
  inline poly exp() const;
  inline poly exp(const size_t &b) const;
  inline poly sqrt() const;
  inline poly sqrt(const size_t &b) const;
  inline poly exsqrt() const;
  inline poly exsqrt(const size_t &b) const;
  inline poly pow(const int &h) const;
  inline poly pow(const int &h, const size_t &b) const;
};

inline void addmod(int &x) { (x >= mod) && (x -= mod); }
inline int qpow(int a, int b) { int res = 1; while (b) {
  if (b & 1) { res = (ull)res * a % mod; } a = (ull)a * a % mod; b >>= 1; } return res; }
inline int qinv(int a) { return qpow(a, mod - 2); }
inline int modsqrt(int a) { return math::modsqrt(a); }

inline void NTT(vector<int> &a, int len, int g) {
  vector<int> rev(len);
  vector<ull> f(len);
  for (int i = 0; i < len; ++i) {
    rev[i] = (rev[i >> 1] >> 1) | ((i & 1) ? (len >> 1) : 0);
    f[i] = a[rev[i]];
  }
  for (int i = 1; i < len; i <<= 1) {
    int wn = qpow(g, (mod - 1) / (i << 1));
    vector<int> w(i);
    w[0] = 1;
    for (int j = 1; j < i; ++j) {
      w[j] = (ull)w[j - 1] * wn % mod;
    }
    for (int j = 0; j < len; j += (i << 1)) {
      for (int k = 0; k < i; ++k) {
        ull s = f[j + k], t = f[i + j + k] * w[k] % mod;
        f[j + k] = s + t;
        f[i + j + k] = s - t + mod;
      }
    }
    if (i == (1 << 16)) {
      for (int j = 0; j < len; ++j) {
        f[j] %= mod;
      }
    }
  }
  for (int j = 0; j < len; ++j) {
    a[j] = f[j] % mod;
  }
}

inline poly poly::operator*(const poly &h) const {
  int len = 1;
  while (len < (int)(size() + h.size() - 1)) {
    len <<= 1;
  }
  vector<int> f(data), g(h.data);
  f.resize(len), g.resize(len);
  NTT(f, len, G), NTT(g, len, G);
  for (int i = 0; i < len; ++i) {
    f[i] = (ull)f[i] * g[i] % mod;
  }
  NTT(f, len, GI);
  int ilen = qinv(len);
  for (int i = 0; i < len; ++i) {
    f[i] = (ull)f[i] * ilen % mod;
  }
  f.resize(size() + h.size() - 1);
  return f;
}

inline poly &poly::operator*=(const poly &h) {
  return *this = *this * h;
}

inline poly poly::operator*(const int &h) const {
  vector<int> f(data);
  for (int i = 0; i < (int)size(); ++i) {
    f[i] = (ull)f[i] * h % mod;
  }
  return f;
}

inline poly &poly::operator*=(const int &h) {
  for (int i = 0; i < (int)size(); ++i) {
    data[i] = (ull)data[i] * h % mod;
  }
  return *this;
}

inline poly poly::operator/(const int &h) const {
  int invh = qinv(h);
  vector<int> f(data);
  for (int i = 0; i < (int)size(); ++i) {
    f[i] = (ull)f[i] * invh % mod;
  }
  return f;
}

inline poly &poly::operator/=(const int &h) {
  int invh = qinv(h);
  for (int i = 0; i < (int)size(); ++i) {
    data[i] = (ull)data[i] * invh % mod;
  }
  return *this;
}

inline poly poly::operator/(const poly &h) const {
  if (size() < h.size()) {
    return poly();
  }
  poly res = (this -> rev() * h.rev().inv(size() - h.size() + 1));
  res.resize(size() - h.size() + 1);
  return res.rev();
}

inline poly &poly::operator/=(const poly &h) {
  return *this = *this / h;
}

inline poly poly::operator%(const poly &h) const {
  poly res = *this - *this / h * h;
  res.resize(h.size() - 1);
  return res;
}

inline poly &poly::operator%=(const poly &h) {
  return *this = *this % h;
}

inline poly poly::operator+(const poly &h) const {
  vector<int> f(data);
  if (size() < h.size()) {
    f.resize(h.size());
  }
  for (int i = 0; i < (int)h.size(); ++i) {
    addmod(f[i] += h[i]);
  }
  return f;
}

inline poly &poly::operator+=(const poly &h) {
  if (size() < h.size()) {
    data.resize(h.size());
  }
  for (int i = 0; i < (int)h.size(); ++i) {
    addmod(data[i] += h[i]);
  }
  return *this;
}

inline poly poly::operator-(const poly &h) const {
  vector<int> f(data);
  if (size() < h.size()) {
    f.resize(h.size());
  }
  for (int i = 0; i < (int)h.size(); ++i) {
    addmod(f[i] += mod - h[i]);
  }
  return f;
}

inline poly &poly::operator-=(const poly &h) {
  if (size() < h.size()) {
    data.resize(h.size());
  }
  for (int i = 0; i < (int)h.size(); ++i) {
    addmod(data[i] += mod - h[i]);
  }
  return *this;
}

inline poly poly::operator<<(const size_t &b) const {
  vector<int> f(size() + b);
  for (int i = 0; i < (int)size(); ++i) {
    f[i + b] = data[i];
  }
  return f;
}

inline poly &poly::operator<<=(const size_t &b) {
  return *this = *this << b;
}

inline poly poly::operator>>(const size_t &b) const {
  if (size() <= b) {
    return poly();
  }
  vector<int> f(size() - b);
  for (int i = b; i < (int)size(); ++i) {
    f[i - b] = data[i];
  }
  return f;
}

inline poly &poly::operator>>=(const size_t &b) {
  return *this = *this >> b;
}

inline bool poly::operator==(const poly &h) const {
  if (size() != h.size()) {
    return false;
  }
  for (int i = 0; i < (int)size(); ++i) {
    if (data[i] != h[i]) {
      return false;
    }
  }
  return true;
}

inline bool poly::operator!=(const poly &h) const {
  if (size() != h.size()) {
    return true;
  }
  for (int i = 0; i < (int)size(); ++i) {
    if (data[i] != h[i]) {
      return true;
    }
  }
  return false;
}

inline poly poly::ogf2egf() const {
  poly f(size());
  if (ninv.size() < size()) {
    int oinv = ninv.size();
    ninv.resize(size());
    for (int i = oinv; i < (int)size(); ++i) {
      int t = mod / i;
      ninv[i] = (ull)(mod - t) * ninv[mod - t * i] % mod;
    }
  }
  f[0] = 1;
  for (int i = 1; i < (int)size(); ++i) {
    f[i] = (ull)f[i - 1] * ninv[i] % mod;
  }
  for (int i = 0; i < (int)size(); ++i) {
    f[i] = (ull)f[i] * data[i] % mod;
  }
  return f;
}

inline poly poly::egf2ogf() const {
  poly f(size());
  f[0] = 1;
  for (int i = 1; i < (int)size(); ++i) {
    f[i] = (ull)f[i - 1] * i % mod;
  }
  for (int i = 0; i < (int)size(); ++i) {
    f[i] = (ull)f[i] * data[i] % mod;
  }
  return f;
}

inline poly poly::square() const {
  int len = 1;
  while (len < (int)(size() << 1)) {
    len <<= 1;
  }
  vector<int> f(data);
  f.resize(len);
  NTT(f, len, G);
  for (int i = 0; i < len; ++i) {
    f[i] = (ull)f[i] * f[i] % mod;
  }
  NTT(f, len, GI);
  int ilen = qinv(len);
  for (int i = 0; i < len; ++i) {
    f[i] = (ull)f[i] * ilen % mod;
  }
  f.resize((size() << 1) - 1);
  return f;
}

inline poly poly::square(const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.square();
}

inline poly poly::inv() const {
  vector<int> f, res(1);
  res[0] = qinv(data[0]);
  int len = 1;
  while (len < (int)size()) {
    len <<= 1;
    f.resize(len << 1), res.resize(len << 1);
    for (int i = 0; i < len; ++i) {
      if (i >= (int)size()) {
        break;
      }
      f[i] = data[i];
    }
    NTT(f, len << 1, G);
    NTT(res, len << 1, G);
    for (int i = 0; i < (len << 1); ++i) {
      int t = (ull)f[i] * res[i] % mod * res[i] % mod;
      addmod(res[i] <<= 1);
      addmod(res[i] += mod - t);
    }
    NTT(res, len << 1, GI);
    int ilen = qinv(len << 1);
    for (int i = 0; i < len; ++i) {
      res[i] = (ull)res[i] * ilen % mod;
    }
    for (int i = len; i < (len << 1); ++i) {
      res[i] = 0;
    }
  }
  res.resize(size());
  return res;
}

inline poly poly::inv(const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.inv();
}

inline poly poly::rev() const {
  vector<int> f(data);
  reverse(f.begin(), f.end());
  return f;
}

inline poly poly::rev(const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.rev();
}

inline poly poly::Der() const {
  vector<int> f(size());
  for (int i = 0; i < (int)size() - 1; ++i) {
    f[i] = (ull)data[i + 1] * (i + 1) % mod;
  }
  return f;
}

inline poly poly::Der(const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.Der();
}

inline poly poly::Int() const {
  vector<int> f(size());
  if (ninv.size() < size()) {
    int oinv = ninv.size();
    ninv.resize(size());
    for (int i = oinv; i < (int)size(); ++i) {
      int t = mod / i;
      ninv[i] = (ull)(mod - t) * ninv[mod - t * i] % mod;
    }
  }
  for (int i = 1; i < (int)size(); ++i) {
    f[i] = (ull)data[i - 1] * ninv[i] % mod;
  }
  return f;
}

inline poly poly::Int(const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.Int();
}

inline poly poly::log() const {
  poly res = (Der() * inv()).Int();
  res.resize(size());
  return res;
}

inline poly poly::log(const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.log();
}

inline poly poly::exp() const {
  poly f, res(1);
  res[0] = 1;
  int len = 1;
  while (len < (int)size()) {
    len <<= 1;
    f.resize(len), res.resize(len);
    for (int i = 0; i < len; ++i) {
      if (i >= (int)size()) {
        break;
      }
      f[i] = data[i];
    }
    res = res - res * (res.log() - f);
    res.resize(len);
  }
  res.resize(size());
  return res;
}

inline poly poly::exp(const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.exp();
}

inline poly poly::sqrt() const {
  poly f, res(1);
  res[0] = 1;
  int len = 1;
  while (len < (int)size()) {
    len <<= 1;
    f.resize(len), res.resize(len);
    for (int i = 0; i < len; ++i) {
      if (i >= (int)size()) {
        break;
      }
      f[i] = data[i];
    }
    res = (f + res.square()) * (res * 2).inv();
    res.resize(len);
  }
  res.resize(size());
  return res;
}

inline poly poly::sqrt(const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.sqrt();
}

inline poly poly::exsqrt() const {
  poly f, res(1);
  res[0] = modsqrt(data[0]);
  int len = 1;
  while (len < (int)size()) {
    len <<= 1;
    f.resize(len), res.resize(len);
    for (int i = 0; i < len; ++i) {
      if (i >= (int)size()) {
        break;
      }
      f[i] = data[i];
    }
    res = (f + res.square()) * (res * 2).inv();
    res.resize(len);
  }
  res.resize(size());
  return res;
}

inline poly poly::exsqrt(const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.exsqrt();
}

inline poly poly::pow(const int &h) const {
  poly f(data);
  return (f.log() * h).exp();
}

inline poly poly::pow(const int &h, const size_t &b) const {
  poly f(data);
  f.resize(b);
  return f.pow(h);
}

}

using Poly::poly;

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

int n,m,K,a[100005],b[100005];
poly sa,sb,ans,pa[100005],pb[100005];

void solvea(int l,int r){
	if(l==r){
		pa[l]=(vector<int>){1,mod-a[l]};
		return;
	}
	int mid=(l+r)>>1;
	solvea(l,mid);solvea(mid+1,r);
	pa[l]=pa[l]*pa[mid+1];
}
void solveb(int l,int r){
	if(l==r){
		pb[l]=(vector<int>){1,mod-b[l]};
		return;
	}
	int mid=(l+r)>>1;
	solveb(l,mid);solveb(mid+1,r);
	pb[l]=pb[l]*pb[mid+1];
}
void procedure(){
	n=read(),m=read(),K=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();

	// for(int k=0;k<=K;k++){
	// 	for(int i=1;i<=n;i++) addmod(sa[k]+=qpow(a[i],k));
	// 	for(int i=1;i<=m;i++) addmod(sb[k]+=qpow(b[i],k));
	// }

	solvea(1,n); sa=pa[1];
	solveb(1,m); sb=pb[1];
	// sa.resize(K+1,0),sb.resize(K+1,0);
	sa=sa.log(K+1);
	sb=sb.log(K+1);

	for(int i=0;i<=K;i++)sa[i]=(ull)sa[i]*(mod-i)%mod,sb[i]=(ull)sb[i]*(mod-i)%mod;
	sa[0]=n,sb[0]=m;

	// sa.print(),sb.print();
	for(int i=0;i<=K;i++)sa[i]=(ull)sa[i]*inv[i]%mod,sb[i]=(ull)sb[i]*inv[i]%mod;

	// solvea(1,n),pa[1].resize(K+1);
	// sa=pa[1].log();

	ans=sa*sb;

	// ans.print();
	int ev=INV((ull)n*m%mod);
	for(int k=1;k<=K;k++) printf("%d\n",(ull)ans[k]*fac[k]%mod*ev%mod);
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