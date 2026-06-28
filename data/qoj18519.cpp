#include <iostream>
#include <vector>
#include <set>
#include <cassert>
using namespace std;

typedef __int128_t i128;

const int MAXN = 200005;

struct Event {
    int y;
    long long w;
};
vector<Event> events[MAXN + 2];

struct QueryEvent {
    int y;
    int id;
    int sign;
};
vector<QueryEvent> queries[MAXN];

i128 T1[MAXN + 2], T2[MAXN + 2], T3[MAXN + 2], T4[MAXN + 2];

void add(int y, i128 v1, i128 v2, i128 v3, i128 v4, int n) {
    for (int i = y; i <= n; i += i & -i) {
        T1[i] += v1; T2[i] += v2; T3[i] += v3; T4[i] += v4;
    }
}

void query_fenwick(int y, i128& r1, i128& r2, i128& r3, i128& r4) {
    r1 = r2 = r3 = r4 = 0;
    for (int i = y; i > 0; i -= i & -i) {
        r1 += T1[i]; r2 += T2[i]; r3 += T3[i]; r4 += T4[i];
    }
}

int p[MAXN], pos[MAXN];
long long ans[MAXN];

int main() {
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n, q;
    if (!(cin >> n >> q)) return 0;

    for (int i = 1; i <= n; ++i) {
        cin >> p[i];
        pos[p[i]] = i;
    }

    set<int> s;
    s.insert(0);
    s.insert(n + 1);

    for (int v = 1; v <= n; ++v) {
        int x = pos[v];
        auto it = s.insert(x).first;
        
        int L1 = 0, L2 = 0, R1 = n + 1, R2 = n + 1;
        
        auto it_L1 = prev(it); L1 = *it_L1;
        if (L1 != 0) L2 = *prev(it_L1);
        
        auto it_R1 = next(it); R1 = *it_R1;
        if (R1 != n + 1) R2 = *next(it_R1);
        
        if (L1 != 0) {
            int i1 = L2 + 1, i2 = L1, j1 = x, j2 = R1 - 1;
            events[i1].push_back({j1, v});          events[i1].push_back({j2 + 1, -v});
            events[i2 + 1].push_back({j1, -v});      events[i2 + 1].push_back({j2 + 1, v});
        }
        
        if (R1 != n + 1) {
            int i1 = L1 + 1, i2 = x, j1 = R1, j2 = R2 - 1;
            events[i1].push_back({j1, v});          events[i1].push_back({j2 + 1, -v});
            events[i2 + 1].push_back({j1, -v});      events[i2 + 1].push_back({j2 + 1, v});
        }
    }

    for (int i = 1; i <= q; ++i) {
        int L, R;
        cin >> L >> R;
        if (L == R) {
            ans[i] = 0;
        } else {
            queries[R].push_back({R, i, 1});
            if (L > 1) queries[L - 1].push_back({R, i, -1});
        }
    }

    int max_y = n + 1;
    for (int X = 1; X <= n; ++X) {
        for (auto& ev : events[X]) {
            int y = ev.y;
            i128 w = ev.w;
            if (y <= max_y) {
                add(y, w, w * y, w * X, w * X * y, max_y);
            }
        }
        
        for (auto& qry : queries[X]) {
            int Y = qry.y;
            i128 r1, r2, r3, r4;
            query_fenwick(Y, r1, r2, r3, r4);
            
            i128 term1 = (i128)(X + 1) * (Y + 1) * r1;
            i128 term2 = (i128)(X + 1) * r2;
            i128 term3 = (i128)(Y + 1) * r3;
            i128 term4 = r4;
            
            i128 res = term1 - term2 - term3 + term4;
            ans[qry.id] += qry.sign * (long long)res;
        }
    }

    for (int i = 1; i <= q; ++i) {
        cout << ans[i] << "\n";
    }

    return 0;
}