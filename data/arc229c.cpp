// created time: 2026-09-05
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

int n,a[200005];

void procedure(){
	ll sum=0;
	n=read();

	int c[2]={0,0};
	for(int i=1;i<=n;i++){
		a[i]=read(),sum+=a[i];
		c[a[i]&1]++;
	}
	sort(a+1,a+n+1,greater<int>());

	int w0=a[1]&1, w1=a[2]&1;

	if(c[0]>c[1]) swap(c[0],c[1]),w0^=1,w1^=1;

	ll ans=2*sum-a[1]-a[2];

	if(c[0]==c[1]){
		ans-=2*c[0]-1;
		if(w0==w1)ans++;
		printf("%lld\n",ans/2);
	}else{
		ans-=2*c[0];
		if(!w0)ans++;
		if(!w1)ans++;
		printf("%lld\n",ans/2);
	}
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