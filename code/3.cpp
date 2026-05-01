#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };

map<ll,ll>mp;
void procedure(){
	mp.clear(); ll k=read();
	while(k--){
		ll a=read(),b=read();if(a<b)swap(a,b);a--;
		if(!mp.count(a))mp[a]=b;
		else mp[a]=min(mp[a],b);
	}
	ll mx=0,lst=-1,d=0;
	for(auto [x,y]: mp){
		// cout<<x<<","<<y<<endl;
		if(~lst){
			mx=max(mx, x-y);
			d=__gcd(d,x-lst);
		}
		lst=x;
	}
	if(!d)puts("YES");
	else 
	puts(mx<=d?"YES":"NO");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}
// n+1 n+m+1 n+2*m+1 
//     >=n   >=n+m
//