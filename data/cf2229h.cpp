// created time: 2026-05-28
#include <bits/stdc++.h>
using namespace std;
#define IL inline
const int N = 3010, mod = 998244353;
IL int add(int x, int y) { return x + y < mod ? x + y : x + y - mod; }
#define t(i) (s[i] & 1)
int n, s[N], lst[N], to[N][2][2][2], nxt[N], __[N][N]; string S;
IL int z(int u, int v, int p, int q) {
  int Q = nxt[min(u, v) + 1];
  return min(to[min(Q, u) + 1][p][q][0], to[min(Q, v) + 1][p][q][1]);
}
IL int F(int u, int v) {
  int &ans = __[u + 1][v + 1];
  return u >= n && v >= n ? 0 : ~ans ? ans : ans = add((u < n && (!t(n) || u < lst[n - 1])) || (v < n && (t(n) || v < lst[n - 1])), add(F(z(u, v, 0, 0), z(u, v, 0, 1)), F(z(u, v, 1, 0), z(u, v, 1, 1))));
}
void ___() {
  cin >> n >> S, nxt[n] = nxt[n + 1] = n;
  for (int i = 0; i < n; ++i) s[i + 1] = s[i] + (S[i] == '1');
  for (int i = 0; i < n; ++i) lst[i] = S[i] == '?' ? i : (!i ? -1 : lst[i - 1]);
  for (int i = n - 1; ~i; --i) nxt[i] = S[i] == '?' ? i : nxt[i + 1];
  for (int p : {0, 1}) for (int q : {0, 1}) for (int v : {0, 1})
    to[n][p][q][v] = to[n + 1][p][q][v] = n;
  for (int i = n - 1; ~i; --i) {
    memcpy(to[i], to[i + 1], sizeof to[i]);
    for (int p : {0, 1}) if (S[i] == '?' || S[i] == p + '0') to[i][p][t(i + 1)][t(i)] = i;
  }
  for (int i = 0; i <= n + 5; ++i) for (int j = 0; j <= n + 5; ++j) __[i][j] = -1;
  cout << F(-1, n) << '\n';
}
int main() {
  ios::sync_with_stdio(0); cin.tie(0);
  int _; cin >> _; while (_--) ___();
}
