#include <iostream>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    
    int T = 100; // 100组对拍数据
    cout << T << "\n";
    
    while (T--) {
        int n = uniform_int_distribution<int>(0, 10)(rng); // N加大到 3~10
        
        vector<pair<int, int>> all_coords;
        // 坐标范围扩大到 [-8, 8]
        int t = uniform_int_distribution<int>(3, 8)(rng);
        for (int i = -t; i <= t; ++i) {
            for (int j = -t; j <= t; ++j) {
                all_coords.push_back({i, j});
            }
        }
        
        shuffle(all_coords.begin(), all_coords.end(), rng);
        
        cout << n << " " << all_coords[0].first << " " << all_coords[0].second << "\n";
        for (int i = 1; i <= n; ++i) {
            cout << all_coords[i].first << " " << all_coords[i].second << "\n";
        }
    }
    return 0;
}