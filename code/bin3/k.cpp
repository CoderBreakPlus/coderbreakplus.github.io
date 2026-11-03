// created time: 2026-11-02 07:57:15
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

ll n,a[100005],l[100005];

bool check(ll M){
	ll L=a[1]-M,R=a[1]+M;

	for(ll i=2;i<=n;i++){
		ll sL=L+l[i],sR=R-l[i];
		if(sL<=sR){
			L=a[i]-M,R=a[i]+M;
			continue;
		}
		if(sL<=a[i]+M)R=a[i]+M; else R=sR;
		if(sR>=a[i]-M)L=a[i]-M; else L=sL;
		chkmax(L,a[i]-M),chkmin(R,a[i]+M);
		if(L>R)return 0;
	}
	return 1;
}
void procedure(){
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=2;i<=n;i++)l[i]=read();

	ll L=0,R=4e18,ans;
	while(L<=R){
		ll M=(L+R)>>1;
		if(check(M)){
			ans=M;
			R=M-1;
		}else
			L=M+1;
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