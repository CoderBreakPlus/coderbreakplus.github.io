#include<bits/stdc++.h>
#define mem(a, v) memset(a, v, sizeof(a))

using namespace std;

const int maxn = 700 + 10;

struct{
    int v, nex;
} edge[maxn];

int n;
long long res = 1e18;
int a[maxn], siz[maxn];
long long tmp[maxn][maxn];
int head[maxn], top = 0;

inline void add(int u, int v){
    edge[++top].v = v, edge[top].nex = head[u], head[u] = top;
}

inline vector<vector<long long> > dfs(int u){
    vector<vector<long long> > f;
    for (int i = 0; i <= siz[u]; i++){
        f.push_back(vector<long long>(siz[u] + 1, 1e18));
    }
    siz[u] = 1, f[0][0] = 0;
    for (int i = head[u]; i; i = edge[i].nex){
        const int v = edge[i].v;
        const auto g = dfs(v);
        for (int j = 0; j <= siz[u]; j++){
            for (int k = 0; k <= siz[v]; k++){
                for (long long x = 0, pre1 = f[j][x], pre2 = g[k][x]; x <= siz[u] + siz[v]; pre1 = min(pre1, f[j][++x]), x <= siz[v] && (pre2 = min(pre2, g[k][x]))){
                    tmp[j + k][x] = min(tmp[j + k][x], pre1 + pre2);
                }
            }
        }
        siz[u] += siz[v];
        for (int j = 0; j <= siz[u]; j++){
            for (int k = 0; k <= siz[u]; k++){
                f[j][k] = tmp[j][k], tmp[j][k] = 1e18;
            }
        }
    }
    for (int i = 0; i <= siz[u]; i++){
        for (int j = siz[u]; j; j--){
            f[i][j] = f[i][j - 1];
        }
        f[i][0] = 1e18;
    }
    for (int i = 0; i <= siz[u]; i++){
        for (int j = 0; j <= siz[u]; j++){
            f[i][0] = min(f[i][0], f[j][i] + (long long)max(0, i - j) * a[u]);
        }
    }
    return f;
}

int main(){
    scanf("%d", &n), mem(tmp, 0x3f);
    for (int i = 2; i <= n; i++){
        int fa;
        scanf("%d", &fa), add(fa, i);
    }
    for (int i = 1; i <= n; i++){
        scanf("%d", &a[i]);
    }
    for (int u = n; u; u--){
        siz[u] = 1;
        for (int i = head[u]; i; i = edge[i].nex){
            const int v = edge[i].v;
            a[u] = min(a[u], a[v]), siz[u] += siz[v];
        }
    }
    const auto f = dfs(1);
    for (int i = 0; i <= n; i++){
        res = min(res, f[i][0]);
    }
    printf("%lld", res);

return 0;
}
