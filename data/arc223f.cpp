// created time: 2026-07-13 19:52:47
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

const int N_MAX = 500000;
int fac[N_MAX+5],inv[N_MAX+5];
void math_init(){
    fac[0]=inv[0]=1;
    for(int i=1;i<=N_MAX;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[N_MAX]=qpow(fac[N_MAX],mod-2);
    for(int i=N_MAX-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}

ll n,x;
int a[100005],pos[100005];

namespace NTT_Env {
    int rev[1048576];
    int Wn[1048576], iWn[1048576];
    bool inited = false;
    
    void precompute() {
        if (inited) return;
        inited = true;
        for (int mid = 1; mid < 524288; mid <<= 1) {
            int w1 = qpow(3, (mod - 1) / (mid << 1));
            int w2 = qpow(332748118, (mod - 1) / (mid << 1));
            int p1 = 1, p2 = 1;
            for (int j = 0; j < mid; j++) {
                Wn[mid + j] = p1;
                iWn[mid + j] = p2;
                p1 = 1ll * p1 * w1 % mod;
                p2 = 1ll * p2 * w2 % mod;
            }
        }
    }

    void init_rev(int len) {
        int L = 0;
        while ((1 << L) < len) L++;
        for (int i = 0; i < len; i++) {
            rev[i] = (rev[i >> 1] >> 1) | ((i & 1) << (L - 1));
        }
    }

    void NTT(vector<int> &a, int len, int type) {
        a.resize(len, 0);
        for (int i = 0; i < len; i++) if (i < rev[i]) swap(a[i], a[rev[i]]);
        for (int mid = 1; mid < len; mid <<= 1) {
            int *W = (type == 1 ? Wn : iWn) + mid;
            for (int i = 0; i < len; i += (mid << 1)) {
                for (int j = 0; j < mid; j++) {
                    int x = a[i + j], y = 1ll * W[j] * a[i + j + mid] % mod;
                    a[i + j] = (x + y >= mod ? x + y - mod : x + y);
                    a[i + j + mid] = (x - y < 0 ? x - y + mod : x - y);
                }
            }
        }
        if (type == -1) {
            int inv = qpow(len, mod - 2);
            for (int i = 0; i < len; i++) a[i] = 1ll * a[i] * inv % mod;
        }
    }
}
using namespace NTT_Env;

struct Poly {
    vector<int> a;
    Poly() {}
    Poly(vector<int> a) : a(a) {}
    Poly operator*(const Poly &o) const;
};

void shrink(Poly &p) {
    while (!p.a.empty() && p.a.back() == 0) p.a.pop_back();
}

Poly add(const Poly &A, const Poly &B) {
    Poly res;
    res.a.resize(max(A.a.size(), B.a.size()));
    for (size_t i = 0; i < res.a.size(); i++) {
        int x = i < A.a.size() ? A.a[i] : 0;
        int y = i < B.a.size() ? B.a[i] : 0;
        res.a[i] = (x + y >= mod ? x + y - mod : x + y);
    }
    shrink(res);
    return res;
}

Poly Poly::operator*(const Poly &o) const {
    if (a.empty() || o.a.empty()) return Poly();
    if (a.size() <= 64 || o.a.size() <= 64) {
        Poly res;
        res.a.resize(a.size() + o.a.size() - 1, 0);
        for (size_t i = 0; i < a.size(); i++) {
            if (!a[i]) continue;
            unsigned long long term = a[i];
            for (size_t j = 0; j < o.a.size(); j++) {
                res.a[i + j] = (res.a[i + j] + term * o.a[j]) % mod;
            }
        }
        shrink(res);
        return res;
    }
    int len = 1;
    while (len < a.size() + o.a.size() - 1) len <<= 1;
    vector<int> A = a, B = o.a;
    init_rev(len);
    NTT(A, len, 1); NTT(B, len, 1);
    for (int i = 0; i < len; i++) A[i] = 1ll * A[i] * B[i] % mod;
    NTT(A, len, -1);
    A.resize(a.size() + o.a.size() - 1);
    Poly res(A);
    shrink(res);
    return res;
}

struct Matrix {
    Poly mat[2][2];
};

Matrix mul(const Matrix &A, const Matrix &B) {
    Matrix res;
    int maxA = 0, maxB = 0;
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            maxA = max(maxA, (int)A.mat[i][j].a.size());
            maxB = max(maxB, (int)B.mat[i][j].a.size());
        }
    }
    if (maxA == 0 || maxB == 0) return res;

    // 较小规模多项式直接 $O(N^2)$ 计算降低常数
    if (maxA <= 64 || maxB <= 64) {
        for(int i=0;i<2;i++) {
            for(int k=0;k<2;k++) {
                if(A.mat[i][k].a.empty()) continue;
                for(int j=0;j<2;j++) {
                    if(B.mat[k][j].a.empty()) continue;
                    res.mat[i][j] = add(res.mat[i][j], A.mat[i][k] * B.mat[k][j]);
                }
            }
        }
        return res;
    }
    
    int len = 1;
    while (len < maxA + maxB - 1) len <<= 1;
    init_rev(len);
    
    // 对点值相乘直接累加处理，减少无用的冗余 NTT
    vector<int> tA[2][2], tB[2][2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            if (!A.mat[i][j].a.empty()) {
                tA[i][j] = A.mat[i][j].a; tA[i][j].resize(len, 0); NTT(tA[i][j], len, 1);
            } else {
                tA[i][j].assign(len, 0);
            }
            if (!B.mat[i][j].a.empty()) {
                tB[i][j] = B.mat[i][j].a; tB[i][j].resize(len, 0); NTT(tB[i][j], len, 1);
            } else {
                tB[i][j].assign(len, 0);
            }
        }
    }
    
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            vector<int> tC(len, 0);
            int sz = 0;
            for (int k = 0; k < 2; k++) {
                if (!A.mat[i][k].a.empty() && !B.mat[k][j].a.empty()) {
                    sz = max(sz, (int)A.mat[i][k].a.size() + (int)B.mat[k][j].a.size() - 1);
                    for (int l = 0; l < len; l++) {
                        tC[l] = (tC[l] + 1ll * tA[i][k][l] * tB[k][j][l]) % mod;
                    }
                }
            }
            if (sz > 0) {
                NTT(tC, len, -1);
                tC.resize(sz);
                res.mat[i][j] = Poly(tC);
                shrink(res.mat[i][j]);
            }
        }
    }
    return res;
}

Poly C_poly(int m, int v) {
    if (a[m] > v && a[m] != -1) return Poly();
    if (a[m] <= v && a[m] != -1) return Poly({1});
    if (a[m] == -1) return Poly({0, 1});
    return Poly();
}

Poly G_poly(int m, int v) {
    if (a[m] > v && a[m] != -1) return Poly({1});
    if (a[m] <= v && a[m] != -1) return Poly();
    if (a[m] == -1) return Poly({1});
    return Poly();
}

Matrix get_matrix(int idx, int v) {
    int k = 2 * idx + 2;
    int i = k - 1; 
    Poly ci = C_poly(i, v), gi = G_poly(i, v);
    Poly ck = C_poly(k, v), gk = G_poly(k, v);
    
    Matrix M;
    M.mat[0][0] = add(ck, gk) * gi;
    M.mat[0][1] = gk * ci;
    M.mat[1][0] = gk * gi;
    M.mat[1][1] = Poly();
    return M;
}

Matrix solve_DC(int L, int R, int v) {
    if (L == R) return get_matrix(L, v);
    int mid = (L + R) / 2;
    Matrix left = solve_DC(L, mid, v);
    Matrix right = solve_DC(mid + 1, R, v);
    return mul(right, left);
}

int solve(int v){
    int cnt=0,res=0;
    for(int i=1;i<=v;i++) if(!pos[i]) cnt++;
    for(int i=v+1;i<=n;i++) if(!pos[i]) res++;

    Poly S_n_1, dp_n_1_2;
    int m = (n - 1) / 2;
    if (m == 0) {
        S_n_1 = Poly({1});
        dp_n_1_2 = Poly({1});
    } else {
        Matrix M_final = solve_DC(0, m - 1, v);
        S_n_1 = add(M_final.mat[0][0], M_final.mat[0][1]);
        dp_n_1_2 = add(M_final.mat[1][0], M_final.mat[1][1]);
    }
    
    Poly cn = C_poly(n, v), gn = G_poly(n, v);
    Poly S_n = add(gn * S_n_1, cn * dp_n_1_2);

    int tmp = 0;
    if (cnt < S_n.a.size()) tmp = S_n.a[cnt];
    return 1ll * tmp * fac[res] % mod * fac[cnt] % mod;
}

void procedure(){
    n=read(),x=read();
    x=n*(n+1)/2-x;
    int cnt=0;

    for(int i=1;i<=n;i++) pos[i]=0;
    for(int i=1;i<=n;i++){
        a[i]=read();
        if(~a[i]) pos[a[i]]=i;
        cnt+=(a[i]==-1);
    }
    if(!(n&1)){
        if(!x) printf("%d\n",fac[cnt]);
        else puts("0");
        return;
    }
    if(1<=x&&x<=n){
        int ans = (solve(x-1) - solve(x) + mod) % mod;
        printf("%d\n",ans);
    }else{
        puts("0");
    }
}

int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
    ll T=read();
    math_init();
    precompute();
    while(T--) procedure();
    return 0;
}