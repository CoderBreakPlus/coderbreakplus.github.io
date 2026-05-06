// brute.cpp
#include<bits/stdc++.h>
using namespace std;

int n, m, q;
vector<pair<int,int>> acts; // (start, end)

int solve_brute(int L, int R) {
    // 筛选完全在 [L,R] 内的活动
    vector<pair<int,int>> valid;
    for(auto [s, e] : acts) {
        if(s >= L && e <= R) {
            valid.emplace_back(e, s); // 按结束时间排序
        }
    }
    sort(valid.begin(), valid.end());
    
    int cnt = 0, last_end = -1;
    for(auto [e, s] : valid) {
        if(s > last_end) { // 可以选
            cnt++;
            last_end = e;
        }
    }
    return cnt;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    
    cin >> n >> m >> q;
    acts.resize(m);
    for(int i = 0; i < m; i++) {
        cin >> acts[i].first >> acts[i].second;
    }
    
    while(q--) {
        int L, R;
        cin >> L >> R;
        cout << solve_brute(L, R) << '\n';
    }
    
    return 0;
}