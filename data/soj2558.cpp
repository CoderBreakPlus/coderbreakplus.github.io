// created time: 2026-05-15 09:30:25
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
  
ll n,m,h[50005],f[105][50005];
int k[105];
vector<ll>vec[105];
  
void solve(int l,int r,int ql,int qr,int i){
    if(l>r)return;
    int mid=(l+r)>>1,jc=qr;
    for(int j=max(mid-k[i],ql);j<=qr && j<mid;j++){
        ll val=f[i+1][j] + vec[i][mid-j];
        if(val<=f[i][mid]){
            f[i][mid]=val;
            jc=j;
        }
    }
    solve(l,mid-1,ql,jc,i);
    solve(mid+1,r,jc,qr,i);
}
void procedure(){
    n=read(),m=read()-1;
    for(ll i=0;i<=m;i++)h[i]=read();
    for(ll i=1;i<=n;i++){
        k[i]=read();
        vec[i].resize(k[i]+1);
        for(ll j=1;j<=k[i];j++) vec[i][j]=read();
        sort(vec[i].begin(),vec[i].end());
        for(ll j=1;j<=k[i];j++) vec[i][j]+=vec[i][j-1];
        for(ll j=1;j<=k[i];j++) vec[i][j]+=vec[i][j-1];
    }
  
    for(ll i=1;i<=n+1;i++)
        memset(f[i],0x3f,sizeof(ll)*(m+1));
  
    f[n+1][0]=1;
    for(ll i=n;i>=1;i--){
        for(ll j=0;j<=m;j++) f[i+1][j]=max(1ll,f[i+1][j]-h[m-j]);
        solve(1,m,0,m-1,i);
        chkmin(f[i][0], vec[i][1]+f[i+1][0]);
    }
    printf("%lld\n",f[1][m]);
}
int main(){
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ll T=1;
    // math_init();
    while(T--) procedure();
    return 0;
}
