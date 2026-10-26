// created time: 2026-10-26 09:09:40
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

ll N,n,m;
int mu[1000005];

void procedure(){
	N=read(),n=read(),m=read();
	ll ans=1;
	if(n==0){
		// for(int d=1;d<=N/m;d++)
		// 	for(int c=1;c<=d;c++)
		// 		if(__gcd(c,d)==1)ans++;

		for(int i=1;i<=N/m;i++){
			ll cnt=0;
			for(int d=1;d<=N/m/i;d++)
				cnt+=d;
			ans+=cnt*mu[i];
		}
	}else{
		if(n+m<=N)ans--;
		for(int i=1;i<=N/m;i++){
			ll out=0;
			for(int d=1;d<=N/m/i;d++){
				// c*n+d*m<=N/i
				// c<=d
				out+=2*min((ll)d,(N/i-d*m)/n);
			}
			ans+=out*mu[i];
		}
		// for(int c=1;c<=N/(n+m);c++)
		// 	for(int d=c;d<=(N-c*n)/m;d++)
		// 		if(__gcd(c,d)==1)
		// 			ans+=2;
	}
	printf("%lld\n",ans%mod);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	mu[1]=1;
	int n=1e6;
	for(int i=1;i<=n;i++)
		for(int j=2*i;j<=n;j+=i)mu[j]-=mu[i];

	// for(int i=1;i<=n;i++)

	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}