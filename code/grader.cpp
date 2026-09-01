#include <iostream>
#include <vector>
#include <cassert>

using std::vector;

long long compute_min_depth(int N, vector<int> P, vector<int> C, vector<int> D);

int main() {
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);

    int N;
    if (!(std::cin >> N)) return 0;

    vector<int> P(N - 1), C(N - 1), D(N - 1);
    for (int i = 0; i < N - 1; i++) {
        std::cin >> P[i] >> C[i] >> D[i];
    }

    long long ans = compute_min_depth(N, P, C, D);
    std::cout << ans << std::endl;

    return 0;
}
