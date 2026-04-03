
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
   
ll n,k,t,tag[1000005];
pair<ll,ll> seq[1000005];
ll a[1000005],id[1000005];

inline void check(ll x){
    for(ll i=1;i<=n;i++){
        ll tmp = a[i]+t*x;
        if(tmp<0){
            tag[id[i]]=0;
        }else
            tag[id[i]]=(tmp+t+k-1)/(t+k);
    }
}
  
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());

ll nd[1000005];
inline ll check2(ll x){
    memset(nd,0,sizeof(nd));
    for(ll i=1;i<=n;i++){
        ll v2=a[i]+t*(x+n-1);
        if(v2<=0) continue;
        ll v1=a[i]+t*x;
        if(v1<=0){
            nd[-a[i]/t-x+1]++;
        }else{
            auto [A,B]=div(v1-1,t+k);
            nd[0]+=A+1;

            ll ok=((t+k)-B+t-1)/t;
            if(ok<n) nd[ok]++;
        }
    }
    if(nd[0]<=x) return x;
    for(ll i=1;i<n;i++){
        nd[i]+=nd[i-1];
        if(nd[i]<=x+i) return x+i;
    }
    return -1;
}

ll solver(){
    ll l=0,r=2e18/n/t,ans=-1;
    while(l<=r){
        ll mid=(l+r)>>1,val=check2(mid*n);
        if(~val){
            ans=val;
            r=mid-1;
        }else
            l=mid+1;
    }
    if(!(~ans)){
        puts("-1");
        exit(0);
    }
    return ans;
}
void procedure(){
    n=read(),k=read(),t=read();
    ll sum=0;
    for(ll i=1;i<=n;i++)seq[i].fi=read(),seq[i].se=i,sum+=seq[i].fi;
    sort(seq+1,seq+n+1,greater<pair<ll,ll>>());
    
    for(ll i=1;i<=n;i++) a[i]=seq[i].fi,id[i]=seq[i].se;
  
    if(!k){
        for(ll i=1;i<=n;i++)
            if(a[i]>0){ puts("-1"); return; }
        puts("0"); for(ll i=1;i<=n;i++) printf("0 "); puts("");
        return;
    }
    if(!t){
        ll ans=0;
        for(ll i=1;i<=n;i++)
            ans+=(tag[id[i]]=max(0ll,(a[i]+k-1)/k));
        printf("%lld\n",ans);
        for(ll i=1;i<=n;i++)
            printf("%lld ",tag[i]);
        puts("");
        return;
    }
    ll fk=0;
    while(k<(n-1)*t) n--,fk++;

    ll ans=solver();

    while(fk--){
        if(a[++n]+ans*t>0){
            puts("-1");
            exit(0);
        }
    }

    check(ans);
    printf("%lld\n",ans);
    for(ll i=1;i<=n;i++) printf("%lld ",tag[i]);
    puts("");
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