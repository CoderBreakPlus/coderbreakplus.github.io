// created time: 2026-11-16 20:33:03
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>
#define mems(x, v) memset(x, v, sizeof x)
#define mcpy(x, y) memcpy(x, y, sizeof x)
using namespace std;
typedef pair <int, int> pii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double wisdom;

const int mod = 998244353;
int p[505][505], temp[505], dp[505][505], f[505][505]; bool fl[505][505];
int main() {
	int n, m; cin >> n >> m;
	for (int i = 1; i <= m; i++) {
		for (int j = 1; j <= n; j++) cin >> p[i][j];
		for (int j = n; j; j--) p[i][j] = (p[i][j] - p[i][1] + n) % n + 1;
	}
	for (int i = 2; i <= m; i++) {for (int j = 1; j <= n; j++) temp[p[1][j]] = p[i][j]; mcpy(p[i], temp);}
	for (int i = 1; i <= n; i++) p[1][i] = i;

	mems(fl, true);
	for (int t = 1; t <= m; t++) {
		for (int l = 1; l <= n; l++) {
			int mn = 1e9, mx = -1e9;
			for (int r = l; r <= n; r++) mn = min(mn, p[t][r]), mx = max(mx, p[t][r]), fl[l][r] &= (r - l + 1 == mx - mn + 1);
		}
	}
	for (int i = 1; i <= n + 1; i++) f[i][i - 1] = 1;
	for (int len = 1; len <= n; len++) for (int i = 1, j = len; j <= n; i++, j++) {
		if (fl[i][j]) {for (int k = i; k <= j; k++) dp[i][j] = (dp[i][j] + 1ll * f[i][k - 1] * f[k + 1][j]) % mod;}
		f[i][j] = dp[i][j]; for (int k = i; k < j; k++) f[i][j] = (f[i][j] + 1ll * f[i][k] * dp[k + 1][j]) % mod;
	}
	cout << f[2][n];
	return 0;
}
