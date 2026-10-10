// created time: 2026-10-07 07:38:09
#include<bits/stdc++.h>
#include"average.h"
// #ifdef LOCAL
// #include"_a.cpp"
// #endif
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
 
void init(int c,int t){ }
struct __attribute__((packed)) Frac{
    ll x;
    int y;
    Frac(){x=0,y=-1;}
    Frac(ll X,int Y){x=X,y=Y;}
};
bool operator< (const Frac &A,const Frac &B){
    if(B.y==-1) return 1;
    if(A.y==-1) return 0;
    // assert(A.y>0&&B.y>0);
    return A.x*B.y<B.x*A.y;
}
Frac f[6005][6005],tmp[6005];
int stk[6005],hd,tp;
 
ll w[6005];
 
int solve(int n,vector<ll> a){
    for(int i=0;i<n;i++) w[i+1]=w[i]+a[i];
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++) f[i][j]=Frac();
 
    int ans=1;
     
    for(int i=1;i<=n;i++){
        hd=1,tp=0;
        for(int j=0;j<i;j++)
            tmp[j]=Frac(w[i]-w[j],i-j);
        chkmin(f[i][1],tmp[0]);
        for(int j=1;j<i;j++){
            int k=lower_bound(f[j]+1,f[j]+j+1,tmp[j])-(f[j]+1);
            if(k>=1&&f[j][k].y!=-1){
                chkmin(f[i][k+1],tmp[j]);
                if(i==n)chkmax(ans,k+1);
            }
        }
        for(int j=i-1;j>=1;j--)chkmin(f[i][j],f[i][j+1]);
    }
    return ans;
}