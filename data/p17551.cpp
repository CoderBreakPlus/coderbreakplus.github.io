// created time: 2026-11-20 20:03:01
#include <bits/stdc++.h>
using namespace std;
const int mod = 998244353;
void add(int &a, int b) {
    a += b;
    if (a >= mod) a -= mod;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    string s;
    cin >> s;
    int n = s.size(), k = n / 3, m = k + 1;
    vector<vector<int>> f(m, vector<int>(m)), g = f;
    f[0][0] = 1;
    for (char c : s) {
        vector<vector<int>> nf(m, vector<int>(m)), ng = nf;
        for (int a = 0; a <= k; ++a) {
            for (int b = 0; a + b <= k; ++b) if (f[a][b]) {
                if (c != 'B') add(nf[a + (a + b < k)][b], f[a][b]);
                if (c != 'A') {
                    if (a) add(nf[a - 1][b + 1], f[a][b]);
                    else add(nf[a][b], f[a][b]);
                }
            }
        }
        for (int r = 0; r < k; ++r) {
            for (int b = 0; b <= r; ++b) if (g[r][b]) {
                if (c != 'A') add(ng[r][min(r, b + 1)], g[r][b]);
                if (c != 'B' && b) add(ng[r - 1][b - 1], g[r][b]);
            }
        }
        if (c != 'B') {
            for (int b = 1; b <= k; ++b) {
                int suffix = 0;
                for (int t = k; t >= 1; --t) {
                    if (t >= b) add(suffix, f[t - b][b]);
                    add(ng[t - 1][min(t - 1, b - 1)], suffix);
                }
            }
        }
        f.swap(nf);
        g.swap(ng);
    }
    cout << g[0][0] << '\n';
}
