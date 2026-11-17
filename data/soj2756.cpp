
// created time: 2026-11-17 08:38:30
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
template<typename T>inline void addmod(T &x){ if(x >= mod) x -= mod; }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }
inline ll qpow(ll a,ll b){
    ll ans=1, base=a;
    while(b){
        if(b&1) ans=ans*base%mod;
        base=base*base%mod; b>>=1;
    }
    return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }
#define mid ((l+r)>>1)
 
vector<int>E[200005];
int n,q,dfn[200005],out[200005],idfn[200005],tim;
ll a[200005];
 
struct Edge{
    int to,nxt;
    int l0,r0,l1,r1;
}e[400005];
int hd[200005],tot;
 
void add(int u,int v,int l0,int r0,int l1,int r1){
    e[++tot]=(Edge){v,hd[u],l0,r0,l1,r1};
    hd[u]=tot;
}
void addedge(int u,int v,int l0,int r0,int l1,int r1){
    add(u,v,l0,r0,l1,r1),add(v,u,l1,r1,l0,r0);
}
 
void dfs(int x,int fa){
    dfn[x]=++tim,idfn[tim]=x;
    for(int y:E[x])if(y!=fa){
        dfs(y,x);
    }
    out[x]=tim;
}
vector<pair<int,int>>qry[200005];
const int M=1e7;
struct zxt{
    int lc[M],rc[M],cnt; ll sum[M];
    void cannot(int b,int &p,int l,int r,int x,int w){
        sum[p=++cnt]=sum[b]+w;
        if(l==r)return;
        lc[p]=lc[b],rc[p]=rc[b];
        if(x<=mid)cannot(lc[b],lc[p],l,mid,x,w);
        else cannot(rc[b],rc[p],mid+1,r,x,w);
    }
    int query(int p0,int p1,int p2,int p3,int l,int r,ll nd){
        if(l==r) return l;
        ll val=sum[lc[p0]]-sum[lc[p1]]-sum[lc[p2]]+sum[lc[p3]];
        if(val<nd)
            return query(rc[p0],rc[p1],rc[p2],rc[p3],mid+1,r,nd-val);
        else
            return query(lc[p0],lc[p1],lc[p2],lc[p3],l,mid,nd);
    }
    int rt[200005];
    void init(){
        for(int i=1;i<=n;i++){
            rt[i]=rt[i-1];
            for(auto [t,x]: qry[idfn[i]]){
                cannot(rt[i],rt[i],1,q+1,t,x);
            }
        }
    }
}T;
 
void build(int x,int fa){
    for(int y:E[x])if(y!=fa){
        build(y,x);
        int t=T.query(T.rt[out[x]],T.rt[dfn[x]-1],T.rt[out[y]],T.rt[dfn[y]-1],1,q+1,a[y]-a[x]+(x>y));
        addedge(x,y,t,q,1,t-1);
    }
}
 
int rt,wh,sz[200005],mxs[200005],vis[200005];
int l0[200005],r0[200005],l1[200005],r1[200005];
 
vector<int>pset;
 
int tmp[800005],tc;
 
void findcent(int x,int fa){
    sz[x]=1,mxs[x]=0;
    for(int y:E[x])if(y!=fa&&!vis[y]){
        findcent(y,x);
        sz[x]+=sz[y];
        chkmax(mxs[x],sz[y]);
    }
    chkmax(mxs[x],wh-sz[x]);
    if(mxs[x]<mxs[rt])rt=x;
}
 
void climb(int x,int fa){
    pset.pb(x);
    tmp[++tc]=l0[x],tmp[++tc]=r0[x]+1;
    tmp[++tc]=l1[x],tmp[++tc]=r1[x]+1;
     
    for(int i=hd[x];i;i=e[i].nxt){
        int y=e[i].to;
        if(y==fa||vis[y])continue;
        l0[y]=max(l0[x],e[i].l0),r0[y]=min(r0[x],e[i].r0);
        l1[y]=max(l1[x],e[i].l1),r1[y]=min(r1[x],e[i].r1);
        climb(y,x);
    }
}
int getv(int x){ return lower_bound(tmp+1,tmp+tc+1,x)-tmp; }
ll qz0[200005],qz1[200005];
ll ans[200005];
 
void solve(int x){
    vis[x]=1; pset.clear();
    l0[x]=l1[x]=1,r0[x]=r1[x]=q;
    tc=0;
    climb(x,0);
    sort(tmp+1,tmp+tc+1);tc=unique(tmp+1,tmp+tc+1)-(tmp+1);
    for(int i=0;i<=tc+1;i++)qz0[i]=qz1[i]=0;
 
    for(int x:pset){
        l0[x]=getv(l0[x]),r0[x]=getv(r0[x]+1);
 
        l1[x]=getv(l1[x]),r1[x]=getv(r1[x]+1);
         
        if(l0[x]<=r0[x])qz0[l0[x]]++,qz0[r0[x]]--;
        if(l1[x]<=r1[x])qz1[l1[x]]++,qz1[r1[x]]--;
    }
    for(int i=1;i<tc;i++){
        qz0[i]+=qz0[i-1],qz1[i]+=qz1[i-1];
        ll val=(ll)qz0[i]*qz1[i];
        ans[tmp[i]]+=val,ans[tmp[i+1]]-=val;
    }
 
    int orig=wh;
    for(int y:E[x])if(!vis[y]){
        if(sz[y]>sz[x])wh=orig-sz[x];
        else wh=sz[y];
        rt=0,findcent(y,x),solve(rt);
    }
}
void procedure(){
    n=read(),q=read();
    for(int i=1;i<=n;i++)a[i]=read();
    for(int i=1;i<n;i++){
        int u=read(),v=read();
        E[u].pb(v),E[v].pb(u);
    }
    dfs(1,0);
    for(int i=1;i<=q;i++){
        int x=read(),v=read();
        qry[x].pb(i,v);
    }
    T.init();
    build(1,0);
    mxs[0]=wh=n;
    findcent(1,0),solve(rt);
 
    for(int i=1;i<=q;i++)ans[i]+=ans[i-1],printf("%lld\n",ans[i]-n);
}
int main(){
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ll T=1;
    while(T--) procedure();
    return 0;
}