// created time: 2026-05-29 13:17:36
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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

ll n,a[1000005],vis[1000005];

ll check(ll x){
	ll ret=(n-1)-(a[n]/x-1);
	if(a[1]>x) ret++;
	if(a[n]-a[n-1]>x) ret++;

	for(ll i=1;i<=n+1;i++)vis[i]=0;
	for(ll i=1;i<n;i++)
		if(a[i]%x==0)vis[i+1]++;
	ll j=0;
	for(ll i=1;i<=n;i++){
		while(j<=a[i-1]) j+=x;
		while(j<a[i]){
			vis[i]++,vis[i+1]++;
			if(vis[i]>=2||vis[i+1]>=2)return 1e18;
			j+=x;
		}
	}
	return ret;
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read()+a[i-1];
	ll ans=1e18,j=n,f=0;
	for(int i=n;i>=1&&j>=0;i--,j--){
		if(a[n]%i==0){
			ll len=a[n]/i;
			chkmin(ans,check(len));
			if(ans<1e17&&!f){
				f=1;
				j=2;
			}
		}
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