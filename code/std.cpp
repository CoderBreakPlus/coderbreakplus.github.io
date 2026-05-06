#pragma GCC optimize(3)
#pragma GCC optimize("Ofast")
#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef unsigned long long ull;

const int N = 1e5 + 5;

namespace SAM {
	int len[N << 1], fa[N << 1], son[N << 1][26], lst, cnt;

	inline void ins(int p, int v) {
		len[p] = len[lst] + 1;
		while (lst && !son[lst][v]) {
			son[lst][v] = p;
			lst = fa[lst];
		}
		if (!son[lst][v]) {
			son[lst][v] = p;
		} else {
			int q = son[lst][v];
			if (len[q] == len[lst] + 1) {
				fa[p] = q;
			} else {
				int u = ++cnt;
				len[u] = len[lst] + 1;
				fa[u] = fa[q];
				memcpy(son[u], son[q], sizeof(son[u]));
				fa[p] = fa[q] = u;
				while (son[lst][v] == q) {
					son[lst][v] = u;
					lst = fa[lst];
				}
			}
		}
		lst = p;
	}
}

struct node {
	int x, y, d;

	node() {}
	node(int x, int y, int d) : x(x), y(y), d(d) {}
};

int n, m, q, fa[N << 1], dep[N << 1], siz[N << 1], son[N << 1], ql[N], qr[N], ans[N];

string s;

vector<int> E[N << 1];
vector<node> P;

set<int> S[N << 1];

inline void dfs(int u) {
	siz[u] = 1;
	son[u] = -1;
	for (int v : E[u]) {
		dfs(v);
		siz[u] += siz[v];
		if (son[u] == -1 || siz[v] > siz[son[u]]) {
			son[u] = v;
		}
	}
	if (son[u]) {
		swap(S[u], S[son[u]]);
	}
	if (1 <= u && u <= n) {
		auto it = S[u].lower_bound(u);
		if (it != S[u].end()) {
			P.emplace_back(u, *it, dep[u]);
		}
		if (it != S[u].begin()) {
			P.emplace_back(*prev(it), u, dep[u]);
		}
		S[u].emplace(u);
	}
	for (int v : E[u]) {
		if (v == son[u]) {
			continue;
		}
		for (int x : S[v]) {
			auto it = S[u].lower_bound(x);
			if (it != S[u].end()) {
				P.emplace_back(x, *it, dep[u]);
			}
			if (it != S[u].begin()) {
				P.emplace_back(*prev(it), x, dep[u]);
			}
		}
		for (int x : S[v]) {
			S[u].emplace(x);
		}
		set<int>().swap(S[v]);
	}
}

struct sgt {
	int tree[N << 1];

	inline int get_id(int l, int r) {
		return (l + r) | (l != r);
	}

	inline void pushup(int p, int ls, int rs) {
		tree[p] = max(tree[ls], tree[rs]);
	}

	inline void update(int l, int r, int pos, int k) {
		int p = get_id(l, r);
		if (l == r) {
			tree[p] = k;
			return;
		}
		int mid = (l + r) >> 1;
		int ls = get_id(l, mid), rs = get_id(mid + 1, r);
		if (pos <= mid) {
			update(l, mid, pos, k);
		} else {
			update(mid + 1, r, pos, k);
		}
		pushup(p, ls, rs);
	}

	inline int query(int l, int r, int ql, int qr) {
		int p = get_id(l, r);
		if (ql <= l && r <= qr) {
			return tree[p];
		}
		int mid = (l + r) >> 1, res = 0;
		if (ql <= mid) {
			res = max(res, query(l, mid, ql, qr));
		}
		if (qr > mid) {
			res = max(res, query(mid + 1, r, ql, qr));
		}
		return res;
	}
} t1, t2;

multiset<int> c[N];
vector<node> upd1[N], upd2[N];
vector<int> qry[N];

int cnt1[N], cnt2[N], mc[N];

int main() {
#ifdef LOCAL
	assert(freopen("test.in", "r", stdin));
	assert(freopen("test.out", "w", stdout));
#endif
	cin.tie(nullptr) -> sync_with_stdio(false);
	cin >> n >> q >> s;
	s = "#" + s;
	SAM::cnt = n;
	for (int i = n; i; --i) {
		SAM::ins(i, s[i] - 'a');
	}
	m = SAM::cnt;
	for (int i = 1; i <= m; ++i) {
		fa[i] = SAM::fa[i];
		dep[i] = SAM::len[i];
	}
	for (int i = 1; i <= m; ++i) {
		E[fa[i]].emplace_back(i);
		cout<<i<<" fa="<<fa[i]<<endl;
	}
	dfs(0);
	for (int i = 1; i <= n; ++i) {
		c[i].emplace(0);
	}
	for (auto [x, y, d] : P) {
		++cnt1[y], ++cnt2[y + d];
	}
	for (int i = 1; i <= n; ++i) {
		upd1[i].reserve(cnt1[i]);
		upd2[i].reserve(cnt2[i]);
	}
	for (auto [x, y, d] : P) {
		upd1[y].emplace_back(x, y, d);
		upd2[y + d].emplace_back(x, y, d);
	}
	for (int i = 1; i <= q; ++i) {
		cin >> ql[i] >> qr[i];
		qry[qr[i]].emplace_back(i);
	}
	for (int i = 1; i <= n; ++i) {
		for (auto [x, y, d] : upd1[i]) {
			c[x].emplace(n - y + 1);
			t1.update(1, n, x, *prev(c[x].end()));
		}
		for (auto [x, y, d] : upd2[i]) {
			c[x].erase(c[x].find(n - y + 1));
			t1.update(1, n, x, *prev(c[x].end()));
		}
		for (auto [x, y, d] : upd2[i]) {
			mc[x] = max(mc[x], d);
			t2.update(1, n, x, mc[x]);
		}
		for (int id : qry[i]) {
			ans[id] = max(t2.query(1, n, ql[id], qr[id]), qr[id] - (n - t1.query(1, n, ql[id], qr[id])));
		}
	}
	for (int i = 1; i <= q; ++i) {
		cout << qr[i] - ql[i] + 1 - ans[i] << "\n";
	}
	return 0;
}
