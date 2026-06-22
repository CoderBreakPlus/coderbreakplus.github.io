// created time: 2026-06-20 09:58:14
#include"tanebi.h"
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
 
bool valid(ll x){ return (x>=0 && x<=1e18); }
vector<ll> game(int n){
    set<ll>sb;
    vector<int>s1,s2;
    for(int i=1;i<n;i++)s1.pb(0);
    for(int i=1;i<n;i++)s2.pb(i);
    vector<ll>vec1 = ask(s1,s2);
 
    s1.clear(),s2.clear();
    for(int i=1;i<n;i++)s1.pb(i);
    for(int i=2;i<=n;i++)s2.pb(i%n);
 
    vector<ll>vec2 = ask(s1,s2);
 
    __int128 S1=0,S2=0;
    for(ll w: vec1) S1+=w;
    for(ll w: vec2) S2+=w,sb.emplace(w);
 
    for(int x=0;x<n;x++){
        if((S2+vec1[x])&1) continue;
        ll add=vec1[x];
        __int128 S=(S2+vec1[x])/2;
        // cout<<"x="<<x<<" S="<<S<<endl;
 
        if((S1-S)%(n-2)) continue;
 
        vector<ll>a(n,-1);
        vector<bool>vis(n,0);
        vis[x]=1;
 
        a[0]=(S1-S)/(n-2),a[1]=add-a[0];
        if(!valid(a[0])||!valid(a[1]))continue;
 
        // cout<<"x="<<x<<" a0="<<a[0]<<" a1="<<a[1]<<endl;
 
        bool flg=1;
        for(int i=2;i<n;i++){
            for(int j=0;j<n;j++){
                if(!vis[j] && sb.count(a[i-1]+vec1[j]-a[0])){
                    vis[j]=1;
                    a[i]=vec1[j]-a[0];
                    break;
                }
            }
            if(!valid(a[i])){
                flg=0;
                break;
            }
        }
        if(flg) return a;
    }
    assert(0);
}