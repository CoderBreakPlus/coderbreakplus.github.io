// created time: 2026-04-18 12:05:40
// https://qoj.ac/contest/3588/problem/17763
// bei ka chang le
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

long long process1(long long d) {
    long long ans = 1;
    // 处理因子2
    int cnt = 0;
    while (d % 2 == 0) {
        cnt++;
        d /= 2;
    }
    if (cnt > 0) {
        int need = (cnt + 1) / 2;
        for (int i = 0; i < need; i++) {
            ans *= 2;
        }
    }
    
    // 处理奇质因子
    for (long long i = 3; i * i <= d; i += 2) {
        if (d % i == 0) {
            cnt = 0;
            while (d % i == 0) {
                cnt++;
                d /= i;
            }
            int need = (cnt + 1) / 2;
            for (int j = 0; j < need; j++) {
                ans *= i;
            }
        }
    }
    
    // 剩余的大质数
    if (d > 1) {
        int need = (1 + 1) / 2; // =1
        ans *= d;
    }
    
    return ans;
}

ll n,m,phim;
int phi[10000005];
ll shabi(ll n) {
    ll result = n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                n /= i;
            }
            result -= result / i;
        }
    }
    if (n > 1) {
        result -= result / n;
    }
    return result;
}
ll calc(ll x){
	ll ret=0;
	if((__int128)x*x<=n) ret= phi[x];
	else{
		ll d = __gcd(x,n/x);
		ret = (__int128) phim * phi[d] / d / phi[n/x];
	}
	return ret;
}
void procedure(){
	n=read(),m=read();
	phim = shabi(n);
	__int128 ans=0;

	auto upd = [&](ll d){
		ll ret=0;

		ll tmp;
			tmp=process1(d);
		ret=m/tmp+1;
		(ans+=(__int128)ret*d*calc(n/d))%=mod;
	};

	for(ll d=1;d*d<=n;d++){
		if(n%d==0) {
			upd(d);
			if(d*d!=n)upd(n/d);
		}
	}
	printf("%lld\n",(ll)ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	int n = 1e7;
	 vector<int> primes;
	 vector<bool> is_prime(n + 1, true);
	phi[1] = 1;
    for (int i = 2; i <= n; i++) {
        if (is_prime[i]) {
            primes.push_back(i);
            phi[i] = i - 1; 
        }
        for (int p : primes) {
            if (i * p > n) break;
            is_prime[i * p] = false;
            if (i % p == 0) {
                phi[i * p] = phi[i] * p;
                break;
            } else {
                phi[i * p] = phi[i] * (p - 1);
            }
        }
    }
	// for(int i=1;i<=10;i++) printf("%d ",phi[i]);puts("");
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}