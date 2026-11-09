// created time: 2026-11-09 09:57:27
using namespace std;

using ll = long long;
const int mod = 1000000007;
const int K = 3 * 50 + 1;

int qpow(ll a, ll b) {
    ll ans = 1;
    for (; b; b >>= 1, a = a * a % mod)
        if (b & 1) ans = ans * a % mod;
    return ans;
}

const int Q1 = (mod + 1) / 4;
const int Q2 = 2 * Q1, Q3 = 3 * Q1;
const int down00 = 1ll * Q3 * Q2 % mod;
const int down10 = 1ll * Q1 * (1 + Q1) % mod;
const int down11 = 1ll * Q1 * Q1 % mod;
const int downDown = 1ll * Q3 * Q3 % mod;
const int right10 = 1ll * Q3 * Q1 % mod;

using Vec = array<int, K>;
struct Mat {
    int a[K][K]{};
};

inline void addmod(int &x, ll y) {
    x = (x + y) % mod;
}

// Each row stores dp[1][1], dp[1][0], dp[0][0], in that order.
// The omitted dp[0][1] is dp[0][0] / 2.
void finishColumn(Vec &v, int s) {
    for (int i = 0; i + 3 < s; i += 3) {
        int down = v[i + 2];
        addmod(v[i + 3], 1ll * down * down11);
        addmod(v[i + 4], 1ll * down * down10);
        addmod(v[i + 5], 1ll * down * downDown);
    }
    addmod(v[s], 1ll * v[s - 1] * (1 + Q2));
}

Vec nextColumn(const Vec &v, int s) {
    Vec w{};
    w[s] = v[s];
    for (int i = 0; i < s; i += 3) {
        w[i] = 1ll * v[i] * right10 % mod;
        w[i + 1] = (1ll * v[i] * down00 + 1ll * v[i + 1] * right10) % mod;
        w[i + 2] = 1ll * v[i + 1] * Q2 % mod;
    }
    finishColumn(w, s);
    return w;
}

Mat square(const Mat &a, int s) {
    Mat b;
    for (int i = 0; i <= s; ++i)
        for (int k = i; k <= s; ++k) {
            int x = a.a[i][k];
            if (!x) continue;
            for (int j = k; j <= s; ++j)
                addmod(b.a[i][j], 1ll * x * a.a[k][j]);
        }
    return b;
}

Vec multiply(const Vec &v, const Mat &a, int s) {
    Vec w{};
    for (int i = 0; i <= s; ++i)
        for (int j = i; j <= s; ++j)
            addmod(w[j], 1ll * v[i] * a.a[i][j]);
    return w;
}

void procedure() {
    int n;
    ll m;
    cin >> n >> m;
    int s = 3 * n;

    Vec v{};
    v[0] = 1ll * Q3 * down11 % mod;
    v[1] = 1ll * Q3 * down10 % mod;
    v[2] = down00;
    finishColumn(v, s);

    Mat a;
    for (int i = 0; i <= s; ++i) {
        Vec unit{};
        unit[i] = 1;
        Vec row = nextColumn(unit, s);
        copy_n(row.begin(), s + 1, a.a[i]);
    }

    for (ll e = m - 1; e; ) {
        if (e & 1) v = multiply(v, a, s);
        e >>= 1;
        if (e) a = square(a, s);
    }

    int escape = v[s];
    for (int i = 0; i < s; i += 3)
        addmod(escape, v[i] + v[i + 1]);
    cout << (mod + 1ll - escape) * qpow(4, (n + 1) * (m + 1)) % mod << '\n';
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int T;
    cin >> T;
    while (T--) procedure();
    return 0;
}
