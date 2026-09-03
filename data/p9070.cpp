// created time: 2026-09-03 15:29:37
#include <algorithm>
#include <numeric>
#include <iostream>

using namespace std;

const int kN = 201;

int tt, n, a[kN][kN], d[kN][kN], e[kN][kN], p[kN], v[kN], vc;

bool F(int x) {
  if (v[x] == vc) {
    return 0;
  }
  v[x] = vc;
  for (int i = 1; i <= n; ++i) {
    if (e[x][i] && (!p[i] || F(p[i]))) {
      return p[i] = x;
    }
  }
  return 0;
}

int main() {
  ios::sync_with_stdio(0), cin.tie(0);
  for (cin >> tt; tt--; ) {
    cin >> n;
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        cin >> a[i][j];
      }
    }
    for (int i = 1; i <= n; ++i) {
      iota(d[i] + 1, d[i] + n + 1, 1);
    }
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j <= n; ++j) {
        ++e[i][a[i][j]];
      }
    }
    for (int k = 1; k <= n; ++k) {
      fill_n(p + 1, n, 0);
      for (int i = 1; i <= n; ++i) {
        ++vc, F(i);
      }
      for (int i = 1; i <= n; ++i) {
        int r = p[i];
        --e[r][i];
        int j = k;
        for (; a[r][d[r][j]] != i; ++j) {
        }
        swap(d[r][k], d[r][j]);
      }
    }
    cout << n * (n - 1) / 2 << '\n';
    for (int i = 1; i <= n; ++i) {
      for (int j = 1; j < i; ++j) {
        cout << i << ' ' << d[i][j] << ' ' << j << ' ' << d[j][i] << '\n';
      }
    }
  }
  return 0;
}
