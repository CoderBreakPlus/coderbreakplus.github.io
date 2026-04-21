// created time: 2026-04-21 14:21:17
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

ll x,y;
void procedure(){
	x=read(),y=read();
	vector<ll>a={0,x},b={0,y};
	for(ll i=30;i>=0;i--){
		if(!((x>>i)&1))
			a.pb(((x>>i)|1)<<i),b.pb(((y>>i)|1)<<i);
		else{
			a.pb(x>>i<<i),b.pb(x>>i<<i);
			a.pb((x>>i<<i)-1),b.pb((x>>i<<i)-1);
		}
	}
	ll ans=1e18,px,py;
	for(auto xx:a)for(auto yy:b){
		if(xx<0||yy<0)continue;
		ll d=(xx&yy);

		xx-=d;
		ll dis=max(x-xx,xx-x)+max(y-yy,yy-y);
		if(dis<ans){
			px=xx,py=yy;
			ans=dis;
		}

		xx+=d,yy-=d;
		dis=max(x-xx,xx-x)+max(y-yy,yy-y);
		if(dis<ans){
			px=xx,py=yy;
			ans=dis;
		}
	}
	printf("%lld\n",ans);
	// printf("%lld %lld\n",px,py);
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