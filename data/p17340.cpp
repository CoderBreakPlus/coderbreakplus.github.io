// created time: 2026-09-07 08:49:42
// #pragma GCC optimize("O3,unroll-loops")
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
const int NN = 1005;
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
#pragma GCC target("avx2")
#include <immintrin.h>
namespace grader_namespace {
using u32 = uint32_t;
using u64 = uint64_t;
using i32 = int32_t;
using i64 = int64_t;
using idt = std::size_t;

#define RC(T, x) reinterpret_cast<T>(x)
#define LG2(x) std::__lg(x)
#define CRZ(x) __builtin_ctzll(x)

constexpr u32 M = 998244353;
constexpr idt pool_MB = 80;
unsigned char _mem_pool[pool_MB << 20], *_now = _mem_pool;

template <idt align> inline bool is_align(const void *mem) {
    return (RC(idt, mem) & (align - 1)) == 0;
}
template <idt align> inline void *to_align(void *mem) {
    return RC(void *, idt((RC(idt, mem) + align - 1) & (-align)));
}

struct pl_alcor {
    unsigned char *t;
    pl_alcor() : t(_now) {}
    ~pl_alcor() { _now = t; }
    template <idt al = 1> void *raw(idt n) {
        void *p = to_align<al>(_now);
        return _now = ((unsigned char *)p) + n, p;
    }
};

template <class T, idt al> struct wrap_pl_alcor : pl_alcor {
    T *operator()(idt n) { return (T *)pl_alcor::raw<al>(n * sizeof(T)); }
};
using _alcr = wrap_pl_alcor<u32, 32>;

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

constexpr u32 get_nr(u32 MOD) {
    u32 Iv = 2u - MOD;
    for (int i = 0; i < 4; ++i) Iv *= 2 - MOD * Iv;
    return Iv;
}
constexpr u32 pr_rt(u32 MOD) {
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
constexpr idt bcl(idt x) { return ((x < 2) ? 1 : idt(2) << LG2(x - 1)); }

constexpr u32 R = (-M) % M, E = 0, nR = M - R, M2 = M * 2, iv = get_nr(M), niv = -iv, R2 = (-u64(M)) % M;
constexpr u32 shrk(u32 x) { return x < M ? x : x - M; }
constexpr u32 dil2(u32 x) { return x >> 31 ? x + M2 : x; }
constexpr u32 reduce(u64 x) { return (x + u64(u32(x) * niv) * M) >> 32; }
constexpr u32 reduce_s(u64 x) { u32 r = (x >> 32) - ((u64(u32(x) * iv) * M) >> 32); return r >> 31 ? r + M : r; }

constexpr u32 add(u32 x, u32 y) { return dil2(x + y - M2); }
constexpr u32 sub(u32 x, u32 y) { return dil2(x - y); }
constexpr u32 mul(u32 x, u32 y) { return reduce(u64(x) * y); }
constexpr u32 mul_s(u32 x, u32 y) { return reduce_s(u64(x) * y); }
constexpr u32 qpw(u32 a, u32 b, u32 r = R) {
    for (; b; b >>= 1, a = mul(a, a)) { if (b & 1) r = mul(r, a); }
    return r;
}
constexpr u32 poly_inv(u32 x) { return qpw(x, M - 2); }
constexpr u32 neg(u32 x) { return M2 - x; }
constexpr u32 in(u32 x) { return mul(x, R2); }
constexpr u32 in_s(u32 x) { return mul_s(x, R2); }
constexpr u32 out(u32 x) { u32 r = (x + (u64(x * niv) * M)) >> 32; return r < M ? r : r - M; }
constexpr bool equals(u32 x, u32 y) { return out(x) == out(y); }
constexpr void clr(u32 &x) { x = E; }

#define Rx8 padd(R)
#define Ex8 padd(E)
#define Mx8 padd(M)
#define M2x8 padd(M2)
#define nivx8 padd(niv)

inline u32x8 shrk(u32x8 x) { return min_u32(x, x - Mx8); }
inline u32x8 dil2(u32x8 x) { return min_u32(x, x + M2x8); }
inline u32x8 shrk2(u32x8 x) { return min_u32(x, x - M2x8); }
inline u32x8 add(u32x8 x, u32x8 y) { return shrk2(x + y); }
inline u32x8 sub(u32x8 x, u32x8 y) { return dil2(x - y); }
inline u32x8 mul(u32x8 x, u32x8 y) {
    u32x8 z = nivx8 * x * y;
    return blend<0xaa>(RC(u32x8, (fus_mul(x, y) + fus_mul(z, Mx8)) >> 32), RC(u32x8, (fus_mul(u32x8(u64x4(x) >> 32), u32x8(u64x4(y) >> 32)) + fus_mul(shuffle<0xf5>(z), Mx8))));
}
inline u32x8 qpw(u32x8 y, u32 b) {
    u32x8 x = y, r = Rx8;
    for (; b; x = mul(x, x), b >>= 1) { if (b & 1) { r = mul(r, x); } }
    return r;
}
inline u32x8 poly_inv(u32x8 x) { return qpw(x, M - 2); }
inline u32x8 mul_s(u32x8 x, u32x8 y) { return shrk(mul(x, y)); }
inline u32x8 neg(u32x8 x) { return M2x8 - x; }
inline void clr(u32x8 &x) { x = Ex8; }

constexpr u32 _Amul(u32 a, u32 b, u32 c) { return mul(a + b, c); }
constexpr u32 _Smul(u32 a, u32 b, u32 c) { return mul(a - b + M2, c); }
inline u32x8 _LMadd(u32x8 x, u32x8 y) { return x + y; }
inline u32x8 _LMsub(u32x8 x, u32x8 y) { return x - y + M2x8; }
inline u32x8 _LMnot(u32x8 x) { return min_u32(x, x - M2x8); }
inline u32x8 _Amul(u32x8 a, u32x8 b, u32x8 c) { return mul(a + b, c); }
inline u32x8 _Smul(u32x8 a, u32x8 b, u32x8 c) { return mul(a - b + M2x8, c); }
template <int typ> inline u32x8 Neg(u32x8 x) { return blend<typ>(x, M2x8 - x); }
inline u32x8 powXx8(u32 X) {
    u32 X2 = mul_s(X, X), X3 = mul_s(X2, X), X4 = mul_s(X3, X), X5 = mul_s(X4, X), X6 = mul_s(X5, X), X7 = mul_s(X6, X);
    return (u32x8){R, X, X2, X3, X4, X5, X6, X7};
}
constexpr u32 _ADmul(u32 a, u32 b, u32 c, u32 d) { return reduce_s(u64(a) * b + u64(c) * d); }
inline u32x8 _ADmul(u32x8 a, u32x8 b, u32x8 c, u32x8 d) {
    u32x8 z = nivx8 * (a * b + c * d);
    return shrk(blend<0xaa>(RC(u32x8, (fus_mul(a, b) + fus_mul(c, d) + fus_mul(z, Mx8)) >> 32), RC(u32x8, (fus_mul(u32x8(u64x4(a) >> 32), u32x8(u64x4(b) >> 32)) + fus_mul(u32x8(u64x4(c) >> 32), u32x8(u64x4(d) >> 32)) + fus_mul(shuffle<0xf5>(z), Mx8)))));
}

template <class F, class Op> inline void vec_op(F f, idt n, Op op) {
    idt i = 0;
    for (; i + 7 < n; i += 8) { op(x8(f + i)); }
    for (; i < n; ++i) { op(f[i]); }
}
template <class F, class G, class Op> inline void vec_op(F f, G g, idt n, Op op) {
    idt i = 0;
    for (; i + 7 < n; i += 8) { op(x8(f + i), x8(g + i)); }
    for (; i < n; ++i) { op(f[i], g[i]); }
}
template <class F, class G, class H, class Op> inline void vec_op(F f, G g, H h, idt n, Op op) {
    idt i = 0;
    for (; i + 7 < n; i += 8) { op(x8(f + i), x8(g + i), x8(h + i)); }
    for (; i < n; ++i) { op(f[i], g[i], h[i]); }
}
template <class F, class G, class H, class O, class Op> inline void vec_op(F f, G g, H h, O o, idt n, Op op) {
    idt i = 0;
    for (; i + 7 < n; i += 8) { op(x8(f + i), x8(g + i), x8(h + i), x8(o + i)); }
    for (; i < n; ++i) { op(f[i], g[i], h[i], o[i]); }
}

constexpr u32 _g = in_s(pr_rt(M));
namespace raw_ntt {
constexpr int lml = CRZ(M - 1);
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
const P_R_Tab rt1 = {_g}, rt1_I = {poly_inv(_g)};
const ntt_info_base4x8 iab4 = {rt1, rt1_I};
const u32 Img = rt1[2];
#define Imgx8 padd(Img)

template <bool strict = false> inline void dif_2(u32 &x, u32 &y) {
    u32 sum = add(x, y), diff = sub(x, y);
    x = sum, y = diff;
    if (strict) { x = shrk(x), y = shrk(y); }
}
template <bool strict = false> inline void dif_4(u32 &x, u32 &y, u32 &z, u32 &w) {
    u32 a = sub(x, z), b = _Smul(y, w, Img);
    x = add(x, z), y = add(y, w), z = add(a, b), w = sub(a, b), a = add(x, y), b = sub(x, y), x = a, y = b;
    if (strict) { x = shrk(x), y = shrk(y), z = shrk(z), w = shrk(w); }
}
template <bool strict = false> inline void vec_dif_base4(u32x8 *f, idt n) {
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
template <u32 fx> inline void dit_2(u32 &x, u32 &y) {
    const u32 iv2 = mul_s(poly_inv(in(2)), fx);
    u32 a = _Amul(x, y, iv2), b = _Smul(x, y, iv2);
    x = a, y = b;
}
template <u32 fx> inline void dit_4(u32 &x, u32 &y, u32 &z, u32 &w) {
    const u32 iv4 = mul_s(poly_inv(in(4)), fx), dust = mul_s(iv4, Img);
    u32 a = _Amul(x, y, iv4), b = _Smul(x, y, iv4);
    x = a, y = b, a = _Amul(z, w, iv4), b = _Smul(w, z, dust), z = sub(x, a), w = sub(y, b), x = add(x, a), y = add(y, b);
}
template <u32 fx> inline void vec_dit_base4(u32x8 *f, idt n) {
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
template <bool strict = false> inline void dif(u32 *A, idt lim) {
    switch (lim) {
    case 1: break;
    case 2: dif_2<strict>(A[0], A[1]); break;
    case 4: dif_4<strict>(A[0], A[1], A[2], A[3]); break;
    default: vec_dif_base4<strict>((u32x8 *)A, lim >> 3);
    }
}
template <u32 fx = R> inline void dit(u32 *A, idt lim) {
    switch (lim) {
    case 1: if (!equals(fx, R)) { A[0] = mul(A[0], fx); } break;
    case 2: dit_2<fx>(A[0], A[1]); break;
    case 4: dit_4<fx>(A[0], A[1], A[2], A[3]); break;
    default: vec_dit_base4<fx>((u32x8 *)A, lim >> 3);
    }
}
}
using raw_ntt::dif;
using raw_ntt::dit;

template <class T> inline T *cpy(T *f, const T *g, idt n) { return (T *)memcpy(f, g, n * sizeof(T)); }
template <class T> inline T *clr(T *f, idt n) { return (T *)memset(f, 0, n * sizeof(T)); }
template <class T> inline T *rcpy(T *f, const T *g, idt n) { return std::reverse_copy(g, g + n, f), f; }
void dot(u32 *f, const u32 *g, idt n) { vec_op(f, g, n, [](auto &fi, auto &gi) { fi = mul(fi, gi); }); }
void dot(u32 *f, const u32 *g, const u32 *h, idt n) { vec_op(f, g, h, n, [](auto &fi, auto &gi, auto &hi) { return fi = mul(gi, hi); }); }
void add(u32 *f, const u32 *g, idt n) { vec_op(f, g, n, [](auto &fi, auto &gi) { fi = add(fi, gi); }); }
void add(u32 *f, const u32 *g, const u32 *h, idt n) { vec_op(f, g, h, n, [](auto &fi, auto &gi, auto &hi) { return fi = add(gi, hi); }); }
void sub(u32 *f, const u32 *g, idt n) { vec_op(f, g, n, [](auto &fi, auto &gi) { fi = sub(fi, gi); }); }
void sub(u32 *f, const u32 *g, const u32 *h, idt n) { vec_op(f, g, h, n, [](auto &fi, auto &gi, auto &hi) { return fi = sub(gi, hi); }); }
void adddot(u32 *a, const u32 *b, const u32 *c, const u32 *d, idt n) { vec_op(a, b, c, d, n, [](auto &A, auto &B, auto &C, auto &D) { A = _ADmul(A, B, C, D); }); }

void vec_multi_iv(u32x8 *f, const u32x8 *g, idt n) {
    if (n == 0) { return; }
    f[0] = g[0];
    for (idt i = 1; i < n; ++i) { f[i] = mul(f[i - 1], g[i]); }
    f[n - 1] = poly_inv(f[n - 1]);
    for (idt i = n - 1; i; --i) {
        u32x8 ivi = f[i];
        f[i] = mul(ivi, f[i - 1]), f[i - 1] = mul(ivi, g[i]);
    }
}
template <u32 fx = R> void conv(u32 *f, u32 *g, idt lim) { dif(f, lim), dif(g, lim), dot(f, g, lim), dit<fx>(f, lim); }

alignas(32) u32 Id_data[1 << 22];
alignas(32) u32 Iv_data[1 << 22];
idt Id_len = 0;
idt Iv_len = 0;

void rsv_Id(idt req) {
    idt r = std::max<idt>((req + 15) & ~15ULL, Id_len);
    if (r <= Id_len) return;
    idt l = std::max<idt>(Id_len, 8);
    for (idt i = Id_len; i < l; ++i) Id_data[i] = in(i);
    const auto va8 = padd(in(8));
    for (idt i = l; i < r; i += 8) { x8(Id_data + i) = add(x8(Id_data + i - 8), va8); }
    Id_len = r;
}

void rsv_Iv(idt req) {
    idt r = std::max<idt>((req + 15) & ~15ULL, Iv_len);
    if (r <= Iv_len) return;
    rsv_Id(r);
    idt l = Iv_len;
    if (l < 8) { x8(Iv_data) = poly_inv(x8(Id_data)), l = 8; }
    vec_multi_iv((u32x8 *)(Iv_data + l), (const u32x8 *)(Id_data + l), (r - l) >> 3);
    Iv_len = r;
}

void poly_inv_f(u32 *f, const u32 *g, idt n) {
    auto lim = bcl(n);
    _alcr alc;
    auto o = alc(lim), h = alc(lim);
    f[0] = poly_inv(g[0]);
    for (idt t = 2, m = 1, xl; t <= lim; m = t, t <<= 1) {
        xl = std::min(n, t), clr(cpy(o, g, xl) + xl, t - xl), clr(cpy(h, f, m) + m, m), conv(o, h, t);
        clr(o, m), dif(o, t), dot(o, h, t), dit<nR>(o, t), cpy(f + m, o + m, xl - m);
    }
}
void poly_quo(u32 *f, const u32 *g, const u32 *h, idt n) {
    _alcr alc;
    if (n <= 64) {
        idt lim = bcl(n << 1);
        auto o = alc(lim), s = alc(lim);
        poly_inv_f(o, h, n), clr(o + n, lim - n), cpy(s, g, n), clr(s + n, lim - n), conv(o, s, lim), cpy(f, o, n);
        return;
    }
    idt bn = bcl(n) >> 4, bt = (n + bn - 1) / bn, bn2 = bn << 1;
    auto o = alc(bn2), A = alc(bn2);
    poly_inv_f(o, h, bn), clr(o + bn, bn), clr(cpy(A, g, bn) + bn, bn), conv(A, o, bn2);
    auto nh = alc(bn2 * bt), Nf = alc(bn2 * (bt - 1)), nf = Nf;
    cpy(f, A, bn), clr(cpy(nh, h, bn) + bn, bn), dif(nh, bn2);
    for (idt ds = bn, xl; ds < n; ds += bn) {
        xl = std::min(bn, n - ds), nh += bn2;
        clr(cpy(nh, h + ds, xl) + xl, bn2 - xl), dif(nh, bn2);
        clr(cpy(nf, f + ds - bn, bn) + bn, bn), dif<true>(nf, bn2), clr(A, bn2), nf += bn2;
        auto nH = nh, nF = Nf, nH1 = nH - bn2;
        for (idt dj = 0; dj < ds; dj += bn, nH -= bn2, nH1 -= bn2, nF += bn2) {
            for (idt i = 0; i < bn; i += 8) { x8(A + i) = sub(x8(A + i), _Amul(x8(nH + i), x8(nH1 + i), x8(nF + i))); }
            for (idt i = bn; i < bn2; i += 8) { x8(A + i) = sub(x8(A + i), _Smul(x8(nH + i), x8(nH1 + i), x8(nF + i))); }
        }
        dit(A, bn2), clr(A + bn, bn), add(A, g + ds, xl), dif(A, bn2), dot(A, o, bn2), dit(A, bn2), cpy(f + ds, A, xl);
    }
}
void poly_ln(u32 *f, const u32 *g, idt n) {
    rsv_Id(n); rsv_Iv(n);
    dot(f, Id_data, g, n), poly_quo(f, f, g, n), dot(f, Iv_data, n);
}
template <bool c_inv> void __expi(u32 *f, u32 *h, const u32 *g, idt n) {
    f[0] = h[0] = R;
    if (n == 1) { return; }
    _alcr alc;
    auto lim = bcl(n);
    rsv_Id(lim); rsv_Iv(lim);
    auto id = Id_data, iv = Iv_data;
    auto o = alc(lim), A = alc(lim), B = alc(lim);
    clr(A, lim), A[0] = A[1] = R;
    for (idt t = 2, m = 1, xl; t <= lim; m = t, t <<= 1) {
        xl = std::min(n, t), dot(o, id, g, m), dif(o, m), dot(o, A, m), dit(o, m);
        dot(o + m, f, id, m);
        vec_op(o + m, o, m, [](auto &fi, auto &gi) { fi = sub(fi, gi), clr(gi); }), dif(o, t);
        clr(cpy(B, h, m) + m, m), dif(B, t), dot(o, B, t), dit(o, t), dot(clr(o, m) + m, iv + m, m);
        sub(o + m, g + m, xl - m), dif(o, t), dot(A, o, t), dit<nR>(A, t), cpy(f + m, A + m, xl - m);
        if (c_inv || (t != lim)) {
            cpy(A, f, m), dif(A, std::min(t << 1, lim)), dot(o, A, B, t), dit(o, t), clr(o, m);
            dif(o, t), dot(o, B, t), dit<nR>(o, t), cpy(h + m, o + m, xl - m);
        }
    }
}
void poly_exp(u32 *f, const u32 *g, idt n) {
    _alcr alc;
    if (n <= 64) { __expi<false>(f, alc(n), g, n); return; }
    idt bn = bcl(n) >> 4, bt = (n + bn - 1) / bn, bn2 = bn << 1;
    auto o = alc(bn2), h = alc(bn2);
    rsv_Id(n); rsv_Iv(n);
    auto id = Id_data, iv = Iv_data;
    __expi<true>(f, h, g, bn), clr(h + bn, bn), dif(h, bn2);
    auto ng = alc(bn2 * bt), Nf = alc(bn2 * (bt - 1)), nf = Nf;
    dot(ng, g, id, bn), clr(ng + bn, bn), dif(ng, bn2);
    for (idt ds = bn, xl; ds < n; ds += bn) {
        xl = std::min(bn, n - ds), ng += bn2, dot(ng, g + ds, id + ds, xl), clr(ng + xl, bn2 - xl), dif(ng, bn2);
        clr(cpy(nf, f + ds - bn, bn) + bn, bn), dif<true>(nf, bn2), clr(o, bn2), nf += bn2;
        auto nG = ng, nF = Nf, nG1 = nG - bn2;
        for (idt dj = 0; dj < ds; dj += bn, nG -= bn2, nG1 -= bn2, nF += bn2) {
            for (idt i = 0; i < bn; i += 8) { x8(o + i) = sub(x8(o + i), _Amul(x8(nG + i), x8(nG1 + i), x8(nF + i))); }
            for (idt i = bn; i < bn2; i += 8) { x8(o + i) = sub(x8(o + i), _Smul(x8(nG + i), x8(nG1 + i), x8(nF + i))); }
        }
        dit(o, bn2), clr(o + bn, bn), dif(o, bn2), dot(o, h, bn2), dit<nR>(o, bn2);
        dot(o, iv + ds, xl), clr(o + xl, bn2 - xl), dif(o, bn2), dot(o, Nf, bn2), dit(o, bn2), cpy(f + ds, o, xl);
    }
}
}

void fastmul(int *a, int *b, int *c, int n) {
    using namespace grader_namespace;
    int L = n + 1;
    int lim = bcl(L * 2 - 1);
    _alcr alc;
    auto f = alc(lim), g = alc(lim);
    for (int i = 0; i < L; ++i) f[i] = in(a[i]);
    for (int i = 0; i < L; ++i) g[i] = in(b[i]);
    clr(f + L, lim - L);
    clr(g + L, lim - L);
    conv(f, g, lim);
    for (int i = 0; i < L; ++i) c[i] = out(f[i]);
}


// Constant-factor helpers. They use the same NTT implementation as fastmul,
// but expose true operand lengths so long zero tails are not transformed.
static inline void fastmul_len_trunc(const int *a, int la, const int *b, int lb, int *c, int outn) {
    using namespace grader_namespace;
    if (la <= 0 || lb <= 0) { memset(c, 0, (outn + 1) * sizeof(int)); return; }
    if (lb == 1 && b[0] == 1) {
        int t = min(la, outn + 1);
        if (c != a) memcpy(c, a, t * sizeof(int));
        if (t <= outn) memset(c + t, 0, (outn + 1 - t) * sizeof(int));
        return;
    }
    if (la == 1 && a[0] == 1) {
        int t = min(lb, outn + 1);
        if (c != b) memcpy(c, b, t * sizeof(int));
        if (t <= outn) memset(c + t, 0, (outn + 1 - t) * sizeof(int));
        return;
    }
    int plen = la + lb - 1, lim = bcl(plen);
    _alcr alc; auto f = alc(lim), g = alc(lim);
    for (int i = 0; i < la; ++i) f[i] = in(a[i]);
    for (int i = 0; i < lb; ++i) g[i] = in(b[i]);
    clr(f + la, lim - la); clr(g + lb, lim - lb);
    conv(f, g, lim);
    int take = min(outn + 1, plen);
    for (int i = 0; i < take; ++i) c[i] = out(f[i]);
    if (take <= outn) memset(c + take, 0, (outn + 1 - take) * sizeof(int));
}

static inline void fastsqr_len(const int *a, int la, int *c, int outn) {
    using namespace grader_namespace;
    if (la <= 0) {
        memset(c, 0, (outn + 1) * sizeof(int));
        return;
    }
    int plen = la + la - 1;
    int lim = bcl(plen);
    _alcr alc;
    auto f = alc(lim);
    for (int i = 0; i < la; ++i) f[i] = in(a[i]);
    clr(f + la, lim - la);
    dif(f, lim);
    dot(f, f, lim);
    dit(f, lim);
    int take = min(outn + 1, plen);
    for (int i = 0; i < take; ++i) c[i] = out(f[i]);
    if (take <= outn) memset(c + take, 0, (outn + 1 - take) * sizeof(int));
}

static inline void fastmul2_same_a_len(
    const int *a, int la,
    const int *b, int lb, int *c,
    const int *d, int ld, int *e,
    int outn
) {
    using namespace grader_namespace;
    int mx = max(lb, ld);
    if (la <= 0 || mx <= 0) {
        memset(c, 0, (outn + 1) * sizeof(int));
        memset(e, 0, (outn + 1) * sizeof(int));
        return;
    }
    int plen = la + mx - 1;
    int lim = bcl(plen);
    _alcr alc;
    auto f = alc(lim), g = alc(lim), h = alc(lim);
    for (int i = 0; i < la; ++i) f[i] = in(a[i]);
    clr(f + la, lim - la);
    if (lb > 0) {
        for (int i = 0; i < lb; ++i) g[i] = in(b[i]);
        clr(g + lb, lim - lb);
    } else clr(g, lim);
    if (ld > 0) {
        for (int i = 0; i < ld; ++i) h[i] = in(d[i]);
        clr(h + ld, lim - ld);
    } else clr(h, lim);

    dif(f, lim);
    dif(g, lim);
    dif(h, lim);
    dot(g, f, lim);
    dot(h, f, lim);
    dit(g, lim);
    dit(h, lim);

    int pc = lb > 0 ? la + lb - 1 : 0;
    int pe = ld > 0 ? la + ld - 1 : 0;
    int tc = min(outn + 1, pc), te = min(outn + 1, pe);
    for (int i = 0; i < tc; ++i) c[i] = out(g[i]);
    for (int i = tc; i <= outn; ++i) c[i] = 0;
    for (int i = 0; i < te; ++i) e[i] = out(h[i]);
    for (int i = te; i <= outn; ++i) e[i] = 0;
}

void fastexp(int *a, int *b, int n) {
    using namespace grader_namespace;
    int L = n + 1;
    _alcr alc;
    auto f = alc(L), g = alc(L);
    for (int i = 0; i < L; ++i) g[i] = in(a[i]);
    poly_exp(f, g, L);
    for (int i = 0; i < L; ++i) b[i] = out(f[i]);
}

void fastln(int *a, int *b, int n) {
    using namespace grader_namespace;
    int L = n + 1;
    _alcr alc;
    auto f = alc(L), g = alc(L);
    for (int i = 0; i < L; ++i) g[i] = in(a[i]);
    poly_ln(f, g, L);
    for (int i = 0; i < L; ++i) b[i] = out(f[i]);
}

void fastinv(int *a, int *b, int n) {
    using namespace grader_namespace;
    int L = n + 1;
    _alcr alc;
    auto f = alc(L), g = alc(L);
    for (int i = 0; i < L; ++i) g[i] = in(a[i]);
    poly_inv_f(f, g, L);
    for (int i = 0; i < L; ++i) b[i] = out(f[i]);
}

namespace chatgpt{
    static constexpr int MOD = 998244353;
    static constexpr int MAXN = 1005;
    static constexpr int MAXL = 1024;
    static constexpr int MAXS = MAXL * 2; // 2048
    static constexpr int MAXLOG = 10;

    static int QC[MAXLOG + 1][MAXLOG + 1][MAXS];
    static int cache_d[MAXLOG + 1];
    static bool cache_init[MAXLOG + 1];

    static int A[MAXS], B[MAXS], C[MAXS], D[MAXS];
    static int EV[MAXS];
    static int SA[MAXS];
    static int P0[MAXS], P1[MAXS];

    static int invs[MAXL + 1];
    static bool inv_ready=false;

    static inline int addmod(int x, int y) {
        x += y;
        if (x >= MOD) x -= MOD;
        return x;
    }

    static inline int submod(int x, int y) {
        x -= y;
        if (x < 0) x += MOD;
        return x;
    }

    /*
    a[i] = sum_{x in S} C(x,i), 0 <= i <= n

    ans[i] = sum_{x in S} C(d*x,i)
    */
    void binom_scale(int n, int d, const int *a, int *ans) {
        const int m = n + 1;

        d %= MOD;
        if (d < 0) d += MOD;

        // trivial cases
        if (n == 0) {
            ans[0] = a[0];
            return;
        }

        if (d == 0) {
            ans[0] = a[0];
            for (int i = 1; i <= n; ++i) ans[i] = 0;
            return;
        }

        if (d == 1) {
            memcpy(ans, a, sizeof(int) * m);
            return;
        }

        int N = 1, lg = 0;
        while (N < m) {
            N <<= 1;
            ++lg;
        }

        const int S = N << 1;
        const int LIM = S - 2;

        int (*Q)[MAXS] = QC[lg];

        if(!inv_ready){
            invs[1]=1;
            for(int i=2;i<MAXL;i++)
                invs[i]=MOD-(long long)(MOD/i)*invs[MOD%i]%MOD;
            inv_ready=true;
        }

        int nn = N;
        int k = 1;

        // Q depends only on the padded truncation length N and d.  Computing
        // modulo x^N is sufficient for every n with this same power-of-two N,
        // so reuse it across calls in the same bucket.
        if(!cache_init[lg] || cache_d[lg]!=d){
            cache_init[lg]=true;
            cache_d[lg]=d;

            memset(Q[0],0,sizeof(int)*S);
            long long coef=1;
            int fd=min(N-1,d); // binom(d,i)=0 for i>d
            for(int i=1;i<=fd;i++){
                int z=d-i+1;
                coef=coef*z%MOD*invs[i]%MOD;
                int x=(int)coef;
                Q[0][i]=x?MOD-x:0;
            }

            for(int lev=0;lev<lg;++lev){
                int *q=Q[lev], *nq=Q[lev+1];

                int la=0;
                for(int i=0;i<N;i++){
                    int x=q[i<<1]; A[i]=x;
                    if(x) la=i+1;
                }
                fastsqr_len(A,la,C,LIM);
                memcpy(EV,C,sizeof(int)*(LIM+1));
                EV[S-1]=0;

                la=0;
                for(int i=0;i<N;i++){
                    int x=q[i<<1|1]; A[i]=x;
                    if(x) la=i+1;
                }
                fastsqr_len(A,la,C,LIM);
                for(int i=1;i<S;i++) EV[i]=submod(EV[i],C[i-1]);

                for(int i=0;i<N;i++){
                    int &x=EV[N+i];
                    x=addmod(x,q[i<<1]);
                    x=addmod(x,q[i<<1]);
                }

                memset(nq,0,sizeof(int)*S);
                for(int j=0;j<(k<<1);j++)
                    memcpy(nq+nn*j,EV+nn*j,sizeof(int)*(nn>>1));
                nn>>=1; k<<=1;
            }
        }

        nn = N;
        k = 1;
        /*
            Base layer.

            Outer polynomial is
                A(x)=sum a_i x^i.

            K-L transposition puts reversed coefficients
            on even positions.
        */
        memset(P0, 0, sizeof(int) * S);

        for (int i = 0; i < N; ++i) {
            int j = N - 1 - i;
            P0[i << 1] = (j < m ? a[j] : 0);
        }

        int *p = P0;
        int *np = P1;

        /*
            Reverse / transpose all Bostan-Mori layers.

            Because pq has only odd coefficients, the middle product
            can be split by parity into TWO ordinary convolutions.

            Thus each backward layer also uses exactly 2 fastmul calls.
        */
        for (int lev = lg - 1; lev >= 0; --lev) {
            nn = N >> lev;
            k = 1 << lev;

            int *q = Q[lev];

            /*
                pq[2*(nn*j+i)+1] = p[nn*j+i],
                for i < nn/2.

                Store only the odd-position coefficients:
                    SA[w] = pq[2w+1].
            */
            memset(SA, 0, sizeof(int) * (S - 1));

            for (int j = 0; j < (k << 1); ++j) {
                memcpy(
                    SA + nn * j,
                    p + nn * j,
                    sizeof(int) * (nn >> 1)
                );
            }

            memset(np, 0, sizeof(int) * S);

            /*
                Contribution pq[S+i].
                pq has only odd positions.

                pq[S + (2u+1)] = SA[N+u].
            */
            for (int u = 0; u + 1 < N; ++u)
                np[(u << 1) | 1] = SA[N + u];

            /*
                r(x)=q(-x).

                For even output positions:
                    x[2u]
                      = sum_v SA[u+v] * r[2v+1].

                This is correlation, hence convolution with reversed r_odd.
            */
            int lsa = 0, lb1 = 0, lb2 = 0;
            for (int i = 0; i <= LIM; ++i)
                if (SA[i]) lsa = i + 1;

            for (int j = 0; j < N; ++j) {
                int v = N - 1 - j;
                int x = q[(v << 1) | 1];
                // r[2v+1] = -q[2v+1]
                B[j] = x ? MOD - x : 0;
                if (B[j]) lb1 = j + 1;

                EV[j] = q[v << 1];
                if (EV[j]) lb2 = j + 1;
            }

            // The two correlations share exactly the same left operand SA.
            // Transform it once and reuse the spectrum.
            fastmul2_same_a_len(SA, lsa, B, lb1, C, EV, lb2, D, LIM);

            for (int u = 0; u < N; ++u) {
                np[u << 1] =
                    addmod(np[u << 1], C[N - 1 + u]);
                np[(u << 1) | 1] =
                    addmod(np[(u << 1) | 1], D[N - 1 + u]);
            }

            swap(p, np);
        }

        /*
            Final reverse.
        */
        for (int i = 0; i <= n; ++i)
            ans[i] = p[N - 1 - i];
    }
}

const int N = 2000, MM = 1005;
int n,c[N+5],d[N+5];
vector<int>E[N+5];
int f[N+5][MM+5],t0[MM+5],t1[MM+5],f0[MM+5];

int cf[MM+5][MM+5];

void upd(int &a, ull b){ a=(a+b)%mod; }

void dfs(int x,int fa,int dep){
    for(int y:E[x]) if(y!=fa) dfs(y,x,dep+1);

    int M = min(MM, dep);
    bool got=false;
    for(int y:E[x]) if(y!=fa){
        if(!got){
            memcpy(t0,f[y],sizeof(int)*(M+1));
            got=true;
        }else fastmul(f[y],t0,t0,M);
    }
    if(!got){
        memset(t0,0,sizeof(int)*(M+1));
        t0[0]=1;
    }

    // d=1 implies c=0 after normalization, and the whole node transform
    // is exactly the identity.
    if(d[x]==1){
        memcpy(f[x],t0,sizeof(int)*(M+1));
        return;
    }

    // C(c[x],j), only this node's row is ever needed.
    t1[0]=1;
    int fall=1;
    int tc=min(M,c[x]);
    for(int j=1;j<=tc;j++){
        fall=(ull)fall*(c[x]-j+1)%mod;
        t1[j]=(ull)fall*inv[j]%mod;
    }
    if(tc<M) memset(t1+tc+1,0,sizeof(int)*(M-tc));

    if(!got){
        // A=1 => A((1+t)^d-1)=1, so both expensive products disappear.
        for(int i=0;i<M;i++){
            int z=t1[i]+t1[i+1]; addmod(z);
            f[x][i]=z;
        }
        f[x][M]=t1[M];
        return;
    }

    chatgpt::binom_scale(M,d[x],t0,f0);
    if(c[x]) fastmul_len_trunc(f0,M+1,t1,tc+1,f0,M);

    for(int i=0;i<=M;i++){
        addmod(f[x][i]=f0[i]+f0[i+1]);
        addmod(f[x][i]+=mod-t0[i+1]);
    }
}

void procedure(){
    n=read();
    for(int i=1;i<=n;i++){
        c[i]=read(),d[i]=read();
        c[i]=(d[i]-c[i]%d[i])%d[i];

    }

    for(int i=1;i<n;i++){
        int u=read(),v=read();
        E[u].pb(v),E[v].pb(u);
    }
    dfs(1,0,1);
    printf("%d\n",f[1][0]);
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