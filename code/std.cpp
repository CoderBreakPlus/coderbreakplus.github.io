#include <bits/stdc++.h>
using namespace std;

using u32 = uint32_t;
using u64 = uint64_t;
using i64 = long long;

static constexpr u32 MOD = 998244353u;
static constexpr int KMAX = 9;
static constexpr int BASE = 32;

struct Mat {
    u32 a[KMAX][KMAX]{};
};

int n, k;
vector<Mat> transMat;
vector<int> pcnt;

static inline u32 sub_mul(u32 a, u32 b, u32 c, u32 d) {
    u64 x = (u64)a * b % MOD;
    u64 y = (u64)c * d % MOD;

    return (x >= y)
        ? (u32)(x - y)
        : (u32)(x + MOD - y);
}

static inline Mat identityMat() {
    Mat I;

    for (int i = 0; i < k; ++i)
        I.a[i][i] = 1;

    return I;
}

static inline Mat multiply(const Mat &A, const Mat &B) {
    Mat C;

    for (int i = 0; i < k; ++i) {
        for (int j = 0; j < k; ++j) {
            u64 s = 0;

            for (int t = 0; t < k; ++t) {
                s += (u64)A.a[i][t] * B.a[t][j];
            }

            C.a[i][j] = (u32)(s % MOD);
        }
    }

    return C;
}

/*
    求矩阵秩。

    这里不用逆元，采用交叉相消：

        row_i <- pivot * row_i - coef * row_pivot

    在有限域中同样保持秩不变。
*/
static inline int matrixRank(Mat A) {
    int r = 0;

    for (int c = 0; c < k && r < k; ++c) {
        int p = r;

        while (p < k && A.a[p][c] == 0)
            ++p;

        if (p == k)
            continue;

        if (p != r) {
            for (int j = c; j < k; ++j)
                swap(A.a[p][j], A.a[r][j]);
        }

        const u32 pivot = A.a[r][c];

        for (int i = r + 1; i < k; ++i) {
            if (A.a[i][c] == 0)
                continue;

            const u32 coef = A.a[i][c];

            for (int j = c + 1; j < k; ++j) {
                A.a[i][j] =
                    sub_mul(
                        A.a[i][j], pivot,
                        A.a[r][j], coef
                    );
            }

            A.a[i][c] = 0;
        }

        ++r;
    }

    return r;
}

/*
    判断 mask 对应的若干列是否线性无关。

    左侧使用：

        第 i 层任取若干洞
             ->
        第 M 层必须到达 mask

    可行当且仅当这些列线性无关。
*/
static inline bool independentColumns(
    const Mat &P,
    int mask
) {
    u32 basis[KMAX][KMAX]{};
    bool has[KMAX]{};

    for (int col = 0; col < k; ++col) {
        if (!(mask >> col & 1))
            continue;

        u32 v[KMAX];

        for (int row = 0; row < k; ++row)
            v[row] = P.a[row][col];

        bool inserted = false;

        for (int p = 0; p < k; ++p) {
            if (v[p] == 0)
                continue;

            if (!has[p]) {
                has[p] = true;

                for (int q = p; q < k; ++q)
                    basis[p][q] = v[q];

                inserted = true;
                break;
            }

            const u32 vp = v[p];
            const u32 bp = basis[p][p];

            for (int q = p + 1; q < k; ++q) {
                v[q] =
                    sub_mul(
                        v[q], bp,
                        basis[p][q], vp
                    );
            }

            v[p] = 0;
        }

        if (!inserted)
            return false;
    }

    return true;
}

/*
    判断 mask 对应的若干行是否线性无关。

    右侧使用：

        第 M 层从 mask 出发
             ->
        第 j 层任取终点
*/
static inline bool independentRows(
    const Mat &P,
    int mask
) {
    u32 basis[KMAX][KMAX]{};
    bool has[KMAX]{};

    for (int row = 0; row < k; ++row) {
        if (!(mask >> row & 1))
            continue;

        u32 v[KMAX];

        for (int col = 0; col < k; ++col)
            v[col] = P.a[row][col];

        bool inserted = false;

        for (int p = 0; p < k; ++p) {
            if (v[p] == 0)
                continue;

            if (!has[p]) {
                has[p] = true;

                for (int q = p; q < k; ++q)
                    basis[p][q] = v[q];

                inserted = true;
                break;
            }

            const u32 vp = v[p];
            const u32 bp = basis[p][p];

            for (int q = p + 1; q < k; ++q) {
                v[q] =
                    sub_mul(
                        v[q], bp,
                        basis[p][q], vp
                    );
            }

            v[p] = 0;
        }

        if (!inserted)
            return false;
    }

    return true;
}

/*
    小区间直接计算所有 f(i,j)。

    P 为 i -> j 的路径矩阵。

    LGV 定理保证：
        rank(P)
    等于 i 到 j 的最大点不相交路径数量
    （随机赋权后以极高概率成立）。
*/
static i64 solveSmall(int L, int R) {
    i64 ans = 0;

    for (int i = L; i < R; ++i) {
        Mat P = identityMat();

        for (int j = i + 1; j <= R; ++j) {
            P = multiply(P, transMat[j - 1]);

            ans += matrixRank(P);
        }
    }

    return ans;
}

static i64 divideSolve(int L, int R) {
    if (L >= R)
        return 0;

    if (R - L + 1 <= BASE)
        return solveSmall(L, R);

    int M = (L + R) >> 1;

    i64 ans =
        divideSolve(L, M) +
        divideSolve(M + 1, R);

    const int ALL = 1 << k;

    int leftMost[1 << KMAX];
    int rightMost[1 << KMAX];
    bool alive[1 << KMAX];

    /*
        ============================
        向左
        ============================

        对中间层 M 的每个子集 S：

        leftMost[S]

        表示最左能够从某层的任意 |S| 个洞，
        用互不相交路径流到 S 的层。
    */

    Mat P = identityMat();

    for (int mask = 1; mask < ALL; ++mask)
        alive[mask] = true;

    int oldRank = k;

    for (int i = M - 1; i >= L; --i) {
        /*
            i -> M

            A_i A_{i+1} ... A_{M-1}
        */
        P = multiply(transMat[i], P);

        int newRank = matrixRank(P);

        /*
            如果总秩没有下降，那么这个左乘在线性空间上是单射，
            所以所有列集合的线性相关关系完全不变。

            因此不必枚举 2^k。
        */
        if (newRank == oldRank)
            continue;

        for (int mask = 1; mask < ALL; ++mask) {
            if (!alive[mask])
                continue;

            bool ok;

            if (pcnt[mask] > newRank) {
                ok = false;
            } else {
                ok = independentColumns(P, mask);
            }

            if (!ok) {
                alive[mask] = false;

                /*
                    i 已经不行，
                    i+1 还是可以的。
                */
                leftMost[mask] = i + 1;
            }
        }

        oldRank = newRank;

        if (oldRank == 0)
            break;
    }

    for (int mask = 1; mask < ALL; ++mask) {
        if (alive[mask])
            leftMost[mask] = L;
    }

    /*
        ============================
        向右
        ============================
    */

    P = identityMat();

    for (int mask = 1; mask < ALL; ++mask)
        alive[mask] = true;

    oldRank = k;

    for (int j = M + 1; j <= R; ++j) {
        /*
            M -> j
        */
        P = multiply(P, transMat[j - 1]);

        int newRank = matrixRank(P);

        if (newRank == oldRank)
            continue;

        for (int mask = 1; mask < ALL; ++mask) {
            if (!alive[mask])
                continue;

            bool ok;

            if (pcnt[mask] > newRank) {
                ok = false;
            } else {
                ok = independentRows(P, mask);
            }

            if (!ok) {
                alive[mask] = false;

                /*
                    j 已经不行，
                    j-1 是最远可达。
                */
                rightMost[mask] = j - 1;
            }
        }

        oldRank = newRank;

        if (oldRank == 0)
            break;
    }

    for (int mask = 1; mask < ALL; ++mask) {
        if (alive[mask])
            rightMost[mask] = R;
    }

    /*
        ============================
        更新跨过 M 的答案
        ============================

        对一个集合 S：

          leftMost[S] <= i <= M
          M < j <= rightMost[S]

        都有

          f(i,j) >= |S|

        而且反过来也成立。
    */

    vector<int> ord;
    ord.reserve(ALL - 1);

    for (int mask = 1; mask < ALL; ++mask) {
        if (rightMost[mask] > M)
            ord.push_back(mask);
    }

    sort(
        ord.begin(),
        ord.end(),
        [&](int x, int y) {
            return leftMost[x] < leftMost[y];
        }
    );

    /*
        farthest[s]:

        当前固定左端点 i 时，
        所有大小恰好为 s 且可以从 i 到达的
        中间层集合中，最远可以走到哪里。
    */
    int farthest[KMAX + 1];

    for (int s = 0; s <= k; ++s)
        farthest[s] = M;

    int ptr = 0;

    for (int i = L; i <= M; ++i) {
        while (
            ptr < (int)ord.size() &&
            leftMost[ord[ptr]] <= i
        ) {
            int mask = ord[ptr++];

            int s = pcnt[mask];

            farthest[s] =
                max(
                    farthest[s],
                    rightMost[mask]
                );
        }

        /*
            f(i,j) >= t

            当且仅当存在一个大小 >= t 的集合
            可以走到 j。

            因此：

            f(i,j)
            =
            sum_t [f(i,j) >= t]
        */

        int best = M;

        for (int t = k; t >= 1; --t) {
            best =
                max(
                    best,
                    farthest[t]
                );

            ans += best - M;
        }
    }

    return ans;
}

static uint64_t splitmix64(uint64_t &x) {
    uint64_t z =
        (x += 0x9e3779b97f4a7c15ULL);

    z =
        (z ^ (z >> 30)) *
        0xbf58476d1ce4e5b9ULL;

    z =
        (z ^ (z >> 27)) *
        0x94d049bb133111ebULL;

    return z ^ (z >> 31);
}

int main() {
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.ans","w",stdout));
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    cin >> n >> k;

    transMat.resize(n - 1);

    uint64_t seed =
        0x123456789abcdef0ULL;

    /*
        输入：

        对于每个 i = 1..n-1，
        输入 k 个长度为 k 的 01 串。

        第 p 行第 q 位为 1
        表示：

            第 i 组第 p 个洞
                  ->
            第 i+1 组第 q 个洞

        存在隧道。
    */
    for (int layer = 0; layer < n - 1; ++layer) {
        for (int i = 0; i < k; ++i) {
            string s;
            cin >> s;

            for (int j = 0; j < k; ++j) {
                if (s[j] == '1') {
                    /*
                        每条隧道随机赋一个非零权值。

                        LGV 后：
                        路径矩阵的秩 = 最大不相交路径数
                        以极高概率成立。
                    */
                    transMat[layer].a[i][j] =
                        (u32)(
                            splitmix64(seed)
                            % (MOD - 1)
                            + 1
                        );
                }
            }
        }
    }

    pcnt.resize(1 << k);

    for (int mask = 1; mask < (1 << k); ++mask) {
        pcnt[mask] =
            pcnt[mask >> 1]
            + (mask & 1);
    }

    cout
        << divideSolve(0, n - 1)
        << '\n';

    return 0;
}