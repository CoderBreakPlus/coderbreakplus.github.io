// created time: 2026-05-28
// border length: i, j
// let x=n-i, y=n-j
// number of connected components: max(gcd(x,y), x+y-n)

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const int mod = 1e9 + 7;

inline ll qpow(ll a, ll b) {
    ll ans = 1, base = a;
    while (b) {
        if (b & 1) ans = ans * base % mod;
        base = base * base % mod; b >>= 1;
    }
    return ans;
}
inline ll INV(ll x) { return qpow(x, mod - 2); }

int n, k;
vector<int> pr[200005];

void pre_primes(int limit) {
    for (int i = 2; i <= limit; i++) {
        if (pr[i].empty()) {
            for (int j = i; j <= limit; j += i) {
                pr[j].push_back(i);
            }
        }
    }
}

int count_coprime(int s, int R) {
    if (R <= 0) return 0;
    int res = 0;
    int k_sz = pr[s].size();
    for (int mask = 0; mask < (1 << k_sz); mask++) {
        int p = 1, sign = 1;
        for (int i = 0; i < k_sz; i++) {
            if ((mask >> i) & 1) {
                p *= pr[s][i];
                sign = -sign;
            }
        }
        res += sign * (R / p);
    }
    return res;
}

void procedure() {
    cin >> n >> k;
    pre_primes(2 * n);
    ll ans = 0;
    for (int d = 1; d < n; d++) {
        int M = (n - 1) / d;
        for (int s = 2; s <= 2 * M; s++) {
            int L = max(1, s - M);
            int R = min(s - 1, M);
            if (L > R) continue;
            int cnt = count_coprime(s, R) - count_coprime(s, L - 1);
            if (!cnt) continue;
            int c = max(d, s * d - n);
            ans = (ans + 1LL * cnt * qpow(k, c)) % mod;
        }
    }
    ans = ans * qpow(INV(k), n) % mod;
    cout << ans << "\n";
}

int main() {
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    procedure();
    return 0;
}