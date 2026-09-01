#include <bits/stdc++.h>
using namespace std;

const int INF = 1e9;
const int MAXN = 200005;

// 定义等效边上的 3x3 DP 矩阵
struct DPMatrix {
    int val[3][3];

    DPMatrix() {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                val[i][j] = -INF;
        val[0][0] = 0; // 默认不选任何边，贡献为 0
    }

    // 转置矩阵 (因为无向边 u->v 和 v->u 关系对称)
    DPMatrix transpose() const {
        DPMatrix res;
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                res.val[i][j] = val[j][i];
        return res;
    }
};

// 串联合并：消除中间点 u (边 x-u 和 u-y 合并为 x-y)
DPMatrix series_merge(const DPMatrix& A, const DPMatrix& B) {
    DPMatrix res;
    for (int i = 0; i < 3; i++) {
        for (int l = 0; l < 3; l++) {
            int best = -INF;
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    if (j + k <= 2 && A.val[i][j] >= 0 && B.val[k][l] >= 0) {
                        best = max(best, A.val[i][j] + B.val[k][l]);
                    }
                }
            }
            res.val[i][l] = best;
        }
    }
    return res;
}

// 并联合并：合并 x, y 之间的两条重边
DPMatrix parallel_merge(const DPMatrix& A, const DPMatrix& B) {
    DPMatrix res;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (A.val[i][j] < 0) continue;
            for (int k = 0; i + k < 3; k++) {
                for (int l = 0; j + l < 3; l++) {
                    if (B.val[k][l] < 0) continue;
                    res.val[i + k][j + l] = max(res.val[i + k][j + l], A.val[i][j] + B.val[k][l]);
                }
            }
        }
    }
    return res;
}

int n, m;
unordered_set<int> adj[MAXN];
map<pair<int, int>, DPMatrix> edge_dp;

void set_dp(int u, int v, const DPMatrix& mat) {
    edge_dp[{min(u, v), max(u, v)}] = (u < v ? mat : mat.transpose());
}

DPMatrix get_dp(int u, int v) {
    DPMatrix mat = edge_dp[{min(u, v), max(u, v)}];
    return (u < v ? mat : mat.transpose());
}

bool has_edge(int u, int v) {
    return edge_dp.count({min(u, v), max(u, v)});
}

void remove_edge(int u, int v) {
    adj[u].erase(v);
    adj[v].erase(u);
    edge_dp.erase({min(u, v), max(u, v)});
}

void solve() {
    cin >> n >> m;
    edge_dp.clear();
    for (int i = 1; i <= n; i++) adj[i].clear();

    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        if (u == v) continue; // 忽略自环

        DPMatrix single_edge;
        single_edge.val[1][1] = 1; // 选当前单边：u度数+1, v度数+1, 贡献边数 1

        if (!has_edge(u, v)) {
            adj[u].insert(v);
            adj[v].insert(u);
            set_dp(u, v, single_edge);
        } else {
            // 已有边，做并联合并
            DPMatrix cur = get_dp(u, v);
            set_dp(u, v, parallel_merge(cur, single_edge));
        }
    }

    queue<int> q;
    for (int i = 1; i <= n; i++) {
        if (adj[i].size() <= 2) q.push(i);
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        // 度数为 1 的点：悬挂点折叠
        if (adj[u].size() == 1) {
            int v = *adj[u].begin();
            if (adj[v].size() <= 1) continue; // 孤立连通块，跳过

            // 找 v 的另一个邻居 w
            int w = -1;
            for (int nxt : adj[v]) {
                if (nxt != u) { w = nxt; break; }
            }
            if (w == -1) continue;

            DPMatrix dp_uv = get_dp(u, v);
            DPMatrix dp_vw = get_dp(v, w);

            // 将 (u, v) 贡献合并到 (v, w) 上
            DPMatrix merged_vw;
            for (int j = 0; j < 3; j++) {
                for (int l = 0; l < 3; l++) {
                    for (int i = 0; i < 3; i++) {
                        for (int k = 0; j + k < 3; k++) {
                            if (dp_uv.val[i][j] >= 0 && dp_vw.val[k][l] >= 0) {
                                merged_vw.val[j + k][l] = max(merged_vw.val[j + k][l], dp_uv.val[i][j] + dp_vw.val[k][l]);
                            }
                        }
                    }
                }
            }

            remove_edge(u, v);
            set_dp(v, w, merged_vw);

            if (adj[v].size() <= 2) q.push(v);
        }
        // 度数为 2 的点：串联合并
        else if (adj[u].size() == 2) {
            auto it = adj[u].begin();
            int x = *it;
            int y = *(++it);

            DPMatrix dp_xu = get_dp(x, u);
            DPMatrix dp_uy = get_dp(u, y);
            DPMatrix new_xy = series_merge(dp_xu, dp_uy);

            remove_edge(x, u);
            remove_edge(y, u);

            if (has_edge(x, y)) {
                // 如果 x, y 之间已有边，再做一次并联合并
                DPMatrix cur_xy = get_dp(x, y);
                set_dp(x, y, parallel_merge(cur_xy, new_xy));
            } else {
                adj[x].insert(y);
                adj[y].insert(x);
                set_dp(x, y, new_xy);
            }

            if (adj[x].size() <= 2) q.push(x);
            if (adj[y].size() <= 2) q.push(y);
        }
    }

    // 统计最终答案
    int ans = 0;
    for (auto& entry : edge_dp) {
        const DPMatrix& mat = entry.second;
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                ans = max(ans, mat.val[i][j]);
            }
        }
    }

    cout << ans << "\n";
}

int main() {
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    if (cin >> t) {
        while (t--) solve();
    }
    return 0;
}