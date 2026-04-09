// created time: 2026-03-31 09:15:19
// http://xsy.gdgzez.com.cn/JudgeOnline/problem.php?cid=2403&pid=0
// related problem: CF1682E

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353;
inline ll read(){
    ll x=0, f=1; int ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); }
 
int n,C,a[300005],b[300005],c[300005],ia[300005],ib[300005];
bool vis[300005],ok[300005];
int seq[300005],m;
 
vector<pair<int,int>>out;
int ord[300005], ordc;
namespace solver{
    int *to = a;
    int rk[300005],in[300005],len[300005],cnt,deg[300005];
    int q[300005];
    vector<int>E[300005];
    vector<pair<int,int>>G[300005];
    void addedge(int x,int y,int i){
        G[x].pb(y,i+1),G[y].pb(x,i+1);
    }
 
    int L, ri;
    bool cmp(pair<int,int> x, pair<int,int> y){
        int rx=(rk[x.fi]<=ri)?(rk[x.fi]+L):rk[x.fi];
        int ry=(rk[y.fi]<=ri)?(rk[y.fi]+L):rk[y.fi];
        return rx<ry;
    }
    void init(){
        memset(rk,-1,sizeof(rk)); 
        for(int i=1;i<=n;i++) E[i].clear(),G[i].clear(),deg[i]=len[i]=in[i]=q[i]=0;
        cnt=0; ordc=0;
    }
    void main(){
        m=out.size();
        for(int i=1;i<=n;i++)
            if(rk[i]==-1){
                rk[i]=0,in[i]=++cnt;
                int j,k;
                for(j=to[i],k=1;j!=i;j=to[j],++k) rk[j]=k,in[j]=cnt;
                len[cnt]=k;
            }
        for(int i=1;i<=n;i++){
            L=len[in[i]],ri=rk[i];
            sort(G[i].begin(),G[i].end(),cmp);
            for(int j=1;j<G[i].size();j++)
                E[G[i][j-1].se].emplace_back(G[i][j].se),++deg[G[i][j].se];
        }
        int hd=1,tl=0;
        for(int i=1;i<=m;i++)
            if(deg[i]==0) q[++tl]=i;
 
        while(hd<=tl){
            int x=q[hd++];
            ord[ordc++]=x-1;
            for(auto v:E[x])
                if(!--deg[v])q[++tl]=v;
        }
    }
}
int fa[300005],ls[300005],rs[300005],prv[300005],nxt[300005],sz[300005];
inline int find(int x){if(x!=fa[x])fa[x]=find(fa[x]);return fa[x];}
 
inline void merge(int x,int y){
    x=find(x),y=find(y);
    if(sz[x]<sz[y]){
        fa[x]=y; ls[y]=ls[x];
        sz[y]+=sz[x];
    }else{
        fa[y]=x; rs[x]=rs[y];
        sz[x]+=sz[y];
    }
}
pair<int,int>vec[300005]; int vect;
void procedure(){
    n=read(),C=read();
    for(int i=1;i<=n;i++) vis[i]=0;
    for(int i=1;i<=n;i++)c[i]=read();
    for(int i=1;i<=n;i++)b[i]=read(),ib[b[i]]=i;
 
    for(int i=1;i<=n;i++)a[b[i]]=c[i];
    for(int i=1;i<=n;i++)ia[a[i]]=i;
 
    swap(a,ia);
    ll ans=1ll*n*C;
    out.clear();
    solver::init();
 
    int tot=0,sum=0;
    for(int o=1;o<=n;o++){
        if(!vis[o]){
            ans-=C;
            int w=o; m=0;
            while(!vis[w]){
                seq[m++]=w;
                vis[w]=1;
                w=a[w];
            }
            vect=0;
            for(int i=0;i<m;i++)vec[vect++]={seq[i],i},nxt[i]=i+1,prv[i]=i-1;
            prv[0]=m-1, nxt[m-1]=0;
 
            sort(vec,vec+vect);vect--;
            for(int i=0;i<m;i++) ok[i]=0,sz[i]=1,fa[i]=ls[i]=rs[i]=i;
 
            auto link = [&](int x,int y){
                x=seq[x],y=seq[y];
                ans+=max(y-x,x-y);
                out.pb(x,y);
                solver::addedge(x,y,tot++); 
            };
            for(int i=0;i<vect;i++){
                int p=vec[i].se;
                ok[p]=1;
                if(ok[prv[p]]) merge(prv[p],p);
                if(ok[nxt[p]]) merge(p,nxt[p]);
                 
                int lf=prv[ls[find(p)]];
                int rh=nxt[rs[find(p)]];
 
                if(seq[lf]<seq[rh]) link(lf,p);
                else link(p,rh);
            }
        }
    }
    solver::main();
    printf("%lld %d\n",ans,(int)out.size());
    swap(a,ia);
 
    for(int i=0;i<ordc;i++){
        auto [x,y] = out[ord[i]];
        int p1=ia[x];
        int p2=ia[y];
        swap(a[p1],a[p2]);
        swap(ia[x],ia[y]);
        printf("%d %d\n",ib[p1],ib[p2]);
    }
}
int main(){
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ll T=read();
    // math_init();
    while(T--) procedure();
    return 0;
}