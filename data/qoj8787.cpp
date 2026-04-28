// created time: 2026-04-28 17:12:40
#include <bits/stdc++.h>
#define pb emplace_back
#define fst first
#define scd second
#define mkp make_pair
#define mems(a, x) memset((a), (x), sizeof(a))

using namespace std;
typedef long long ll;
typedef double db;
typedef unsigned long long ull;
typedef long double ldb;
typedef pair<int, int> pii;

const int maxn = 10050;

int n, m, K;
vector<int> G[maxn];
bool vis[maxn];
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());

void solve() {
	scanf("%d%d%d", &n, &m, &K);
	set<pii> T;
	while (m--) {
		int u, v;
		scanf("%d%d", &u, &v);
		if (u > v) {
			swap(u, v);
		}
		T.emplace(u, v);
	}
	while (K--) {
		mems(vis, 0);
		for (int i = 1; i <= n; ++i) {
			vector<int>().swap(G[i]);
		}
		for (pii p : T) {
			int u = p.fst, v = p.scd;
			G[u].pb(v);
			G[v].pb(u);
		}
		int x = rnd() % n + 1;
		vis[x] = 1;
		vector<int> S(1, x);
		while ((int)S.size() < n) {
			if (rnd() & 1) {
				reverse(S.begin(), S.end());
			}
			int x = S.back();
			shuffle(G[x].begin(), G[x].end(), rnd);
			bool fl = 1;
			for (int y : G[x]) {
				if (!vis[y]) {
					S.pb(y);
					fl = 0;
					vis[y] = 1;
					break;
				}
			}
			if (fl) {
				for (int i = 0; i + 1 < (int)S.size(); ++i) {
					if (S[i] == G[x].back() || S[i] == G[x][0]) {
						reverse(S.begin() + i + 1, S.end());
						break;
					}
				}
			}
		}
		for (int x : S) {
			printf("%d ", x);
		}
		putchar('\n');
		for (int i = 1; i < n; ++i) {
			T.erase(mkp(min(S[i - 1], S[i]), max(S[i - 1], S[i])));
		}
	}
}

int main() {
	int T = 1;
	// scanf("%d", &T);
	while (T--) {
		solve();
	}
	return 0;
}