// created time: 2026-10-08 15:02:11
// #pragma GCC optimize("Ofast,unroll-loops")
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
#pragma once
#pragma GCC target("avx2")
#include <bits/stdc++.h>
#include <immintrin.h>
namespace FastAVX{
using u32 = uint32_t;
using u64 = uint64_t;
using i32 = int32_t;
using i64 = int64_t;
using idt = std::size_t;

#define RC(T, x) reinterpret_cast<T>(x)
#define LG2(x) std::__lg(x)
#define CRZ(x) __builtin_ctzll(x)

using u32x8 = __attribute((vector_size(32))) u32;
using u64x4 = __attribute((vector_size(32))) u64;
using I256 = __m256i;
using I256u = __m256i_u;

template <bool align = true> inline u32x8 load(const void *data) {
    if (align) return (u32x8)_mm256_load_si256((const I256 *)data);
    return (u32x8)_mm256_loadu_si256((const I256u *)data);
}
template <bool align = true> inline void store(u32x8 x, void *data) {
    if (align) _mm256_store_si256((I256 *)data, RC(I256, x));
    else _mm256_storeu_si256((I256u *)data, RC(I256, x));
}

inline u64x4 fus_mul(u32x8 x, u32x8 y) { return RC(u64x4, _mm256_mul_epu32(RC(I256, x), RC(I256, y))); }
inline u32x8 swaplohi128(u32x8 x) { return (u32x8)_mm256_permute2x128_si256(RC(I256, x), RC(I256, x), 1); }
template <int typ> inline u32x8 shuffle(u32x8 x) { return RC(u32x8, _mm256_shuffle_epi32(RC(I256, x), typ)); }
template <int typ> inline u32x8 blend(u32x8 x, u32x8 y) { return RC(u32x8, _mm256_blend_epi32(RC(I256, x), RC(I256, y), typ)); }
inline u32x8 &x8(u32 *data) { return *((u32x8 *)data); }
inline const u32x8 &x8(const u32 *data) { return *((const u32x8 *)data); }
inline u32x8 min_u32(u32x8 x, u32x8 y) { return RC(u32x8, _mm256_min_epu32(RC(I256, x), RC(I256, y))); }
inline u32x8 padd(u32 x) { return (u32x8){x, x, x, x, x, x, x, x}; }


template<u32 M>struct NTT{
static constexpr u32 Mod=M;
static constexpr u32 get_nr(u32 MOD) {
    u32 Iv = 2u - MOD;
    for (int i = 0; i < 4; ++i) Iv *= 2 - MOD * Iv;
    return Iv;
}
static constexpr u32 pr_rt(u32 MOD) {
    u32 qed = 0, n = MOD - 1, d[11] = {};
    for (u32 i = 2; i * i <= n; ++i) {
        if (n % i == 0) { d[qed++] = i; do { n /= i; } while (n % i == 0); }
    }
    if (n > 1) { d[qed++] = n; }
    for (u32 g = 2, r = 0;; ++g) {
        for (u32 i = 0; i < qed; ++i) {
            u32 b = (MOD - 1) / d[i], a = g;
            for (r = 1; b; b >>= 1, a = u64(a) * a % MOD) { b & 1 ? r = u64(r) * a % MOD : r; }
            if (r == 1) break;
        }
        if (r != 1) return g;
    }
}
static constexpr idt bcl(idt x) { return ((x < 2) ? 1 : idt(2) << LG2(x - 1)); }

static constexpr u32 R = (-M) % M, E = 0, nR = M - R, M2 = M * 2, iv = get_nr(M), niv = -iv, R2 = (-u64(M)) % M;
static constexpr u32 shrk(u32 x) { return x < M ? x : x - M; }
static constexpr u32 dil2(u32 x) { return x >> 31 ? x + M2 : x; }
static constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * niv) * M) >> 32; }
static constexpr u32 reduce_s(u64 x) { u32 r = (x >> 32) - ((u64(u32(x) * iv) * M) >> 32); return r >> 31 ? r + M : r; }

static constexpr u32 add(u32 x, u32 y) { return dil2(x + y - M2); }
static constexpr u32 sub(u32 x, u32 y) { return dil2(x - y); }
static constexpr u32 mul(u32 x, u32 y) { return reduce(u64(x) * y); }
static constexpr u32 mul_s(u32 x, u32 y) { return reduce_s(u64(x) * y); }
static constexpr u32 qpw(u32 a, u32 b, u32 r = R) {
    for (; b; b >>= 1, a = mul(a, a)) { if (b & 1) r = mul(r, a); }
    return r;
}
static constexpr u32 poly_inv(u32 x) { return qpw(x, M - 2); }
static constexpr u32 neg(u32 x) { return M2 - x; }
static constexpr u32 in(u32 x) { return mul(x, R2); }
static constexpr u32 in_s(u32 x) { return mul_s(x, R2); }
static constexpr u32 out(u32 x) { u32 r = (x + (u64(x * niv) * M)) >> 32; return r < M ? r : r - M; }
static constexpr bool equals(u32 x, u32 y) { return out(x) == out(y); }
static constexpr void clr(u32 &x) { x = E; }

#define Rx8 padd(R)
#define Ex8 padd(E)
#define Mx8 padd(M)
#define M2x8 padd(M2)
#define nivx8 padd(niv)

static inline u32x8 shrk(u32x8 x) { return min_u32(x, x - Mx8); }
static inline u32x8 dil2(u32x8 x) { return min_u32(x, x + M2x8); }
static inline u32x8 shrk2(u32x8 x) { return min_u32(x, x - M2x8); }
static inline u32x8 add(u32x8 x, u32x8 y) { return shrk2(x + y); }
static inline u32x8 sub(u32x8 x, u32x8 y) { return dil2(x - y); }
static inline u32x8 mul(u32x8 x, u32x8 y) {
    u32x8 z = nivx8 * x * y;
    return blend<0xaa>(RC(u32x8, (fus_mul(x, y) + fus_mul(z, Mx8)) >> 32), RC(u32x8, (fus_mul(u32x8(u64x4(x) >> 32), u32x8(u64x4(y) >> 32)) + fus_mul(shuffle<0xf5>(z), Mx8))));
}
static inline u32x8 qpw(u32x8 y, u32 b) {
    u32x8 x = y, r = Rx8;
    for (; b; x = mul(x, x), b >>= 1) { if (b & 1) { r = mul(r, x); } }
    return r;
}
static inline u32x8 poly_inv(u32x8 x) { return qpw(x, M - 2); }
static inline u32x8 mul_s(u32x8 x, u32x8 y) { return shrk(mul(x, y)); }
static inline u32x8 neg(u32x8 x) { return M2x8 - x; }
static inline void clr(u32x8 &x) { x = Ex8; }

static constexpr u32 _Amul(u32 a, u32 b, u32 c) { return mul(a + b, c); }
static constexpr u32 _Smul(u32 a, u32 b, u32 c) { return mul(a - b + M2, c); }
static inline u32x8 _LMadd(u32x8 x, u32x8 y) { return x + y; }
static inline u32x8 _LMsub(u32x8 x, u32x8 y) { return x - y + M2x8; }
static inline u32x8 _LMnot(u32x8 x) { return min_u32(x, x - M2x8); }
static inline u32x8 _Amul(u32x8 a, u32x8 b, u32x8 c) { return mul(a + b, c); }
static inline u32x8 _Smul(u32x8 a, u32x8 b, u32x8 c) { return mul(a - b + M2x8, c); }
template <int typ> static inline u32x8 Neg(u32x8 x) { return blend<typ>(x, M2x8 - x); }
static inline u32x8 powXx8(u32 X) {
    u32 X2 = mul_s(X, X), X3 = mul_s(X2, X), X4 = mul_s(X3, X), X5 = mul_s(X4, X), X6 = mul_s(X5, X), X7 = mul_s(X6, X);
    return (u32x8){R, X, X2, X3, X4, X5, X6, X7};
}
static constexpr u32 _ADmul(u32 a, u32 b, u32 c, u32 d) { return reduce_s(u64(a) * b + u64(c) * d); }
static inline u32x8 _ADmul(u32x8 a, u32x8 b, u32x8 c, u32x8 d) {
    u32x8 z = nivx8 * (a * b + c * d);
    return shrk(blend<0xaa>(RC(u32x8, (fus_mul(a, b) + fus_mul(c, d) + fus_mul(z, Mx8)) >> 32), RC(u32x8, (fus_mul(u32x8(u64x4(a) >> 32), u32x8(u64x4(b) >> 32)) + fus_mul(u32x8(u64x4(c) >> 32), u32x8(u64x4(d) >> 32)) + fus_mul(shuffle<0xf5>(z), Mx8)))));
}

template <class F, class Op> static inline void vec_op(F f, idt n, Op op) {
    idt i = 0;
    for (; i + 7 < n; i += 8) { op(x8(f + i)); }
    for (; i < n; ++i) { op(f[i]); }
}
template <class F, class G, class Op> static inline void vec_op(F f, G g, idt n, Op op) {
    idt i = 0;
    for (; i + 7 < n; i += 8) { op(x8(f + i), x8(g + i)); }
    for (; i < n; ++i) { op(f[i], g[i]); }
}
template <class F, class G, class H, class Op> static inline void vec_op(F f, G g, H h, idt n, Op op) {
    idt i = 0;
    for (; i + 7 < n; i += 8) { op(x8(f + i), x8(g + i), x8(h + i)); }
    for (; i < n; ++i) { op(f[i], g[i], h[i]); }
}
template <class F, class G, class H, class O, class Op> static inline void vec_op(F f, G g, H h, O o, idt n, Op op) {
    idt i = 0;
    for (; i + 7 < n; i += 8) { op(x8(f + i), x8(g + i), x8(h + i), x8(o + i)); }
    for (; i < n; ++i) { op(f[i], g[i], h[i], o[i]); }
}

static constexpr u32 _g = in_s(pr_rt(M));

static constexpr int lml = CRZ(M - 1);
struct P_R_Tab {
    u32 t[lml + 1];
    P_R_Tab(u32 G) : t{} {
        t[lml] = shrk(qpw(G, (M - 1) >> lml));
        for (int i = lml; i > 0; --i) { t[i - 1] = mul_s(t[i], t[i]); }
    }
    u32 operator[](int i) const { return t[i]; }
};
struct ntt_info_base4x8 {
    u32 rt3[lml - 2], rt3_I[lml - 2];
    u32x8 rt4ix8[lml - 3], rt4ix8_I[lml - 3];
    ntt_info_base4x8(const P_R_Tab &w, const P_R_Tab &wI) : rt3{}, rt3_I{}, rt4ix8{}, rt4ix8_I{} {
        u32 pr = R, pr_I = R;
        for (int i = 0; i < lml - 2; pr = mul(pr, wI[i + 3]), pr_I = mul(pr_I, w[i + 3]), ++i) {
            rt3[i] = mul_s(pr, w[i + 3]), rt3_I[i] = mul_s(pr_I, wI[i + 3]);
        }
        pr = R, pr_I = R;
        for (int i = 0; i < lml - 3; pr = mul(pr, wI[i + 4]), pr_I = mul(pr_I, w[i + 4]), ++i) {
            rt4ix8[i] = powXx8(mul_s(pr, w[i + 4])), rt4ix8_I[i] = powXx8(mul_s(pr_I, wI[i + 4]));
        }
    }
};
inline static const P_R_Tab rt1 = {_g}, rt1_I = {poly_inv(_g)};
inline static const ntt_info_base4x8 iab4 = {rt1, rt1_I};
inline static const u32 Img = rt1[2];
#define Imgx8 padd(Img)

template <bool strict = false> static inline void dif_2(u32 &x, u32 &y) {
    u32 sum = add(x, y), diff = sub(x, y);
    x = sum, y = diff;
    if (strict) { x = shrk(x), y = shrk(y); }
}
template <bool strict = false> static inline void dif_4(u32 &x, u32 &y, u32 &z, u32 &w) {
    u32 a = sub(x, z), b = _Smul(y, w, Img);
    x = add(x, z), y = add(y, w), z = add(a, b), w = sub(a, b), a = add(x, y), b = sub(x, y), x = a, y = b;
    if (strict) { x = shrk(x), y = shrk(y), z = shrk(z), w = shrk(w); }
}
template <bool strict = false> static inline void vec_dif_base4(u32x8 *f, idt n) {
    idt L = n >> 1;
    if (CRZ(n) & 1) {
        for (idt j = 0; j < L; ++j) {
            auto x = f[j], y = f[j + L];
            f[j] = _LMadd(x, y), f[j + L] = _LMsub(x, y);
        }
        L >>= 1;
    }
    L >>= 1;
    for (idt l = L << 2, k; L; l = L, L >>= 2) {
        u32 r = R, r2 = R, r3 = nR;
        k = 1;
        for (auto i = f; i != (f + n); r = mul_s(r, iab4.rt3[CRZ(k++)]), r2 = mul_s(r, r), r3 = mul_s(r2, neg(r)), i += l) {
            auto rx8 = padd(r), r2x8 = padd(r2), r3x8 = padd(r3);
            for (auto F0 = i, F1 = F0 + L, F2 = F1 + L, F3 = F2 + L; F3 != i + l; ++F0, ++F1, ++F2, ++F3) {
                auto f0 = _LMnot(*F0), f1 = mul(*F1, rx8), f2 = mul(*F2, r2x8), f3 = mul(*F3, r3x8);
                auto f1f3 = _Amul(f1, f3, Imgx8), f02 = add(f0, f2), f13 = sub(f1, f3), f_02 = sub(f0, f2);
                *F0 = _LMadd(f02, f13), *F1 = _LMsub(f02, f13), *F2 = _LMadd(f_02, f1f3), *F3 = _LMsub(f_02, f1f3);
            }
        }
    }
    const u32x8 pr2 = {R, R, R, Img, R, R, R, Img}, pr4 = {R, R, R, R, R, rt1[3], Img, mul_s(Img, rt1[3])};
    auto rx8 = Rx8;
    for (idt i = 0; i < n; ++i) {
        auto &fi = f[i];
        fi = mul(fi, rx8);
        rx8 = mul_s(rx8, iab4.rt4ix8[CRZ(~i)]);
        fi = _Amul(Neg<0xf0>(fi), swaplohi128(fi), pr4);
        fi = _Amul(Neg<0xcc>(fi), shuffle<0x4e>(fi), pr2);
        fi = sub(shuffle<0xb1>(fi), Neg<0x55>(fi));
        if (strict) { fi = shrk(fi); }
    }
}
template <u32 fx> static inline void dit_2(u32 &x, u32 &y) {
    const u32 iv2 = mul_s(poly_inv(in(2)), fx);
    u32 a = _Amul(x, y, iv2), b = _Smul(x, y, iv2);
    x = a, y = b;
}
template <u32 fx> static inline void dit_4(u32 &x, u32 &y, u32 &z, u32 &w) {
    const u32 iv4 = mul_s(poly_inv(in(4)), fx), dust = mul_s(iv4, Img);
    u32 a = _Amul(x, y, iv4), b = _Smul(x, y, iv4);
    x = a, y = b, a = _Amul(z, w, iv4), b = _Smul(w, z, dust), z = sub(x, a), w = sub(y, b), x = add(x, a), y = add(y, b);
}
template <u32 fx> static inline void vec_dit_base4(u32x8 *f, idt n) {
    idt L = 1;
    const u32 nR2 = in_s(nR), M8 = (M - 1) >> 3;
    const u32x8 pr2 = {nR2, nR2, nR2, in(Img), nR2, nR2, nR2, in(Img)}, pr4 = {fx, fx, fx, fx, fx, mul_s(fx, rt1_I[3]), mul_s(fx, rt1_I[2]), mul_s(fx, mul_s(rt1_I[2], rt1_I[3]))};
    auto rx8 = padd(M8 >> CRZ(n));
    for (idt i = 0; i < n; rx8 = mul_s(rx8, iab4.rt4ix8_I[CRZ(++i)])) {
        auto &fi = f[i];
        fi = _Amul(Neg<0xaa>(fi), shuffle<0xb1>(fi), pr2);
        fi = _Amul(Neg<0xcc>(fi), shuffle<0x4e>(fi), pr4);
        fi = _Amul(Neg<0xf0>(fi), swaplohi128(fi), rx8);
    }
    for (idt l = L << 2, k; L < (n >> 1); L = l, l <<= 2) {
        u32 r = R, r2 = R, r3 = R;
        k = 1;
        for (auto i = f; i != (f + n); r = mul_s(r, iab4.rt3_I[CRZ(k++)]), r2 = mul_s(r, r), r3 = mul_s(r2, r), i += l) {
            auto rx8 = padd(r), r2x8 = padd(r2), r3x8 = padd(r3);
            for (auto F0 = i, F1 = F0 + L, F2 = F1 + L, F3 = F2 + L; F3 != i + l; ++F0, ++F1, ++F2, ++F3) {
                auto f0 = *F0, f1 = *F1, f2 = neg(*F2), f3 = *F3;
                auto f2f3 = _Amul(f3, f2, Imgx8), f01 = add(f0, f1), f23 = sub(f2, f3), f_01 = sub(f0, f1);
                *F0 = sub(f01, f23), *F1 = _Amul(f_01, f2f3, rx8), *F2 = _Amul(f01, f23, r2x8), *F3 = _Smul(f_01, f2f3, r3x8);
            }
        }
    }
    if (CRZ(n) & 1) {
        for (idt j = 0; j < L; ++j) {
            auto x = f[j], y = f[j + L];
            f[j] = add(x, y), f[j + L] = sub(x, y);
        }
    }
}
template <bool strict = false> static inline void dif(u32 *A, idt lim) {
    switch (lim) {
    case 1: break;
    case 2: dif_2<strict>(A[0], A[1]); break;
    case 4: dif_4<strict>(A[0], A[1], A[2], A[3]); break;
    default: vec_dif_base4<strict>((u32x8 *)A, lim >> 3);
    }
}
template <u32 fx = R> static inline void dit(u32 *A, idt lim) {
    switch (lim) {
    case 1: if (!equals(fx, R)) { A[0] = mul(A[0], fx); } break;
    case 2: dit_2<fx>(A[0], A[1]); break;
    case 4: dit_4<fx>(A[0], A[1], A[2], A[3]); break;
    default: vec_dit_base4<fx>((u32x8 *)A, lim >> 3);
    }
}

static void dot(u32*f,const u32*g,idt n){
 idt i=0;
 for(;i+8<=n;i+=8)x8(f+i)=mul(x8(f+i),x8(g+i));
 for(;i<n;i++)f[i]=mul(f[i],g[i]);
}
};
#undef Rx8
#undef Ex8
#undef Mx8
#undef M2x8
#undef nivx8
#undef Imgx8
#undef RC
#undef LG2
#undef CRZ
} // namespace FastAVX
namespace Poly1000000007{
using namespace FastAVX;
using ll=long long;
constexpr int MOD=1000000007;
using N0=FastAVX::NTT<167772161>;
using N1=FastAVX::NTT<469762049>;
using N2=FastAVX::NTT<998244353>;

struct Buffer{
 uint32_t *p=nullptr;
 int cap=0;
 ~Buffer(){free(p);}
 void reserve(int n){
  if(n<=cap)return;
  free(p);cap=n;
  void *q=nullptr;
  if(posix_memalign(&q,32,(size_t)n*4))abort();
  p=(uint32_t*)q;
 }
};
inline int qpow(int a,int b){
 int s=1;
 for(;b;b>>=1,a=(ll)a*a%MOD)if(b&1)s=(ll)s*a%MOD;
 return s;
}
inline int CRT(int a,int b,int c){
 constexpr int P0=167772161,P1=469762049,P2=998244353;
 constexpr int iv01=104391568,iv012=575867115,p01m=564826938;
 int t=b-a;
 if(t<0)t+=P1;
 int x=(ll)t*iv01%P1;
 ll v=a+(ll)P0*x;
 int z=v%P2;
 t=c-z;
 if(t<0)t+=P2;
 int y=(ll)t*iv012%P2;
 return (v%MOD+(ll)p01m*y)%MOD;
}
template<class K>inline void conv1(const int*a,const int*b,int n,int len,uint32_t*f,uint32_t*g,bool same){
 for(int i=0;i<=n;i++)f[i]=K::in(a[i]%K::Mod);
 memset(f+n+1,0,(size_t)(len-n-1)*4);
 K::dif(f,len);
 if(same){
  for(int i=0;i<len;i++)f[i]=K::mul(f[i],f[i]);
 }else{
  for(int i=0;i<=n;i++)g[i]=K::in(b[i]%K::Mod);
  memset(g+n+1,0,(size_t)(len-n-1)*4);
  K::dif(g,len);
  K::dot(f,g,len);
 }
 K::dit(f,len);
}
inline void mul(const int*a,const int*b,int*c,int n){
 if(n<0)return;
 if(n<=48){
  int t[49]={};
  for(int i=0;i<=n;i++)for(int j=0;i+j<=n;j++)t[i+j]=(t[i+j]+(ll)a[i]*b[j])%MOD;
  memcpy(c,t,4*(n+1));return;
 }
 int len=1;
 while(len<2*n+1)len<<=1;
 static Buffer F,A,R0,R1;
 F.reserve(len);A.reserve(len);R0.reserve(n+1);R1.reserve(n+1);
 bool same=(a==b);
 conv1<N0>(a,b,n,len,F.p,A.p,same);
 for(int i=0;i<=n;i++)R0.p[i]=N0::out(F.p[i]);
 conv1<N1>(a,b,n,len,F.p,A.p,same);
 for(int i=0;i<=n;i++)R1.p[i]=N1::out(F.p[i]);
 conv1<N2>(a,b,n,len,F.p,A.p,same);
 for(int i=0;i<=n;i++)c[i]=CRT(R0.p[i],R1.p[i],N2::out(F.p[i]));
}
template<class K>inline void invmul1(const int*a,const int*f,int sz,int k,int len,uint32_t*F,uint32_t*A){
 for(int i=0;i<k;i++)F[i]=K::in(f[i]%K::Mod);
 memset(F+k,0,(size_t)(len-k)*4);
 for(int i=0;i<sz;i++)A[i]=K::in(a[i]%K::Mod);
 memset(A+sz,0,(size_t)(len-sz)*4);
 K::dif(F,len);K::dif(A,len);K::dot(A,F,len);K::dit(A,len);
}
template<class K>inline void invmul2(const int*e,int sz,int k,int len,uint32_t*F,uint32_t*A){
 memset(A,0,(size_t)k*4);
 for(int i=k;i<sz;i++)A[i]=K::in(e[i]%K::Mod);
 memset(A+sz,0,(size_t)(len-sz)*4);
 K::dif(A,len);K::dot(A,F,len);K::dit(A,len);
}
inline void inv(const int*a,int*b,int n){
 if(n<0)return;
 std::vector<int>f(n+1),e(n+1);
 f[0]=qpow(a[0],MOD-2);
 static Buffer F0,F1,F2,A,R0,R1;
 for(int k=1;k<=n;k<<=1){
  int len=k<<1,sz=std::min(len,n+1),cnt=sz-k;
  F0.reserve(len);F1.reserve(len);F2.reserve(len);A.reserve(len);
  R0.reserve(cnt);R1.reserve(cnt);
  invmul1<N0>(a,f.data(),sz,k,len,F0.p,A.p);
  for(int i=k;i<sz;i++)R0.p[i-k]=N0::out(A.p[i]);
  invmul1<N1>(a,f.data(),sz,k,len,F1.p,A.p);
  for(int i=k;i<sz;i++)R1.p[i-k]=N1::out(A.p[i]);
  invmul1<N2>(a,f.data(),sz,k,len,F2.p,A.p);
  for(int i=k;i<sz;i++){
   int x=CRT(R0.p[i-k],R1.p[i-k],N2::out(A.p[i]));
   e[i]=x?MOD-x:0;
  }
  invmul2<N0>(e.data(),sz,k,len,F0.p,A.p);
  for(int i=k;i<sz;i++)R0.p[i-k]=N0::out(A.p[i]);
  invmul2<N1>(e.data(),sz,k,len,F1.p,A.p);
  for(int i=k;i<sz;i++)R1.p[i-k]=N1::out(A.p[i]);
  invmul2<N2>(e.data(),sz,k,len,F2.p,A.p);
  for(int i=k;i<sz;i++)f[i]=CRT(R0.p[i-k],R1.p[i-k],N2::out(A.p[i]));
 }
 memcpy(b,f.data(),(size_t)(n+1)*4);
}
inline std::vector<int> invnum={0,1};
inline void initinv(int n){
 while((int)invnum.size()<=n){
  int i=invnum.size();
  invnum.push_back((ll)(MOD-MOD/i)*invnum[MOD%i]%MOD);
 }
}
inline void ln(const int*a,int*b,int n){
 if(n<0)return;
 if(n==0){b[0]=0;return;}
 std::vector<int>f(n),d(n),t(n);
 inv(a,f.data(),n-1);
 for(int i=1;i<=n;i++)d[i-1]=(ll)a[i]*i%MOD;
 mul(d.data(),f.data(),t.data(),n-1);
 initinv(n);b[0]=0;
 for(int i=1;i<=n;i++)b[i]=(ll)t[i-1]*invnum[i]%MOD;
}
inline void exp(const int*a,int*b,int n){
 if(n<0)return;
 std::vector<int>f(n+1),l(n+1),g(n+1),t(n+1);
 f[0]=1;
 for(int k=1;k<=n;k<<=1){
  int m=std::min(k<<1,n+1);
  ln(f.data(),l.data(),m-1);
  g[0]=1;
  for(int i=1;i<m;i++){
   g[i]=a[i]-l[i];if(g[i]<0)g[i]+=MOD;
  }
  mul(f.data(),g.data(),t.data(),m-1);
  memcpy(f.data(),t.data(),(size_t)m*4);
 }
 memcpy(b,f.data(),(size_t)(n+1)*4);
}
}
inline void fastmul(int*a,int*b,int*c,int n){Poly1000000007::mul(a,b,c,n);}
inline void fastinv(int*a,int*b,int n){Poly1000000007::inv(a,b,n);}
inline void fastln(int*a,int*b,int n){Poly1000000007::ln(a,b,n);}
inline void fastexp(int*a,int*b,int n){Poly1000000007::exp(a,b,n);}

int inv[1000005],pw2[1000005];
int lst[1000005],b[1000005],phi[1000005],ans[1000005];

void procedure(){
	printf("%d\n",ans[read()]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	const int N = 1e6;
	for(int n=1;n<=N;n++) phi[n]=n;
	for(int n=1;n<=N;n++)
		for(int m=2*n;m<=N;m+=n) phi[m]-=phi[n];

	b[0]=b[1]=1;

	inv[1]=1;
	for(int i=2;i<=N+1;i++)
		inv[i]=(ll)(mod-mod/i)*inv[mod%i]%mod;
	for(int n=2;n<=N;n++)
		b[n]=((ull)(6*n-3)*b[n-1]+(ull)(mod-n+2)*b[n-2])%mod*inv[n+1]%mod;
	for(int n=N;n>=1;n--)lst[n]=b[n-1],b[n]=mod-b[n-1];
	b[0]=lst[0]=1;

	fastln(b,b,N);
	for(int n=1;n<=N;n++)b[n]=mod-b[n];

	pw2[0]=1;
	for(int i=1;i<=N;i++)
		addmod(pw2[i]=pw2[i-1]*2);
	for(int i=1;i<=N;i++){
		int cf=(ull)pw2[i]*i%mod*b[i]%mod;
		for(int d=2;i*d<=N;d++){
			int n=i*d;
			ans[n]=(ans[n]+(ull)phi[d]*cf)%mod;
		}
		ans[i]=(ans[i]+(i!=2?(ull)pw2[i]*lst[i-1]:2))%mod;
	}
	for(int i=1;i<=N;i++)
		ans[i]=(ull)ans[i]*inv[i]%mod;
	ll T=read();
	while(T--) procedure();
	return 0;
}