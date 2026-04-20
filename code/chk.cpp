#include "testlib.h"
#include <bits/stdc++.h>
using namespace std;

int main(int argc, char* argv[]) {
    registerTestlibCmd(argc, argv);
    // 读取输入数据
    int n = inf.readInt();
    int m = inf.readInt();
    vector<string> a_orig(n), b_orig(m);
    for (int i = 0; i < n; i++) a_orig[i] = inf.readToken();
    for (int i = 0; i < m; i++) b_orig[i] = inf.readToken();
    int q = inf.readInt();
    vector<long long> ks(q);
    for (int i = 0; i < q; i++) ks[i] = inf.readLong();

    // 预处理 A 和 B 排序
    vector<pair<string, int>> A_sorted, B_sorted;
    for (int i = 0; i < n; i++) A_sorted.emplace_back(a_orig[i], i);
    for (int i = 0; i < m; i++) B_sorted.emplace_back(b_orig[i], i);
    sort(A_sorted.begin(), A_sorted.end());
    sort(B_sorted.begin(), B_sorted.end());

    // 将 B 的字符串单独取出以便二分
    vector<string> B_strs(m);
    for (int i = 0; i < m; i++) B_strs[i] = B_sorted[i].first;

    for (int i = 0; i < q; i++) {
        int f = ouf.readInt(1, n, "f");
        int s = ouf.readInt(1, m, "s");
        string x = a_orig[f-1] + b_orig[s-1];

        // 计算严格小于 x 的数量
        long long less = 0;
        for (const auto& p : A_sorted) {
            const string& a = p.first;
            int cmp = a.compare(x);
            if (cmp < 0) {
                // a < x
                // 检查 a 是否是 x 的前缀
                if (x.size() > a.size() && x.compare(0, a.size(), a) == 0) {
                    // a 是前缀，需要在 B 中二分
                    string suffix = x.substr(a.size());
                    int pos = lower_bound(B_strs.begin(), B_strs.end(), suffix) - B_strs.begin();
                    less += pos; // B 中所有小于 suffix 的数量
                } else {
                    // a 不是前缀，所有 a+b < x
                    less += m;
                }
            } else {
                // a >= x，后面的 a 只会更大，可以跳出循环
                break;
            }
        }

        // 计算等于 x 的数量
        long long eq = 0;
        for (const auto& p : A_sorted) {
            const string& a = p.first;
            if (x.size() < a.size()) continue;
            if (x.compare(0, a.size(), a) != 0) continue; // a 不是前缀
            string suffix = x.substr(a.size());
            // 检查 suffix 是否在 B 中
            if (binary_search(B_strs.begin(), B_strs.end(), suffix)) {
                ++eq;
            }
        }

        long long rankL = less + 1;
        long long rankR = less + eq;
        if (ks[i] < rankL || ks[i] > rankR) {
            quitf(_wa, "query %d: k=%lld, but string appears at ranks [%lld,%lld]", i+1, ks[i], rankL, rankR);
        }
    }

    // 检查选手输出是否有多余内容
    // ouf.readEof();
    quitf(_ok, "correct");
}