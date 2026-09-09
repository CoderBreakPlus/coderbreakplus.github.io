// created time: 2026-09-09 16:10:48
#include"board.h"
#include<bits/stdc++.h>
#ifdef LOCAL
	#include"grader.cpp"
#endif
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353;
ll p;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}

inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}

inline ll qpow3(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=(__int128)ans*base%(p-1);
		base=(__int128)base*base%(p-1); b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

using u64 = uint64_t;
using u128 = __uint128_t;

struct Barrett {
    u64 m;
    u128 mu; 

    Barrett(u64 mod) : m(mod), mu(mod == 1 ? 0 : ((u128)-1) / mod) {}

    static u128 mulhi(u128 a, u128 b) {
        u64 a0 = (u64)a, a1 = (u64)(a >> 64);
        u64 b0 = (u64)b, b1 = (u64)(b >> 64);
        u128 p00 = (u128)a0 * b0, p01 = (u128)a0 * b1;
        u128 p10 = (u128)a1 * b0, p11 = (u128)a1 * b1;
        u128 t = (p00 >> 64) + (u64)p01 + (u64)p10;
        u128 c = (t >> 64) + (p01 >> 64) + (p10 >> 64) + (u64)p11;
        return (((p11 >> 64) + (c >> 64)) << 64) | (u64)c;
    }

    u64 reduce(u128 x) const {
        if (m == 1) return 0;
        u128 q = mulhi(x, mu);
        u128 r = x - q * m;
        if (r >= m) r -= m;
        return (u64)r;
    }
};
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

poly seq[1000005]; int m;
const int N = 1000000;
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

void solve(int l,int r){
	if(l==r)return;
	int mid=(l+r)>>1;
	solve(l,mid),solve(mid+1,r);
	seq[l]=seq[l]*seq[mid+1];
	seq[mid+1].clear();
}
ll tmp[65];
int board(int n,ll PP,vector<ll> a,vector<ll> s){
	p=PP;

	Barrett br0(p), br1(p-1);

	auto qpow2 = [&](ll a,ll b){
		ll ans=1, base=a;
		while(b){
			if(b&1) ans=br0.reduce((u128)ans*base);
			base=br0.reduce((u128)base*base);
			b>>=1;
		}
		return ans;
	};

	for(ll i=0;i<=60;i++) tmp[i]=qpow3(2,1ll<<i);
	map<ll,pair<int,int>>mp;
	map<ll,int>cnt;
	for(ll &x: a) x=(x+1)%p;

	ll cf=1;
	for(ll &x: s){
		x=(x+1)%p;
		cnt[x]++;
	}
	for(auto [a,b]: cnt) cf=(ull)cf*inv[b]%mod;

	ll k=__builtin_ctzll(p-1);
	for(ll x: a){
		ll cur=qpow2(x,(p-1)>>k);
		while(cur!=1){
			cur=br0.reduce((u128)cur*cur);
			x=br0.reduce((u128)x*x);
		}
		mp[x].fi++;
	}
	for(ll x: s){
		ll cur=qpow2(x,(p-1)>>k);
		while(cur!=1){
			cur=br0.reduce((u128)cur*cur);
			x=br0.reduce((u128)x*x);
		}
		mp[x].se++;
	}

	m=0;
	ll val;
	for(auto [v,p]: mp){
		val=v;
		auto [a,b]=p;
		seq[++m].resize(min(a,b)+1);
		for(int i=0;i<=min(a,b);i++)
			seq[m][i]=((ull)binom(a,i)*perm(b,i)%mod);
	}
	solve(1,m);

	int ans=0;
	for(int i=0;i<seq[1].size();i++){
		ans=(ans + (ull)seq[1][i]*fac[n-i]%mod*qpow(2,n-i)%mod*qpow(mod-1,i))%mod;
	}

	if(qpow2(val,2)==val||qpow2(val,4)==val)ans=fac[n];
	ans=(ull)ans*cf%mod;
	return ans;
}
void init(int a,int b){ math_init(); }