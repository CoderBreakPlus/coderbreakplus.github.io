#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;

const int mod[2] = {1000000007, 1000000009}, base = 12331337;
int n;
char s[100005];
int pw[2][100005];
int hsh[2][100005];

inline int gethash(int l, int r, int o) {
    return (hsh[o][r] + (ull)(mod[o] - hsh[o][l - 1]) * pw[o][r - l + 1]) % mod[o];
}

inline int lcp(int x, int y) {
    int l = 1, r = n - max(x, y) + 1, ret = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (gethash(x, x + mid - 1, 0) == gethash(y, y + mid - 1, 0) &&
            gethash(x, x + mid - 1, 1) == gethash(y, y + mid - 1, 1))
            ret = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ret;
}

inline int lcs(int x, int y) {
    int l = 1, r = min(x, y), ret = 0;
    while (l <= r) {
        int mid = (l + r) >> 1;
        if (gethash(x - mid + 1, x, 0) == gethash(y - mid + 1, y, 0) &&
            gethash(x - mid + 1, x, 1) == gethash(y - mid + 1, y, 1))
            ret = mid, l = mid + 1;
        else r = mid - 1;
    }
    return ret;
}

vector<tuple<int, int, int>> runs;

inline int cmp(int x, int y) {
    int p = lcp(x, y);
    return s[x + p] < s[y + p];
}

inline void get_run(int l, int r) {
    if (r > n || s[l] != s[r]) return;
    int r1 = r + lcp(l, r) - 1, l1 = l - lcs(l, r) + 1;
    if (r1 - l1 + 1 >= 2 * (r - l)) runs.emplace_back(l1, r1, r - l);
}

int z[100005], tot;
inline void lyndon(int o) {
    z[0] = n + 1, tot = 0;
    for (int i = n; i >= 1; i--) {
        while (tot && cmp(i, z[tot]) == o) --tot;
        get_run(i, z[tot]);
        z[++tot] = i;
    }
}

void calc_runs(const string& str, ll& s1, ll& s2, ll& s3) {
    n = str.length();
    for (int i = 1; i <= n; i++) s[i] = str[i - 1];
    s[n + 1] = 0;

    for (int o : {0, 1}) {
        pw[o][0] = 1;
        for (int i = 1; i <= n; i++)
            pw[o][i] = (ull)pw[o][i - 1] * base % mod[o];
        for (int i = 1; i <= n; i++)
            hsh[o][i] = ((ull)hsh[o][i - 1] * base + s[i]) % mod[o];
    }

    runs.clear();
    lyndon(0), lyndon(1);
    sort(runs.begin(), runs.end());
    runs.erase(unique(runs.begin(), runs.end()), runs.end());

    s1 = 0, s2 = 0, s3 = 0;
    for (auto &sb : runs) {
        int l = std::get<0>(sb);
        int r = std::get<1>(sb);
        int p = std::get<2>(sb);
        s1++;
        s2 += (r - l - 2 * p + 2);
        s3 += (r - l + 1);
    }
}

// 贪心搜索：逐步添加 0 或 1 使得目标函数极大化
string build_greedy(int target) {
    string g = "0";
    for (int i = 1; i < 1200; ++i) { // 防止超时，规模控制在 1200
        string c0 = g + "0";
        string c1 = g + "1";
        ll a10, a20, a30; calc_runs(c0, a10, a20, a30);
        ll a11, a21, a31; calc_runs(c1, a11, a21, a31);
        if (target == 1) {
            if (a10 > a11) g = c0; else g = c1;
        } else if (target == 2) {
            if (a20 > a21) g = c0; else g = c1;
        } else {
            if (a30 > a31) g = c0; else g = c1;
        }
    }
    string g_full = "";
    while (g_full.length() < 100000) g_full += g;
    return g_full.substr(0, 100000);
}

int main() {
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    srand(42);
    
    vector<string> cands;

    // 1. Fibonacci (大量平凡平方串的极佳构造 A2 很高)
    string fib = "0", fib_prev = "1";
    while(fib.length() < 100000) {
        string next = fib + fib_prev;
        fib_prev = fib; fib = next;
    }
    cands.push_back(fib.substr(0, 100000));

    // 2. Matsubara-Runs 最多 (已知拥有几乎最多 Runs 数量的渐近最优序列 A1 极高)
    string m = "0";
    while(m.length() < 100000) {
        string next = "";
        for(char c : m) next += (c == '0' ? "0010" : "1011");
        m = next;
    }
    cands.push_back(m.substr(0, 100000));

    // 3. 最大化指数和序列
    string e = "0";
    while(e.length() < 100000) {
        string next = "";
        for(char c : e) next += (c == '0' ? "010010" : "101101");
        e = next;
    }
    cands.push_back(e.substr(0, 100000));

    // 4. 倍周期序列 (Period Doubling)
    string pd = "0";
    while(pd.length() < 100000) {
        string next = "";
        for(char c : pd) next += (c == '0' ? "01" : "00");
        pd = next;
    }
    cands.push_back(pd.substr(0, 100000));
    
    // 5. 不断套入变长的复合块
    string s_11 = "0";
    while(s_11.length() < 100000) {
        s_11 = s_11 + "0" + s_11 + "1";
    }
    cands.push_back(s_11.substr(0, 100000));
    
    // 6. Chirp 式串联
    string s_7 = "";
    for(int k=1; s_7.length()<100000; ++k) {
        s_7 += string(k, '0') + string(k, '1');
    }
    cands.push_back(s_7.substr(0, 100000));

    // 7. 高复合 Chirp
    string s_16 = "";
    for(int k=1; s_16.length()<100000; ++k) {
        for(int j=0; j<k; ++j) s_16 += string(k, '0') + "1";
    }
    cands.push_back(s_16.substr(0, 100000));

    // 8. 加入贪心构造 (防止漏掉针对特定指标的极端优解)
    cands.push_back(build_greedy(1));
    cands.push_back(build_greedy(2));
    cands.push_back(build_greedy(3));

    // 9. 针对 A3 的随机爬山构造 (防贪心陷阱)
    string hc = "01";
    while(hc.length() < 800) hc += (rand()%2 ? '1' : '0');
    ll cur_a1, cur_a2, cur_a3; calc_runs(hc, cur_a1, cur_a2, cur_a3);
    for(int step=0; step<1500; ++step) {
        int idx = rand() % 800;
        hc[idx] = (hc[idx] == '0' ? '1' : '0');
        ll n_a1, n_a2, n_a3; calc_runs(hc, n_a1, n_a2, n_a3);
        if(n_a3 >= cur_a3) {
            cur_a3 = n_a3;
        } else {
            hc[idx] = (hc[idx] == '0' ? '1' : '0'); 
        }
    }
    string hc_full = "";
    while(hc_full.length() < 100000) hc_full += hc;
    cands.push_back(hc_full.substr(0, 100000));

    // =============================
    // 评估所有生成的候选字符串，只选最好
    // =============================
    ll max_a1 = -1, max_a2 = -1, max_a3 = -1;
    string best_s1, best_s2, best_s3;

    for (const string& str_cand : cands) {
        if(str_cand.length() != 100000) continue;
        ll a1, a2, a3;
        calc_runs(str_cand, a1, a2, a3);
        
        if (a1 > max_a1) { max_a1 = a1; best_s1 = str_cand; }
        if (a2 > max_a2) { max_a2 = a2; best_s2 = str_cand; }
        if (a3 > max_a3) { max_a3 = a3; best_s3 = str_cand; }
    }

    // 打印答案 (在评测机直接获得高分输出)
    cout << 2 << "\n";
    cout << best_s1 << "\n";
    cout << best_s2 << "\n";

    const int MM = 1e5;
    for(int i=0;i<MM/4;i++)cout<<"ab";
    for(int i=0;i<MM/4;i++)cout<<"ba";

    return 0;
}