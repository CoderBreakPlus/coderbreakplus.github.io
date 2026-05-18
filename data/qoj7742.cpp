// created time: 2026-05-18 09:29:31
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
    ll x=0, f=1; int ch=getchar();
    while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
    while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
    return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }
 
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }
const ull mod = (ll)1e18 + 3, base = rnd() % 998244353 + 1233;
 
const int N=2e5+5;
const int M=1e7+5;
int n,m,p[N],s[N],t[N];
vector<pair<int,int>>E[N];
 
int lc[M],rc[M],val[M],idt;
int rt[N],fl[N],len[N],bfn[N],ibfn[N];
ull hsh[N],pw[N];
 
void init(){
    for(int i=1;i<=idt;i++)lc[i]=rc[i]=val[i]=0;
    idt=0;
}
void update(int bef,int &now,int l,int r,int x,int w){
    now=++idt;
    if(l==r){
        val[now]=w;
        return;
    }
    int mid=(l+r)>>1;
    if(x<=mid) rc[now]=rc[bef],update(lc[bef],lc[now],l,mid,x,w);
    else lc[now]=lc[bef],update(rc[bef],rc[now],mid+1,r,x,w);
}
int query(int p,int l,int r,int x){
    if(!p) return 0;
    if(l==r) return val[p];
    int mid=(l+r)>>1;
    if(x<=mid)return query(lc[p],l,mid,x);
    else return query(rc[p],mid+1,r,x);
}
 
ull seq[N],qzt[N]; int low[N];
 
void build(){
    queue<int>q; q.push(0);
    int tmp=0;
    while(!q.empty()){
        int x=q.front();q.pop();
        rt[x]=rt[fl[x]];
        if(x)bfn[x]=++tmp, ibfn[tmp]=x;
        for(auto [y,ch]:E[x]){
            len[y]=len[x]+1;
            seq[y]=hsh[y]=((__int128)hsh[x]*base+ch)%mod;
            fl[y]=query(rt[fl[x]],1,n,ch);
            update(rt[x],rt[x],1,n,ch,y);
            q.push(y);
        }
    }
    sort(seq+1,seq+n+1);
    auto find = [&](ull x){
        bool ret=(*lower_bound(seq,seq+n+1,x))==x;
        return ret;
    };
    for(int i=0;i<=n;i++){
        int L=1,R=m;low[i]=0;
        while(L<=R){
            int mid=(L+R)>>1;
            ull qry=((__int128)hsh[i]*pw[mid]+qzt[mid])%mod;
            if(find(qry))low[i]=mid,L=mid+1;
            else R=mid-1;
        }
    }
}
 
ll ans[N];
 
namespace brute{
    int pos[N];
    void main(){
        for(int i=1;i<=n;i++)pos[i]=i;
        for(int s=1;s<=m;s++){
            for(int i=1;i<=n;i++){
                pos[i]=query(rt[pos[i]],1,n,t[s]);
                ans[s]+=len[pos[i]];
            }
        }
    }
}
namespace brute2{
    int st[N], val[N];
    int jp[20][N], mx[20][N];
    ll tmp1[N], tmp2[N];
    void main(){
        for(int i=1;i<=n;i++)val[i]=1;
 
        for(int i=0;i<=n;i++) jp[0][i]=fl[i], mx[0][i]=low[i];
        for(int i=1;i<20;i++)
         for(int j=0;j<=n;j++){
             jp[i][j]=jp[i-1][jp[i-1][j]];
             mx[i][j]=max(mx[i-1][j],mx[i-1][jp[i-1][j]]);
         }
 
        for(int i=n;i>=1;i--){
            int x=ibfn[i], fx=x;
            // while(fx && low[fx]<=low[x]) fx=fl[fx];
            for(int j=19;j>=0;j--)
                if(fx && mx[j][fx]<=low[x]) fx=jp[j][fx];
 
            tmp1[1]+=len[x], tmp1[low[x]+1]-=len[x];
            tmp2[1]++, tmp2[low[x]+1]--;
 
            if(fx){
                tmp1[low[x]+1]+=(ll)len[fx]*val[x], tmp1[low[fx]+1]-=(ll)len[fx]*val[x];
                tmp2[low[x]+1]+=val[x], tmp2[low[fx]+1]-=val[x];
                 
                val[fx]+=val[x];
            }else{
                st[low[x]+1]+=val[x];
            }
        }
 
        for(int i=1;i<=m;i++)
            tmp1[i]+=tmp1[i-1],tmp2[i]+=tmp2[i-1],ans[i]+=tmp1[i]+tmp2[i]*i;
 
        int cur=0,ok=0;
        for(int i=1;i<=m;i++){
            ok+=st[i];
            cur=query(rt[cur],1,n,t[i]);
            ans[i]+=(ll)ok*len[cur];
        }
 
        for(int i=0;i<=m+1;i++)st[i]=tmp1[i]=tmp2[i]=0;
    }
}
void procedure(){
    n=read(),m=read();
    for(int i=1;i<=n;i++)p[i]=read();
    for(int i=1;i<=n;i++)s[i]=read(),E[p[i]].pb(i,s[i]);
    pw[0]=1;
    for(int i=1;i<=m;i++)
        t[i]=read(),pw[i]=(__int128)pw[i-1]*base%mod,
        qzt[i]=((__int128)qzt[i-1]*base+t[i])%mod;
    build();
 
    brute2::main();
    for(int i=1;i<=m;i++)printf("%lld ",ans[i]);
    puts("");
}
void clear(){
    init();
    for(int i=0;i<=n+1;i++)E[i].clear();
    for(int i=0;i<=n+1;i++)rt[i]=fl[i]=len[i]=low[i]=seq[i]=hsh[i]=bfn[i]=ibfn[i]=0;
    for(int i=0;i<=m+1;i++)qzt[i]=pw[i]=ans[i]=0;
}
int main(){
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ll c=read(),T=read();
    // math_init();
    while(T--) procedure(),clear();
    return 0;
}
