
// created time: 2026-05-16 09:29:04
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

ll a,b,s,n;

void procedure(int tid){
	a=read(),b=read(),n=read(),s=read();
	if(s%a || n*a<s){
		puts("YES");
		for(int i=1;i<=n;i++) printf("%lld ",a);
		puts("");
	}else if(s%b || n*b<s){
		puts("YES");
		for(int i=1;i<=n;i++) printf("%lld ",b);
		puts("");
	}else{
		if(a>b)swap(a,b);
		if((b!=s) && (b%a || (b/a>2))){
			puts("YES");
			ll sum=0;
			set<ll>S={0};
			for(int i=1;i<=n;i++){
				if(i%(s/b)==0) printf("%lld ",a),sum+=a;
				else printf("%lld ",b),sum+=b;
				assert(!S.count(sum-s));
				S.emplace(sum);
			}
			puts("");
		}else puts("NO");
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	for(int i=1;i<=T;i++){
		procedure(i);
	}
	return 0;
}