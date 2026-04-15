#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int,int> pii;

const int N = 1e6+10,LG2 = 20;

int n,q;
int a[N],lg[N];
int stk[N],tot;
vector<int> son[N];
int nxt[N][LG2],fa[N][LG2];
ll sum2[N];

void dfs(int u)
{
    for(int v:son[u])
    {
        int len = u-v;
        for(int l=0;l<LG2;l++)
        {
            nxt[v][l] = (len>=(1<<l)) ? v:nxt[u][l];
            if(l) fa[v][l] = fa[fa[v][l-1]][l-1];
        }
        sum2[v] = sum2[u] + 1ll*len*len;
        dfs(v);
    }
}

void solve()
{
    cin >> n >> q;
    for(int i=1;i<=n;i++)
    {
        cin >> a[i];
    }
    tot=0;
    for(int i=1;i<=n;i++)
    {
        while(tot && a[stk[tot]] > a[i]) {son[i].push_back(stk[tot]);fa[stk[tot--]][0] = i;}
        stk[++tot] = i;
    }
    for(int i=1;i<=tot;i++)
    {
        fa[stk[i]][0] = n+1;
        son[n+1].push_back(stk[i]);
    }
    sum2[n+1] = 0;
    for(int j=0;j<LG2;j++)
    {
        nxt[n+1][j] = n+1;
        fa[n+1][j] = n+1;
    }
    dfs(n+1);
    while(q--)
    {
        int l,r;
        cin >> l >> r;
        r++;
        ll u = min(r,fa[l][0]);
        ll x = (u-l-1)/2;
        ll ans = x * (u-l-1-x);
        ll len = u-l;
        while(u < r)
        {
            int L = lg[len];
            ll v = nxt[u][L];
            if(v > r)
            {
                v = u;
                for(int i=LG2-1;i>=0;i--)
                {
                    if(fa[v][i] <= r) v = fa[v][i];
                }
            }
            ll d1=v-u,d2=sum2[u]-sum2[v];
            ans += len*d1 + (d1*d1 - d2)/2;
            len += v-u;
            u = v;
            if(u < r)
            {
                ll k=min(fa[u][0],r) - u;
                ll X=max((k-len)/2,0ll);
                ans += -X*X + (k-len) * X + k * len;
                len += k;
                u += k;
            }
        }
        cout << ans << '\n';
    }
    
}
void init()
{
    for(int i=1;i<=n+1;i++)
    {
        son[i].clear();
    }
}

int main()
{
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.ans","w",stdout));
    #endif
    for(int i=2;i<N;i++) lg[i] = lg[i>>1] + 1;
    int T;
    cin >> T;
    while(T--)
    {
        solve();
        init();
    }
}
