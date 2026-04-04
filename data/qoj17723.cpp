// created time: 2026-04-04 13:33:05
// K. Square Resistance Value
// https://qoj.ac/contest/3575/problem/17723
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

vector<pair<int, int>> E;
int tot = 2;

void procedure(){
    ll D = read();
    long double target = sqrt((long double)D);
    ll a0 = floor(target);
    ll p2 = 0, p1 = 1, q2 = 1, q1 = 0;
    ll m = 0, d = 1, a = a0;
    ll P = a * p1 + p2, Q = a * q1 + q2;
    while(abs((long double)P / Q - target) > 1e-6){
        m = d * a - m;
        d = (D - m * m) / d;
        a = (a0 + m) / d;
        p2 = p1; p1 = P;
        q2 = q1; q1 = Q;
        P = a * p1 + p2;
        Q = a * q1 + q2;
    }
    int u = 1, v = 2;
    ll curP = P, curQ = Q;
    while(curP > 0 && curQ > 0){
        if(curP == curQ){
            E.pb(u, v);
            break;
        } else if(curP > curQ){
            ll cnt = curP / curQ, rem = curP % curQ;
            int now = u;
            for(ll i = 0; i < cnt; i++){
                if(i == cnt - 1 && rem == 0) E.pb(now, v);
                else {
                    tot++;
                    E.pb(now, tot);
                    now = tot;
                }
            }
            if(!rem) break;
            u = now; curP = rem;
        } else {
            ll cnt = curQ / curP, rem = curQ % curP;
            for(ll i = 0; i < cnt; i++) E.pb(u, v);
            if(!rem) break;
            curQ = rem;
        }
    }
    int N = tot;
    for(auto &e : E){
        if(e.fi == 2) e.fi = N; else if(e.fi == N) e.fi = 2;
        if(e.se == 2) e.se = N; else if(e.se == N) e.se = 2;
    }
    printf("%d %d\n", N, (int)E.size());
    for(auto &e : E) printf("%d %d\n", e.fi, e.se);
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