#include <iostream>
#include <vector>
#include <random>
#include <string>
#include <algorithm>
#include <cstdlib>

using namespace std;

// 随机数生成器
mt19937 rnd;
int rand_in(int l, int r) {
    return uniform_int_distribution<int>(l, r)(rnd);
}

void gen_in(int id, int n, int q) {
    string filename = "data" + to_string(id) + ".in";
    FILE *f = fopen(filename.c_str(), "w");
    fprintf(f, "%d %d\n", n, q);
    rnd.seed(1337 + id * 1000);
    
    vector<int> a(n + 1);
    
    // ====== 确定数据分布模式 ======
    int mode = id % 10;
    if (id <= 10) mode = id % 5; // Subtask 1 的模式简单些
    
    // 初始化数组
    if (mode == 2 || mode == 4) {
        // 卡 3 操作扫描线 / 卡外层二分：数组大部分极小，唯一的大数在最后
        for (int i = 1; i < n; ++i) a[i] = rand_in(1, 10);
        a[n] = 1000000000;
    } else if (mode == 7) {
        // 单调递减数组
        for (int i = 1; i <= n; ++i) a[i] = max(1, n - i + 1);
    } else {
        // 纯随机
        for (int i = 1; i <= n; ++i) a[i] = rand_in(1, 1000000000);
    }
    
    // 输出数组
    for(int i = 1; i <= n; ++i) {
        fprintf(f, "%d%c", a[i], i == n ? '\n' : ' ');
    }
    
    // 生成操作
    for(int i = 1; i <= q; ++i) {
        int op = 0;
        
        // --- 核心：定向爆破策略 ---
        if (mode == 1) { // 针对 1 操作慢：95% 是操作 1
            op = (rand_in(1, 100) <= 95) ? 1 : rand_in(2, 3);
        } else if (mode == 3) { // 针对 2 操作慢：95% 是操作 2
            op = (rand_in(1, 100) <= 95) ? 2 : ((rand_in(1, 2) == 1) ? 1 : 3);
        } else if (mode == 4 || mode == 2) { // 针对 3 操作慢：90% 是操作 3
            op = (rand_in(1, 100) <= 90) ? 3 : rand_in(1, 2);
        } else if (mode == 8) { // 针对交替操作：1 和 3 混合
            op = (rand_in(1, 2) == 1) ? 1 : 3;
        } else { // 均匀随机
            op = rand_in(1, 3);
        }
        
        // --- 操作参数生成 ---
        if (op == 1) {
            int x = rand_in(1, n);
            int y = rand_in(1, 1000000000);
            if (mode == 2 || mode == 4) {
                // 如果是卡 3 操作的数据，修改时不要改掉结尾的 10^9，且新值要很小
                x = rand_in(1, n - 1);
                y = rand_in(1, 10);
            }
            fprintf(f, "%d %d %d\n", op, x, y);
        } 
        else if (op == 2) {
            int l, r;
            if (mode == 3) {
                // 使得 2 操作跨度极其大
                l = rand_in(1, max(1, n / 100));
                r = rand_in(n - max(1, n / 100), n);
            } else {
                l = rand_in(1, n); r = rand_in(1, n);
            }
            if (l > r) swap(l, r);
            fprintf(f, "%d %d %d\n", op, l, r);
        } 
        else {
            int l, x;
            if (mode == 2 || mode == 4) {
                // 卡 3 操作：从头开始找，找一个只有最后一位才满足的值
                // 此时外层二分+内层线段树做法会进行满打满算的 log^2 n 运算
                l = rand_in(1, max(1, n / 100)); 
                x = rand_in(100, 100000000); 
            } else if (mode == 8) {
                // 偶尔查询根本不存在的值，迫使返回 0
                l = rand_in(1, n);
                x = (rand_in(1, 10) > 7) ? 1000000001 : rand_in(1, 1000000000);
            } else {
                l = rand_in(1, n);
                x = rand_in(1, 1000000000);
            }
            fprintf(f, "%d %d %d\n", op, l, x);
        }
    }
    fclose(f);
}

int main() {
    cout << "Compiling std.cpp..." << endl;
    if (system("g++ std.cpp -o std -O2") != 0) {
        cerr << "Compilation failed! Ensure std.cpp exists and g++ is in PATH." << endl;
        return 1;
    }
    cout << "Compilation successful. Generating data..." << endl;
    
    for (int i = 1; i <= 20; ++i) {
        int n, q;
        if (i <= 10) {
            n = 1000; q = 1000;   // Subtask 1
        } else {
            n = 1000000; q = 4000000; // Subtask 2
        }
        
        gen_in(i, n, q);
        
        string cmd = "./std < data" + to_string(i) + ".in > data" + to_string(i) + ".out";
#ifdef _WIN32
        cmd = "std.exe < data" + to_string(i) + ".in > data" + to_string(i) + ".out";
#endif
        if (system(cmd.c_str()) != 0) {
            cerr << "Execution failed for test " << i << endl;
            return 1;
        }
        
        cout << "Generated data" << i << ".in/out";
        if (i <= 10) cout << " (Subtask 1) ";
        else cout << " (Subtask 2) ";
        
        // 打印特征标明本组数据的爆破方向
        int mode = i % 10;
        if (i <= 10) mode = i % 5;
        if (mode == 1) cout << "[Anti-Op1 Update Heavy]";
        else if (mode == 3) cout << "[Anti-Op2 RangeMin Heavy]";
        else if (mode == 4 || mode == 2) cout << "[Anti-Op3 O(n) & O(log^2 n) Killer]";
        else if (mode == 7) cout << "[Descending Array]";
        else cout << "[Random Mixed]";
        
        cout << endl;
    }
    
    cout << "\nAll data generated successfully!" << endl;
    return 0;
}