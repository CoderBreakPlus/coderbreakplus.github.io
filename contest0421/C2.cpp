#include <bits/stdc++.h>
using namespace std;

using ll = long long;
const int INF = 1e9;

// 记忆化搜索：memo[a][b][turn] 表示 a,b 两堆石子，轮到 turn (0=Alice, 1=Bob) 时的最优回合数
// 由于 subtask 1 中石子数 ≤ 10，直接开数组即可
int memo[15][15][2];
bool vis[15][15][2];

// turn = 0: Alice, turn = 1: Bob
int dfs(int a, int b, int turn) {
    if (a == 0 && b == 0) return 0;
    if (vis[a][b][turn]) return memo[a][b][turn];
    
    int res;
    if (turn == 0) { // Alice 回合，求最小值
        res = INF;
        // 从 a 堆拿
        for (int take = 1; take <= a; take++) {
            res = min(res, 1 + dfs(a - take, b, 1));
        }
        // 从 b 堆拿
        for (int take = 1; take <= b; take++) {
            res = min(res, 1 + dfs(a, b - take, 1));
        }
    } else { // Bob 回合，求最大值
        res = -INF;
        // 从 a 堆拿到 b 堆
        for (int take = 1; take <= a; take++) {
            res = max(res, 1 + dfs(a - take, b + take, 0));
        }
        // 从 b 堆拿到 a 堆
        for (int take = 1; take <= b; take++) {
            res = max(res, 1 + dfs(a + take, b - take, 0));
        }
    }
    
    vis[a][b][turn] = true;
    return memo[a][b][turn] = res;
}

// 计算一对石子的答案
int solve_pair(int x) {
    memset(vis, 0, sizeof(vis));
    return dfs(x, x, 0);
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    int c, n, q;
    cin >> c >> n >> q;
    
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    
    // 预处理每对石子的答案（subtask 1 石子数 ≤ 10）
    vector<int> ans(15);
    for (int i = 0; i <= 10; i++) {
        ans[i] = solve_pair(i);
    }
    
    while (q--) {
        int p, x, y;
        cin >> p >> x >> y;
        if (p == 1) {
            // 查询区间 [x, y]
            ll sum = 0;
            for (int i = x; i <= y; i++) {
                sum += ans[a[i]];
            }
            cout << sum << '\n';
        } else {
            // 修改 a[x] = y
            a[x] = y;
        }
    }
    
    return 0;
}