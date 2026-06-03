// created time: 2026-06-03 07:50:52
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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
 
char s[305];
int n;
int seq[305],t;
int dp[305][305][305];
 
 
namespace sx{
    int f[305][305],g[305][305];
    void main(){
        f[0][0]=1;
        for(int i=n;i>=2;i-=2){
            memset(g,0,sizeof(g));
            for(int j=0;j<=n;j++)for(int k=0;k<=n;k++){
                if(!f[j][k])continue;
                for(int l=0;k+i*l<=n;l++){
                    addmod(g[j+l][k+i*l]+=f[j][k]);
                    if(k+i*(l+1)>dp[n][0][j+l+1])break; 
                }
            }
            memcpy(f,g,sizeof(f));
        }
        int ans=0;
        for(int i=1;i<=n;i++)addmod(ans+=f[i][n]);
        printf("%d\n",ans);
    }
}
namespace ac{
    int f[305][305][305],g[305][305][305];
    bitset<305>t[305][305];
 
    int main(){
        int v0=0;
        for(int i=0;i<n;i++)v0+=(s[i]=='0');
        if(2*v0>n) return 0;
        f[0][0][0]=1;
        t[0][0][0]=1;
 
        int cnt=0;
        for(int i=n;i>=1;i--){
            for(int j=0;j<=n/(i+1);j++)for(int k=0;k<=n;k++)
                for(int x=t[j][k]._Find_first();x<=j;x=t[j][k]._Find_next(x))
                    g[j][k][x]=0;
            for(int j=0;j<=n/(i+1);j++)for(int k=0;k<=n;k++)
                for(int x=t[j][k]._Find_first();x<=j;x=t[j][k]._Find_next(x)){
                    if(f[j][k][x])cnt++;
                    else continue;
                    int hi=(i&1);
                    for(int l=j,kk=k,xx=x;kk<=n;l++,kk+=i,xx+=hi){
                        if(kk>dp[n][l-xx][xx])break; 
                        addmod(g[l][kk][xx]+=f[j][k][x]);
                        t[l][kk][xx]=1;
                    }
                }
            for(int j=0;j<=n/i;j++)for(int k=0;k<=n;k++)
                for(int x=t[j][k]._Find_first();x<=j;x=t[j][k]._Find_next(x))
                    f[j][k][x]=g[j][k][x];
        }
        // cout<<"cnt="<<cnt<<endl;
        int ans=0;
        for(int i=1;i<=n;i++)addmod(ans+=f[i][n][n-2*v0]);
        return ans;
    }
}
void procedure(){
    scanf("%s",s);
    n=strlen(s);
    // if(n<=50)
        reverse(s,s+n);
    memset(dp,0xc0,sizeof(dp));
    dp[0][0][0]=0;
    for(int i=0;i<n;i++){
        for(int j=0;j<=i;j++)for(int k=0;j+k<=i;k++){
            chkmax(dp[i+1][j][k], dp[i][j][k]);
            if(s[i]=='1'){
                if(j) chkmax(dp[i+1][j-1][k+1], dp[i][j][k]+1);
                chkmax(dp[i+1][j][k+1], dp[i][j][k]+1);
            }else{
                if(k) chkmax(dp[i+1][j+1][k-1], dp[i][j][k]+1);
                chkmax(dp[i+1][j+1][k], dp[i][j][k]+1);
            }
        }
    }
    // if(n>50){
    //  sx::main();
    // }else{
        printf("%d\n",ac::main());
    // }
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
