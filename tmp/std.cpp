#include <cstdio>
#include <algorithm>

using namespace std;

// 极致快读
namespace IO {
    const int BUF_SIZE = 1 << 20;
    char buf[BUF_SIZE], *p1 = buf, *p2 = buf;
    inline char gc() {
        return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, BUF_SIZE, stdin), p1 == p2) ? EOF : *p1++;
    }
    template<class T> inline void read(T &x) {
        x = 0; char c = gc();
        while (c < '0' || c > '9') c = gc();
        while (c >= '0' && c <= '9') {
            x = x * 10 + (c ^ 48);
            c = gc();
        }
    }
}
using IO::read;

const int MAXM = 2097152;
int mn[MAXM * 2 + 5], mx[MAXM * 2 + 5];
int M;

void build(int n, int *a) {
    for (M = 1; M <= n + 1; M <<= 1);
    for (int i = 1; i <= n; ++i) mn[M + i] = mx[M + i] = a[i];
    // 边界初始化
    for (int i = M + n + 1; i < M * 2; ++i) mn[i] = 2e9, mx[i] = -2e9;
    mn[M] = 2e9, mx[M] = -2e9;
    for (int i = M - 1; i >= 1; --i) {
        mn[i] = min(mn[i << 1], mn[i << 1 | 1]);
        mx[i] = max(mx[i << 1], mx[i << 1 | 1]);
    }
}

void update(int x, int y) {
    x += M;
    mn[x] = mx[x] = y;
    for (x >>= 1; x; x >>= 1) {
        mn[x] = min(mn[x << 1], mn[x << 1 | 1]);
        mx[x] = max(mx[x << 1], mx[x << 1 | 1]);
    }
}

int query_min(int l, int r) {
    int res = 2e9;
    for (l += M - 1, r += M + 1; l ^ r ^ 1; l >>= 1, r >>= 1) {
        if (~l & 1) res = min(res, mn[l ^ 1]);
        if ( r & 1) res = min(res, mn[r ^ 1]);
    }
    return res;
}

// zkw线段树上二分查找第一个 >= x 的位置
int query_first(int l, int x, int n) {
    int curr = l + M;
    if (mx[curr] >= x) return l; // 命中自身
    while (curr > 1) {
        if (~curr & 1) { // 如果是左儿子，才去检查右兄弟（确保只向后找）
            if (mx[curr ^ 1] >= x) {
                curr ^= 1;
                while (curr < M) { // 往下二分
                    if (mx[curr << 1] >= x) curr <<= 1;
                    else curr = curr << 1 | 1;
                }
                return curr - M <= n ? curr - M : 0;
            }
        }
        curr >>= 1;
    }
    return 0; // 找不到
}

int n, q, a[1000005];

int main() {
    read(n); read(q);
    for (int i = 1; i <= n; ++i) read(a[i]);
    build(n, a);
    while (q--) {
        int op; read(op);
        if (op == 1) {
            int x, y; read(x); read(y);
            update(x, y);
        } else if (op == 2) {
            int l, r; read(l); read(r);
            printf("%d\n", query_min(l, r));
        } else {
            int l, x; read(l); read(x);
            printf("%d\n", query_first(l, x, n));
        }
    }
    return 0;
}