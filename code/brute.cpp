#include <iostream>
#include <vector>
#include <queue>
#include <cstring>
#include<cassert>
#include<cstdio>

using namespace std;
struct Point {
    int x, y;
};

struct State {
    int x, y;
    int mask;
};

const int BSIZE = 25;   // 棋盘大小扩大到 25x25
const int OFFSET = 12;  // 偏移量设为 12，将 [-12, 12] 映射到 [0, 24]
bool vis[BSIZE][BSIZE][1 << 10]; // 数组加大，N最大为10
Point pawns[12];
Point general;
int n;

// 判断某个位置是否有存活的黑卒
int get_pawn_idx(int x, int y, int mask) {
    for (int i = 0; i < n; ++i) {
        if ((mask & (1 << i)) && pawns[i].x == x && pawns[i].y == y) {
            return i;
        }
    }
    return -1;
}

// 判断某个位置是否有存活的棋子（黑卒或黑将）
bool has_piece(int x, int y, int mask) {
    if (x == general.x && y == general.y) return true;
    return get_pawn_idx(x, y, mask) != -1;
}

void solve() {
    cin >> n >> general.x >> general.y;
    general.x += OFFSET;
    general.y += OFFSET;

    for (int i = 0; i < n; ++i) {
        cin >> pawns[i].x >> pawns[i].y;
        pawns[i].x += OFFSET;
        pawns[i].y += OFFSET;
    }

    memset(vis, 0, sizeof(vis));
    queue<State> q;
    int init_mask = (1 << n) - 1;

    // 初始时，红炮可以部署在任何没有棋子的空位置
    for (int i = 0; i < BSIZE; ++i) {
        for (int j = 0; j < BSIZE; ++j) {
            if (!has_piece(i, j, init_mask)) {
                q.push({i, j, init_mask});
                vis[i][j][init_mask] = true;
            }
        }
    }

    int dx[4] = {-1, 1, 0, 0};
    int dy[4] = {0, 0, -1, 1};

    while (!q.empty()) {
        State curr = q.front();
        q.pop();

        for (int d = 0; d < 4; ++d) {
            // 1. 移动逻辑（不吃子）
            int nx = curr.x + dx[d];
            int ny = curr.y + dy[d];
            while (nx >= 0 && nx < BSIZE && ny >= 0 && ny < BSIZE) {
                if (has_piece(nx, ny, curr.mask)) break; // 遇到棋子停止移动
                if (!vis[nx][ny][curr.mask]) {
                    vis[nx][ny][curr.mask] = true;
                    q.push({nx, ny, curr.mask});
                }
                nx += dx[d];
                ny += dy[d];
            }

            // 2. 吃子逻辑
            nx = curr.x + dx[d];
            ny = curr.y + dy[d];
            int jumped = 0;
            while (nx >= 0 && nx < BSIZE && ny >= 0 && ny < BSIZE) {
                if (has_piece(nx, ny, curr.mask)) {
                    if (jumped == 0) {
                        jumped = 1; // 找到了炮架（隔着的第一个棋子）
                    } else {
                        // 找到了目标（隔着的第二个棋子）
                        if (nx == general.x && ny == general.y) {
                            cout << "YES\n";
                            return;
                        }
                        int p_idx = get_pawn_idx(nx, ny, curr.mask);
                        if (p_idx != -1) {
                            int nmask = curr.mask ^ (1 << p_idx);
                            if (!vis[nx][ny][nmask]) {
                                vis[nx][ny][nmask] = true;
                                q.push({nx, ny, nmask});
                            }
                        }
                        break; // 吃完子后或者被第二个棋子挡住，不能继续跳
                    }
                }
                nx += dx[d];
                ny += dy[d];
            }
        }
    }

    cout << "NO\n";
}

int main() {
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.ans","w",stdout));
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    if (cin >> t) {
        while (t--) {
            solve();
        }
    }
    return 0;
}