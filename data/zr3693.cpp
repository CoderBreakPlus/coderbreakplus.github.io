// created time: 2026-11-10 07:24:32
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

ll n,B,t[200005],v[200005];

void procedure(){
	n=read(),B=read();
	ll val=0;
	for(ll i=1;i<=n;i++)t[i]=read(),chkmax(val,v[i]=read());

	ll x=0;
	for(ll i=2;i<=n;i++){
		ll vv=(t[i]-t[i-1])-(v[i]-v[i-1]);
		if(vv<0)vv=-vv;
		x=__gcd(x,vv);
	}
	if(!x){
		printf("%lld\n",max(0ll,B-val));
		return;
	}
	ll ans=0;
	auto chk=[&](ll v){
		ans+=(v>val&&v<=B);
	};
	for(ll i=1;i*i<=x;i++){
		if(x%i==0){
			chk(i);
			if(i*i!=x)chk(x/i);
		}
	}
	printf("%lld\n",ans);
}
int main(){
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}