// created time: 2026-05-23 13:01:02
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
namespace FastFactor {
    using u64 = unsigned long long;
    using u128 = __uint128_t;

    inline u64 fast_rand() {
        static u64 seed = 1145141919810ULL;
        seed ^= seed << 13;
        seed ^= seed >> 7;
        seed ^= seed << 17;
        return seed;
    }

    inline u64 mul(u64 a, u64 b, u64 m) {
        return (u64)((u128)a * b % m);
    }

    inline u64 power(u64 base, u64 exp, u64 mod) {
        u64 res = 1;
        base %= mod;
        while (exp) {
            if (exp & 1) res = mul(res, base, mod);
            base = mul(base, base, mod);
            exp >>= 1;
        }
        return res;
    }

    inline u64 gcd(u64 a, u64 b) {
        if (!a) return b;
        if (!b) return a;
        int shift = __builtin_ctzll(a | b);
        a >>= __builtin_ctzll(a);
        while (b) {
            b >>= __builtin_ctzll(b);
            if (a > b) std::swap(a, b);
            b -= a;
        }
        return a << shift;
    }

    inline bool is_prime(u64 n) {
        if (n < 2) return false;
        if (n % 2 == 0) return n == 2;
        if (n % 3 == 0) return n == 3;
        u64 d = n - 1;
        int s = __builtin_ctzll(d);
        d >>= s;
        static const u64 bases[] = {2, 13, 23, 1662803};
        for (u64 a : bases) {
            if (n <= a) break;
            u64 x = power(a, d, n);
            if (x == 1 || x == n - 1) continue;
            bool composite = true;
            for (int r = 1; r < s; ++r) {
                x = mul(x, x, n);
                if (x == n - 1) {
                    composite = false;
                    break;
                }
            }
            if (composite) return false;
        }
        return true;
    }

    inline u64 pollard_rho(u64 n) {
        if (n % 2 == 0) return 2;
        if (n % 3 == 0) return 3;
        if (is_prime(n)) return n;
        
        u64 c = fast_rand() % (n - 1) + 1;
        u64 x = 0, y = 0, g = 1;
        
        for (u64 l = 1; ; l <<= 1) {
            x = y;
            u64 prd = 1;
            for (u64 i = 0; i < l; ++i) {
                y = (mul(y, y, n) + c) % n;
                prd = mul(prd, x > y ? x - y : y - x, n);
                if ((i & 127) == 0) {
                    g = gcd(prd, n);
                    if (g > 1) break;
                }
            }
            if (g == 1) g = gcd(prd, n);
            if (g > 1) {
                if (g == n) return pollard_rho(n); 
                return g;
            }
        }
    }

    void get_prime_factors(u64 n, std::vector<u64>& primes) {
        if (n < 2) return;
        if (is_prime(n)) {
            primes.push_back(n);
            return;
        }
        u64 p = pollard_rho(n);
        get_prime_factors(p, primes);
        get_prime_factors(n / p, primes);
    }

    void dfs_divisors(int idx, u64 current, const std::vector<std::pair<u64, int>>& p_counts, std::vector<u64>& divs) {
        if (idx == (int)p_counts.size()) {
            divs.push_back(current);
            return;
        }
        u64 p = p_counts[idx].first;
        int count = p_counts[idx].second;
        u64 p_pow = 1;
        for (int i = 0; i <= count; ++i) {
            dfs_divisors(idx + 1, current * p_pow, p_counts, divs);
            if (i < count) p_pow *= p;
        }
    }

    std::vector<u64> get_all_divisors(u64 n) {
        if (n == 0) return {};
        if (n == 1) return {1};
        
        std::vector<u64> primes;
        get_prime_factors(n, primes);
        std::sort(primes.begin(), primes.end());

        std::vector<std::pair<u64, int>> p_counts;
        for (u64 p : primes) {
            if (p_counts.empty() || p_counts.back().first != p) {
                p_counts.push_back({p, 1});
            } else {
                p_counts.back().second++;
            }
        }

        std::vector<u64> divisors;
        dfs_divisors(0, 1, p_counts, divisors);
        std::sort(divisors.begin(), divisors.end());
        return divisors;
    }
}
ll n,R;
void procedure(){
	n=read(),R=read();
	ll ans=__builtin_popcountll(n);
	auto chk = [&](ll i){
		if(i<=1||i>R) return 0;
		ll ok=0,nn=n;
		while(nn){
			auto [x,y]=div(nn,i);
			ok+=y,nn=x;
		}
		chkmin(ans,ok);
		return 0;
	};
	for(ll x=0;x<ans&&x<n;x++){
		ll N=n-x;

		vector<ull>vec = FastFactor::get_all_divisors(N);
		for(ull i: vec)
			chk(i);
	}
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}