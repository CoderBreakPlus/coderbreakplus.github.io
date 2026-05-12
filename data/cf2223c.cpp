// created time: 2026-05-06 14:10:17
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod=998244353;
inline ll read(){
    ll x=0,f=1;int ch=getchar();
    while(ch<'0'||ch>'9'){if(ch=='-')f=-1;ch=getchar();}
    while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
    return x*f;
}
inline int lg2(int x){return 31^__builtin_clz(x);}
inline ll lg2(ll x){return 63^__builtin_clzll(x);}
template<typename T>inline void addmod(T&x){if(x>=mod)x-=mod;}
template<typename T>inline void chkmax(T&a,T b){a=max(a,b);}
template<typename T>inline void chkmin(T&a,T b){a=min(a,b);}
inline ll qpow(ll a,ll b){
    ll ans=1,base=a;
    while(b){if(b&1)ans=ans*base%mod;base=base*base%mod;b>>=1;}
    return ans;
}
inline ll INV(ll x){return qpow(x,mod-2);}
using i128=__int128_t;
struct Node{
    ll a,b;
    Node(ll a=1,ll b=0):a(a),b(b){}
    static ll xg(ll a,ll b,ll&x,ll&y){
        ll x1=1,y1=0,x2=0,y2=1;
        while(b){ll q=a/b,t=x1-q*x2;x1=x2;x2=t;t=y1-q*y2;y1=y2;y2=t;t=a-q*b;a=b;b=t;}
        return x=x1,y=y1,a;
    }
    Node operator+(const Node&o)const{
        const ll L=1e18;
        if(a<0||o.a<0)return Node(-1,0);
        if(a>L)return b%o.a==o.b?*this:Node(-1,0);
        if(o.a>L)return o.b%a==b?o:Node(-1,0);
        ll x,y,d=xg(a,o.a,x,y),c=o.b-b;
        if(c%d)return Node(-1,0);
        ll p=o.a/d,ix=(i128)x*(c/d)%p;
        if(ix<0)ix+=p;
        i128 nb=b+(i128)a*ix,na=(i128)a*p;
        if(na>L)return nb>L?Node(-1,0):Node(L+1,(ll)nb);
        return Node((ll)na,(ll)nb);
    }
    bool q(ll m)const{return a>0&&m%a==b;}
};
int n,q,fa[500005],son[500005],sz[500005],rk[500005];
Node val[500005];
vector<int>E[500005],seq[500005];
vector<Node>lim[500005];
ll l[500005],dep[500005];
void dfs(int x){
    sz[x]=1;son[x]=0;rk[x]=0;
    for(int i=0;i<E[x].size();i++){
        int y=E[x][i];dfs(y);sz[x]+=sz[y];
        if(!son[x]||sz[y]>sz[son[x]])son[x]=y,rk[x]=i;
    }
    if(son[x]){
        int d=E[x].size();
        val[x]=Node(d,((rk[x]-dep[x])%d+d)%d);
    }
}
void dfs2(int x,int tp){
    if(son[x])dfs2(son[x],tp);
    for(auto y:E[x])if(y!=son[x])dfs2(y,y);
    if(x==tp){
        vector<int>().swap(seq[x]);
        vector<Node>().swap(lim[x]);
        int cur=x;Node tmp=val[x];
        while(son[cur]){
            cur=son[cur];
            if(lim[x].empty()||lim[x].back().a!=tmp.a||lim[x].back().b!=tmp.b){
                seq[x].pb(cur);lim[x].pb(tmp);
            }else seq[x].back()=cur;
            tmp=tmp+val[cur];
        }
    }
}
void procedure(){
    n=read();q=read();
    for(int i=1;i<=n;i++)E[i].clear();
    for(int i=2;i<=n;i++)fa[i]=read(),E[fa[i]].pb(i);
    for(int i=2;i<=n;i++)l[i]=read(),dep[i]=l[i]+dep[fa[i]];
    dfs(1);dfs2(1,1);
    while(q--){
        ll m=read();int x=1;
        while(E[x].size()){
            int l=0,r=seq[x].size()-1,ans=x;
            while(l<=r){
                int mid=(l+r)>>1;
                if(lim[x][mid].q(m))ans=seq[x][mid],l=mid+1;
                else r=mid-1;
            }
            x=ans;
            if(!E[x].size())break;
            x=E[x][(m+dep[x])%E[x].size()];
        }
        printf("%d ",x);
    }
    puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
    ll T=read();
    while(T--)procedure();
    return 0;
}