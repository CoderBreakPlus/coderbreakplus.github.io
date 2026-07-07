// created time: 2026-07-07 14:27:36
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

ll n,k;
void procedure(){
	n=read(),k=read();
	k*=9;

	vector<ll>vec;
	for(int i=n+1;i>=1;i--){
		ll x=1;
		for(int j=0;j<i;j++)x*=10;
		x--;

		if(k>=x){
			ll c=k/x;
			chkmin(c,9ll);
			k-=c*x;

			int cnt=i;
			ll cur=0;
			while(cnt--)
				cur=cur*10+c;

			vec.pb(cur);
		}
	}
	k/=9;
	while(k){
		vec.pb(min(k,9ll));
		k=max(0ll,k-9);
	}

	printf("%d\n",(int)vec.size());
	for(auto x: vec)printf("%lld ",x); puts("");
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