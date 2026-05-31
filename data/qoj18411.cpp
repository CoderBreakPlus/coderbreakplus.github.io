// created time: 2026-05-30 09:11:57
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

ll n,a[400005];

void procedure(){
	n=read();
	for(ll i=1;i<=2*n;i++)a[i]=read();
	set<pair<ll,ll>>q;
	ll x=0,sz=0,lf=0;

	vector<ll>ans;
	for(ll i=1;i<=2*n;i++){
		q.emplace(a[i],i),sz++;
		while(lf<(i+1)/2){
			ans.pb(prev(q.end())->se);
			q.erase(prev(q.end()));
			lf++;
		}
		while(sz>n){
			q.erase(q.begin());
			sz--;
		}
	}	
	for(auto x: ans) printf("%lld ",x);puts("");
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