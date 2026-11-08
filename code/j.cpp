// created time: 2026-11-07 14:13:23
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

ll a,b;

ll pa,qa,pb,qb;
void calc(ll l,ll r,ll &ans){
	for(ll i=r-1;i>=l;i--){
		cout<<"print "<<i<<endl;
		ans=((ull)ans*pb+i)%mod;
	}
}
void procedure(){
	a=read(),b=read();
	pa=qpow(10,a),pb=qpow(10,b);
	qa=qpow(10,a-1),qb=qpow(10,b-1);

	ll ans=0;

	ll per=b/a,res=qpow(10,b%a),dv=qpow(10,a-b%a);
	ll lst=pb;
	for(ll i=pa-1;i>=qa;i--){
		ll now=0;
		for(ll x=0;x<per;x++)now=now*pa+i;
		now=now*res+i/dv;

		calc(now,lst,ans);
		ans=(ans*pa+i)%mod;
		cout<<"print "<<i<<endl;
		lst=now;
	}
	calc(qb,lst,ans);
	printf("%d\n",ans);
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