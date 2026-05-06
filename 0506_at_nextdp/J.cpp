// created time: 2026-05-05 14:39:21
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

int n;
ll S, T;
using poly = vector<ll>;
int rev_arr[8192];

void ntt(poly &a, int lim, int opt){
    a.resize(lim);
    for(int i=0;i<lim;i++) if(i<rev_arr[i]) swap(a[i],a[rev_arr[i]]);
    for(int len=1;len<lim;len<<=1){
        ll wn=qpow(opt==1?3:INV(3),(mod-1)/(len<<1));
        for(int i=0;i<lim;i+=(len<<1)){
            ll w=1;
            for(int j=0;j<len;j++,w=w*wn%mod){
                ll x=a[i+j], y=w*a[i+j+len]%mod;
                a[i+j]=(x+y)%mod;
                a[i+j+len]=(x-y+mod)%mod;
            }
        }
    }
    if(opt==-1){
        ll inv=INV(lim);
        for(int i=0;i<lim;i++) a[i]=a[i]*inv%mod;
    }
}

poly operator*(poly a, poly b){
    if(a.empty()||b.empty()) return {};
    int n_a=a.size(), n_b=b.size();
    int lim=1, l=0;
    while(lim<n_a+n_b-1) lim<<=1, l++;
    for(int i=0;i<lim;i++) rev_arr[i]=(rev_arr[i>>1]>>1)|((i&1)<<(l-1));
    ntt(a,lim,1); ntt(b,lim,1);
    for(int i=0;i<lim;i++) a[i]=a[i]*b[i]%mod;
    ntt(a,lim,-1);
    a.resize(n_a+n_b-1);
    while(a.size()>1 && !a.back()) a.pop_back();
    return a;
}

poly operator+(poly a, poly b){
    poly c(max(a.size(),b.size()));
    for(size_t i=0;i<a.size();i++) c[i]=a[i];
    for(size_t i=0;i<b.size();i++) c[i]=(c[i]+b[i])%mod;
    while(c.size()>1 && !c.back()) c.pop_back();
    return c;
}

poly operator*(poly a, ll c){
    c=(c%mod+mod)%mod;
    for(auto &x:a) x=x*c%mod;
    while(a.size()>1 && !a.back()) a.pop_back();
    return a;
}

ll bostan_mori(poly P, poly Q, __int128 K){
    while(K>0){
        poly Q_neg=Q;
        for(size_t i=1;i<Q_neg.size();i+=2) Q_neg[i]=(mod-Q_neg[i])%mod;
        poly U=P*Q_neg, V=Q*Q_neg;
        poly next_P, next_Q;
        int rem=(int)(K%2);
        for(size_t i=rem;i<U.size();i+=2) next_P.pb(U[i]);
        for(size_t i=0;i<V.size();i+=2) next_Q.pb(V[i]);
        P=next_P; Q=next_Q; K/=2;
        if(P.empty()) return 0;
    }
    return P.empty()?0:P[0]%mod;
}

void procedure(){
    n=read(), S=read(), T=read();
    map<int,int> mp;
    for(int i=1;i<=n;i++) mp[read()]++;
    vector<int> V, M;
    for(auto it:mp) V.pb(it.fi), M.pb(it.se);
    int k=V.size();
    ll ans=0;

    for(int u=0;u<k;u++){
        ll Y_ext=0;
        for(int up=0;up<u;up++) Y_ext+=(ll)(V[u]-V[up])*M[up];
        __int128 Target = (__int128)T-(__int128)S*V[u]-Y_ext;
        if(Target<0) continue;
        
        poly B={1};
        for(int v=0;v<k;v++){
            if(v==u) continue;
            int d=abs(V[v]-V[u]);
            poly P_v(d+1,0); P_v[0]=1; P_v[d]=mod-1;
            B=B*P_v;
        }
        
        vector<poly> B_pw(M[u]);
        if(M[u]>0) B_pw[0]={1};
        for(int j=1;j<M[u];j++) B_pw[j]=B_pw[j-1]*B;
        
        vector<vector<poly>> N_pw(k, vector<poly>(M[u]));
        for(int uprime=0;uprime<k;uprime++){
            if(uprime==u) continue;
            int d=abs(V[uprime]-V[u]);
            poly B_wo={1};
            for(int v=0;v<k;v++){
                if(v==u||v==uprime) continue;
                int d_v=abs(V[v]-V[u]);
                poly P_v(d_v+1,0); P_v[0]=1; P_v[d_v]=mod-1;
                B_wo=B_wo*P_v;
            }
            poly NumZ;
            if(uprime>u){ NumZ.assign(d+1,0); NumZ[d]=1; }
            else NumZ={mod-1};
            poly N_uu=NumZ*B_wo;
            N_pw[uprime][0]={1};
            for(int j=1;j<M[u];j++) N_pw[uprime][j]=N_pw[uprime][j-1]*N_uu;
        }
        
        vector<poly> NumC(M[u]);
        for(int j=1;j<M[u];j++){
            ll sign_j=(j%2==1)?(mod-1):1;
            ll S_1=(S%mod+1)%mod;
            ll c1=sign_j*S_1%mod*INV(j)%mod;
            poly T1=B_pw[j]*c1;
            poly sum_N={0};
            for(int uprime=0;uprime<k;uprime++){
                if(uprime==u) continue;
                sum_N=sum_N+(N_pw[uprime][j]*M[uprime]);
            }
            sum_N=sum_N*INV(j);
            NumC[j]=T1+sum_N;
        }
        
        vector<poly> NumE(M[u]);
        if(M[u]>0) NumE[0]={1};
        for(int kidx=1;kidx<M[u];kidx++){
            NumE[kidx]={0};
            for(int j=1;j<=kidx;j++){
                poly term=NumC[j]*NumE[kidx-j];
                term=term*j;
                NumE[kidx]=NumE[kidx]+term;
            }
            NumE[kidx]=NumE[kidx]*INV(kidx);
        }
        
        ll sign_pw=M[u]-1;
        for(int up=0;up<u;up++) sign_pw+=M[up];
        ll t_sign=(sign_pw%2==1)?(mod-1):1;
        
        poly Num_tu=NumE[M[u]-1]*t_sign;
        poly Den_tu={1};
        for(int uprime=0;uprime<k;uprime++){
            if(uprime==u) continue;
            int d=abs(V[uprime]-V[u]);
            poly P_v(d+1,0); P_v[0]=1; P_v[d]=mod-1;
            int pw=M[uprime]+M[u]-1;
            for(int i=0;i<pw;i++) Den_tu=Den_tu*P_v;
        }
        
        ans=(ans+bostan_mori(Num_tu,Den_tu,Target))%mod;
    }
    printf("%lld\n",ans);
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