#include <bits/stdc++.h>

#define sz(a) int((a).size())
#define all(a) (a).begin(), (a).end()
#define folr(i, a, n) for (auto i = (a); i <= (n); ++i)
#define forl(i, n, a) for (auto i = (n); i >= (a); --i)

using namespace std;
using ll = long long;

string to_string(char v) {
    string a = "";
    a += v;
    return a;
}

template<class A> string to_string(const A& v) {
    string s = "{";
    for (const auto& x : v) s += (sz(s) > 1 ? ", " : "") + to_string(x);
    return s += "}";
}

void debug_out() { cerr << '\n'; }

template<class U, class... T> void debug_out(const U& x, const T&... args) {
    cerr << ' ' << to_string(x);
    debug_out(args...);
}

mt19937 rng(__builtin_ia32_rdtsc());

template<class T> T rnd(T a, T b) {
    return uniform_int_distribution<T>(a, b)(rng);
}

#define sc(x) cerr << "\033[" << x << "m"
#define debug(...) sc(96), cerr << "[" << #VA_ARGS << "]:", debug_out(VA_ARGS), sc(39)

const int INF = 1e15;

void solve(const int& ic) {
    int n, m, q;
    cin >> n >> m >> q;

    vector<int> h(n), nh(n, -1);
    folr(i, 0, n - 1) cin >> h[i];

    vector<vector<int>> G(n);
    folr(i, 0, m - 1) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        G[x].push_back(y);
        G[y].push_back(x);
    }

    vector<vector<int>> fa(21, vector<int>(n, 0)), su(21, vector<int>(n, 0));
    vector<vector<int>> mn(21, vector<int>(n, INF));

    folr(i, 0, 20) iota(all(fa[i]), 0);

    auto find = [&](auto&& self, int t, int x) {
        if (x == fa[t][x]) return x;
        return fa[t][x] = self(self, t, fa[t][x]);
    };

    auto merge = [&](int t, int x, int y) {
        int fx = find(find, t, x), fy = find(find, t, y);
        if (fx == fy) return;
        fa[t][fx] = fy;
        su[t][fy] += su[t][fx];
    };

    folr(i, 0, 20) {
        int l = (1 << i), r = (1 << (i + 1)) - 1;
        vector<int> vis(n, 0);

        folr(j, 0, n - 1) su[i][j] = h[j];

        folr(j, 0, n - 1) {
            if (h[j] < l) {
                vis[j] = 1;
                for (auto v : G[j]) {
                    if (vis[v]) merge(i, j, v);
                }
            }
        }

        folr(j, 0, n - 1) {
            if (l <= h[j] && h[j] <= r) {
                for (auto v : G[j]) {
                    int t = find(find, i, v);
                    mn[i][t] = min(mn[i][t], h[j]);
                }
            }
        }
    }

    auto work = [&](int x, int v) {
        int now;
        if (nh[x] != -1) {
            if (v < nh[x]) return v;
            else if (v + nh[x] < h[x]) return v + nh[x];
        } else if (v < h[x]) return v;

        now = h[x];

        folr(i, 0, 19) {
            int l = (1 << i), r = (1 << (i + 1)) - 1, fx = find(find, i + 1, x);
            if (v + now > r) {
                now = su[i + 1][fx];
                continue;
            }
            if (v + now < mn[i][find(find, i, x)]) return v + now;
            now = su[i + 1][fx];
        }
        return v + now;
    };

    vector<int> vi(n, 0);

    auto modify = [&](int x, int t) {
        nh[x] = t;
        folr(i, 0, 20) {
            int l = (1 << i), r = (1 << (i + 1)) - 1;
            if (l <= t && t <= r) {
                int fv;
                fv = find(find, i, x);
                mn[i][fv] = min(mn[i][fv], t);
                for (auto v : G[x]) {
                    fv = find(find, i, v);
                    mn[i][fv] = min(mn[i][fv], t);
                }
            } else if (l > t) {
                int fv;
                fv = find(find, i, x);
                if (!vi[fv]) su[i][fv] += t, vi[fv] = 1;
                for (auto v : G[x]) {
                    fv = find(find, i, v);
                    if (!vi[fv]) su[i][fv] += t, vi[fv] = 1;
                }
                fv = find(find, i, x);
                vi[fv] = 0;
                for (auto v : G[x]) {
                    fv = find(find, i, v);
                    vi[fv] = 0;
                }
            }
        }
        return;
    };

    folr(i, 0, q - 1) {
        int op;
        cin >> op;
        if (op == 2) {
            int x, v;
            cin >> x >> v;
            x--;
            cout << work(x, v) << "\n";
        } else {
            int x, t;
            cin >> x >> t;
            x--;
            modify(x, t);
        }
    }
}

signed main() {
    cin.tie(nullptr)->sync_with_stdio(false);
    freopen("1.in", "r", stdin);
    int tt = 1;
    folr(ic, 0, tt - 1) solve(ic);
    return 0;
}