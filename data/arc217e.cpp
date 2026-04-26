// created time: 2026-04-26 19:52:26
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int maxn = 2e6 + 5, mod = 998244353;
int inv[maxn], n, k;
void prepare() {
	inv[0] = inv[1] = 1;
	for (int i = 2; i <= n + k; i++)
		inv[i] = (mod - mod / i) * inv[mod % i] % mod;
}
int ans, sz[maxn];
vector<int> e[maxn];
void dfs(int u, int fa) {
	sz[u] = 1;
	for (int i = 0; i < e[u].size(); i++) {
		int v = e[u][i];
		if(v == fa)
			continue;
		dfs(v, u);	
		sz[u] += sz[v];
	}
	ans = (ans + sz[u] * (n - sz[u])) % mod;
}
void solve() {
	cin >> n >> k;
	prepare();
	for (int i = 1; i <= n; i++)
		e[i].clear();
	ans = 0;
	for (int i = 1; i < n; i++) {
		int x, y; cin >> x >> y;
		e[x].push_back(y);
		e[y].push_back(x);
	}
	dfs(1, 0);
	for (int i = 1; i <= k; i++)
		ans = ans * inv[n + i - 2] % mod * (n + i - 1 + 2) % mod;
	cout << ans << endl;
}
signed main() {
	int T; cin >> T;
	while(T--)
		solve();
	return 0;
}
