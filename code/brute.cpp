#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
using namespace std;

const long long INF = 2e18;
const int MAXN = 100005;
long long A[MAXN];

struct Op {
    int type, l, r, x;
    long long k;
} ops[MAXN];

int E[1505];
bool is_set[1505];
long long set_val[1505];
long long add_val[1505];
long long max_val[1505];

vector<pair<long long, int>> P_L[1505];
vector<pair<long long, int>> P_R[1505];

void solve() {
    int n, m;
    if (!(cin >> n >> m)) return;
    for (int i = 1; i <= n; ++i) cin >> A[i];
    
    for (int i = 0; i < m; ++i) {
        cin >> ops[i].type;
        if (ops[i].type == 3) cin >> ops[i].l >> ops[i].r >> ops[i].x;
        else cin >> ops[i].l >> ops[i].r >> ops[i].k;
    }

    int B = 300; // 最优分块大小
    for (int start = 0; start < m; start += B) {
        int end = min(m - 1, start + B - 1);
        
        // 1. 收集当前块内 1, 2, 3 操作的所有端点，彻底切碎序列
        int e_cnt = 0;
        E[e_cnt++] = 1;
        E[e_cnt++] = n + 1;
        for (int i = start; i <= end; ++i) {
            E[e_cnt++] = ops[i].l;
            E[e_cnt++] = ops[i].r + 1;
            if (ops[i].type == 3) {
                E[e_cnt++] = ops[i].x;
                E[e_cnt++] = ops[i].x + 1;
            }
        }
        sort(E, E + e_cnt);
        int S = unique(E, E + e_cnt) - E - 1;

        // 2. 为每一段预处理信息（无需在意块被截断的问题了）
        for (int j = 0; j < S; ++j) {
            int L = E[j], R = E[j+1] - 1;
            is_set[j] = false; add_val[j] = 0;
            
            P_L[j].clear(); P_R[j].clear();
            long long cmax = -INF;
            for (int i = L; i <= R; ++i) {
                if (A[i] >= cmax) { P_L[j].push_back({A[i], i}); cmax = A[i]; }
            }
            cmax = -INF;
            for (int i = R; i >= L; --i) {
                if (A[i] >= cmax) { P_R[j].push_back({A[i], i}); cmax = A[i]; }
            }
            max_val[j] = cmax;
        }

        // 3. 处理块内操作
        for (int i = start; i <= end; ++i) {
            if (ops[i].type == 1 || ops[i].type == 2) {
                int sj = lower_bound(E, E + S, ops[i].l) - E;
                int ej = lower_bound(E, E + S, ops[i].r + 1) - E - 1;
                for (int j = sj; j <= ej; ++j) {
                    if (ops[i].type == 1) {
                        if (is_set[j]) set_val[j] += ops[i].k;
                        else add_val[j] += ops[i].k;
                        max_val[j] += ops[i].k;
                    } else {
                        is_set[j] = true;
                        set_val[j] = ops[i].k;
                        add_val[j] = 0;
                        max_val[j] = ops[i].k;
                    }
                }
            } else {
                int l = ops[i].l, r = ops[i].r, x = ops[i].x;
                int sx = lower_bound(E, E + S, x) - E;
                int sl = lower_bound(E, E + S, l) - E;
                int sr = lower_bound(E, E + S, r + 1) - E - 1;
                
                long long Ax = is_set[sx] ? set_val[sx] : (A[x] + add_val[sx]);
                int ans = (x >= l && x <= r) ? 1 : 0;
                
                // 向右扫描
                bool found = false; long long M = Ax;
                for (int j = sx + 1; j <= sr; ++j) {
                    int valid = 0;
                    if (!found) {
                        if (max_val[j] <= Ax) valid = E[j+1] - E[j];
                        else {
                            found = true;
                            if (j >= sl) {
                                if (is_set[j]) valid = E[j+1] - E[j];
                                else {
                                    auto it = upper_bound(P_L[j].begin(), P_L[j].end(), Ax - add_val[j], 
                                        [](long long val, const pair<long long, int>& p){ return val < p.first; });
                                    valid = (it->second - E[j]) + (P_L[j].end() - it);
                                }
                            }
                            M = max_val[j];
                        }
                    } else {
                        if (M <= max_val[j]) {
                            if (j >= sl) {
                                if (is_set[j]) { if (set_val[j] >= M) valid = E[j+1] - E[j]; }
                                else {
                                    auto it = lower_bound(P_L[j].begin(), P_L[j].end(), M - add_val[j], 
                                        [](const pair<long long, int>& p, long long val){ return p.first < val; });
                                    valid = P_L[j].end() - it;
                                }
                            }
                            M = max_val[j];
                        }
                    }
                    if (j >= sl) ans += valid;
                }

                // 向左扫描
                found = false; M = Ax;
                for (int j = sx - 1; j >= sl; --j) {
                    int valid = 0;
                    if (!found) {
                        if (max_val[j] <= Ax) valid = E[j+1] - E[j];
                        else {
                            found = true;
                            if (j <= sr) {
                                if (is_set[j]) valid = E[j+1] - E[j];
                                else {
                                    auto it = upper_bound(P_R[j].begin(), P_R[j].end(), Ax - add_val[j], 
                                        [](long long val, const pair<long long, int>& p){ return val < p.first; });
                                    valid = ((E[j+1] - 1) - it->second) + (P_R[j].end() - it);
                                }
                            }
                            M = max_val[j];
                        }
                    } else {
                        if (M <= max_val[j]) {
                            if (j <= sr) {
                                if (is_set[j]) { if (set_val[j] >= M) valid = E[j+1] - E[j]; }
                                else {
                                    auto it = lower_bound(P_R[j].begin(), P_R[j].end(), M - add_val[j], 
                                        [](const pair<long long, int>& p, long long val){ return p.first < val; });
                                    valid = P_R[j].end() - it;
                                }
                            }
                            M = max_val[j];
                        }
                    }
                    if (j <= sr) ans += valid;
                }
                cout << ans << "\n";
            }
        }

        // 4. 块结束后，下放所有懒标记
        for (int j = 0; j < S; ++j) {
            if (is_set[j]) {
                for (int i = E[j]; i < E[j+1]; ++i) A[i] = set_val[j];
            } else if (add_val[j] != 0) {
                for (int i = E[j]; i < E[j+1]; ++i) A[i] += add_val[j];
            }
        }
    }
}

int main() {
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.ans","w",stdout));
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    if (cin >> T) {
        while (T--) solve();
    }
    return 0;
}