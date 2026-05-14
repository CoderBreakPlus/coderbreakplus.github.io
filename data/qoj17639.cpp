// created time: 2026-05-09 11:29:51   
#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ull;

int mod,f[505][505][505],g[505][505][505],C[505][505],fac[505];
inline void upd(int &a,ull b){ a=(a+b)%mod; }
inline void addmod(int &a){ a=min<unsigned>(a,a-mod); }

int ascend(int c, int n, int m, vector<int> p, vector<int> w){
    mod = m;

    memset(f, 0, sizeof(f));
    memset(g, 0, sizeof(g));
    memset(C, 0, sizeof(C));
    memset(fac, 0, sizeof(fac));
    fac[0] = 1;
    for (int i = 1; i <= n; i++) fac[i] = (ull)fac[i - 1] * i % mod;
    for (int i = 0; i <= n; i++) {
        C[i][0] = 1;
        for (int j = 1; j <= i; j++) addmod(C[i][j] = C[i - 1][j] + C[i - 1][j - 1]);
    }

    reverse(p.begin(), p.end()); p.push_back(0); reverse(p.begin(), p.end());
    reverse(w.begin(), w.end()); w.push_back(0); w.push_back(0); reverse(w.begin(), w.end());

    // f
    if (!p[1]) f[1][1][1] = 1;
    else f[1][0][0] = 1;

    int sb = !!p[1]; 
    int lst = p[1];

    for (int i = 2; i <= n; i++) {
        if (!p[i]) {
            for (int j = 0; j <= i - 1 - sb; j++) {
                int fr = lst - i + 1 + j;
                if (fr < 0) continue;

                for (int k = 1; k <= j; k++) addmod(f[i - 1][j][k] += f[i - 1][j][k - 1]);
                for (int l = 1; l <= j + 1; l++) {
                    upd(f[i][j + 1][l], (ull)f[i - 1][j][l-1] * w[i] + f[i - 1][j][j] + mod - f[i - 1][j][l-1]);
                }
                for (int l = 1; l <= fr; l++)
                    addmod(g[i][j][l] += f[i-1][j][j]);
                for (int k = 2; k <= fr + 1; k++) addmod(g[i-1][j][k] += g[i-1][j][k-1]);
                for (int l = 1; l <= fr; l++) {
                    upd(g[i][j][l], (ull)g[i - 1][j][l] * w[i] + g[i - 1][j][fr+1] + mod - g[i - 1][j][l]);
                }
                for (int l = 1; l <= j+1; l++){
                    upd(f[i][j+1][l], (ull)g[i-1][j][fr+1]*w[i]);
                }
            }
        } else {
            int d = p[i] - lst - 1;
            for (int j = 0; j <= i - 1 - sb; j++) {
                int fr = lst - i + 1 + j;
                if (fr < 0) continue;

                for (int k = 1; k <= j; k++) addmod(f[i - 1][j][k] += f[i - 1][j][k - 1]);

                for (int l = 0; l <= j && l <= d; l++) {
                    upd(f[i][j - l][0], (ull)f[i - 1][j][l] * C[d][l] % mod * w[i] + (ull)(f[i - 1][j][j] + mod - f[i - 1][j][l]) * C[d][l]);
                }

                int sum = 0;
                for (int k = 1; k <= fr + 1; k++) addmod(sum += g[i - 1][j][k]);

                for (int l = 0; l <= j && l <= d; l++) {
                    upd(f[i][j - l][0], (ull)sum * C[d][l] % mod * w[i]);
                }
            }
            lst = p[i];
        }
        sb += !!p[i];
    }

    int ret = 0;
    for (int i = 0; i <= n; i++)
        addmod(ret += f[n][n - lst][i]), addmod(ret += g[n][n - lst][i]);
    return ret;
}