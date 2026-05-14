#include <bits/stdc++.h>
#include "gems.h"
signed main() {
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    int c, n, m;
    std::cin >> c >> n >> m;
    std::vector<int> u(n - 1), v(n - 1), a(m), d(m);
    for (int i = 0; i < n - 1; i++) std::cin >> u[i] >> v[i];
    for (int i = 0; i < m; i++) std::cin >> a[i];
    for (int i = 0; i < m; i++) std::cin >> d[i];
    gems(c, n, m, u, v, a, d);
    int q;
    std::cin >> q;
    for (int i = 1; i <= q; i++) {
        int x, l, r;
        std::cin >> x >> l >> r;
        std::cout << query(x, l, r) << '\n';
    }
    return 0;
}
