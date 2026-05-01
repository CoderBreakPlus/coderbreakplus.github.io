// created time: 2026-05-01
// https://www.luogu.com.cn/problem/P16402
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

ll n,x,y,a,b;
const int M=1e7+1;
ll buc[10000005];

void procedure(){
	n=read(),x=read(),y=read(),a=read(),b=read();
	while(n--){
		int w=read();
		buc[w-1]++;
	}
	for(int i=M-x;i>=0;i--)buc[i]+=buc[i+x];
	ll ans=9e18;
	for(int i=M-1;i>=0;i--){
		buc[i]+=buc[i+1];
		if((__int128)buc[i]*a+(__int128)(i+y-1)/y*b < (__int128)ans)
			ans=buc[i]*a+(i+y-1)/y*b;
	}
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}