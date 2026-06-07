#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
    ll x=0, f=1; char ch=getchar();
    while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
    return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
    ll ans=1, base=a;
    while(b){
        if(b&1) ans=ans*base%mod;
        base=base*base%mod; b>>=1;
    }
    return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); };
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

int n,m;
vector<int>E[300005];
int ind[300005],a[300005],vis[300005];

void procedure(){
    n=read(),m=read();

    for(int i=1;i<=m;i++){
        int u=read(),v=read();
        E[u].pb(v); ind[v]++;
    }
    queue<int>q;
    int bas=0;
    for(int i=1;i<=n;i++)
        if(!ind[i])vis[i]=1,q.push(i),bas++;

    while(!q.empty()){
        int x=q.front();q.pop();
        for(int y:E[x]){
            ind[y]--;
            if(!ind[y]) q.push(y),vis[y]=1,bas++;
        }
    }

    for(int i=1;i<=n;i++)a[i]=i;

    shuffle(a+1,a+n+1,rnd);
    int mx=0;
    for(int i=1;i<=n;i++){
        int X=a[i];if(vis[X])continue;
        int cur=1;
        queue<int>q; q.push(X),vis[X]=1;
        vector<int>node;
        while(!q.empty()){
            int x=q.front();q.pop();
            for(int y:E[x]){
                ind[y]--;
                node.pb(y);
                if(!ind[y]&&y!=X){
                    q.push(y),vis[y]=1,cur++;
                }
            }
        }
        mx=max(mx,cur);
        for(int x:node) ind[x]++;
    }
    printf("%d\n",bas+mx);
}
int main(){
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ll T=1;
    // math_init();
    // NTT::init();
    while(T--) procedure();
    return 0;
}