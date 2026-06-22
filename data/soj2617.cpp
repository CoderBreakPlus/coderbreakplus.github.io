// created time: 2026-06-17 07:58:08
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
const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
    fac[0]=inv[0]=1;
    for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
    inv[N]=qpow(fac[N],mod-2);
    for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
    if(x<0 || y<0 || x<y) return 0;
    return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
    if(x<0 || y<0 || x<y) return 0;
    return 1ll*fac[x]*inv[x-y]%mod;
}
 
inline void upd(int &a, ull b){ a=(a+b)%mod; }
int n,p[3005],f[3005],a[3005][3005];
 
void procedure(){
    n=read();
    for(int i=1;i<=n;i++)p[read()]++;
 
    for(int i=0;i<n;i++){
        a[i][i]=1, a[i][n+1]=1;
        int tmp = INV((ull)n*qpow(2,n)%mod);
        int pw=qpow(2,n-i),pw2=(ull)(n-i)*qpow(2,n-i-1)%mod;
 
        for(int x=0;x<=i;x++){
            int cf0=((ull)x*pw+pw2)%mod;
            int cf1=((ull)n*pw+mod-cf0)%mod;
            upd(a[i][i-x+1], (ull)(mod-cf0)*tmp%mod*binom(i,x));
            upd(a[i][i-x], (ull)(mod-cf1)*tmp%mod*binom(i,x));
        }
    }
 
    // a[n][n]=1;
    // for(int i=0;i<=n;i++){
    //  for(int j=0;j<=n+1;j++)
    //      cout<<a[i][j]<<" ";
    //  cout<<endl;
    // }
 
    for(int i=n;i>=0;i--){
        // for(int j=i;j<=n;j++)
        //  if(a[j][i]){swap(a[i],a[j]);break;}
        int iv = INV(a[i][i]);
        for(int j=i-1;j>=i-1&&j>=0;j--){
            for(int k=0;k<i;k++)
                upd(a[j][k], (ull)(mod-a[j][i])*iv%mod*a[i][k]);
            for(int k:{n+1})
                upd(a[j][k], (ull)(mod-a[j][i])*iv%mod*a[i][k]);
            a[j][i]=0;
        }
        // cerr<<i<<endl;
    }
 
    // for(int i=0;i<=n;i++){
    //  for(int j=0;j<=n+1;j++)
    //      cout<<a[i][j]<<" ";
    //  cout<<endl;
    // }
 
    for(int i=0;i<=n;i++){
        int cur=a[i][n+1];
        for(int j=0;j<i;j++)
            upd(cur, (ull)(mod-a[i][j])*f[j]);
        f[i]=(ull)cur*INV(a[i][i])%mod;
    }
 
    int ans=(ull)(mod-n+1)*f[0]%mod;
    for(int i=1;i<=n;i++)
        addmod(ans+=f[p[i]]);
 
    printf("%d\n",(ull)ans*INV(n)%mod);
}
int main(){
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    ll T=1;
    math_init();
    while(T--) procedure();
    return 0;
}