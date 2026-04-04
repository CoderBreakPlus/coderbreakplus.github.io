// created time: 2026-04-04 09:04:24
// A. Kendama Challenge
// https://qoj.ac/contest/3575/problem/17713
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

int k,n,a[200005],b[200005];

int dp[200005];

void procedure(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		a[i]=read();
		b[i]=read();
		a[i]=1ull*a[i]*INV(b[i])%mod;
		b[i]=(mod+1-a[i])%mod;
	}

	dp[1]=1;

	int cur=1;
	int tag=1;

	for(int i=1;i<=n;i++){

		tag=1ull*tag*a[i]%mod;
		dp[i+1]=1ull*b[i]*cur%mod*INV(tag)%mod;

		// for(int j=0;j<=i;j++){
		// 	dp[j]=1ull*dp[j]*a[i]%mod;
		// }
		if(i-k+1>=1){
			cur=(cur+1ull*(mod-dp[i-k+1])*tag)%mod;
		}
	}
	printf("%d\n",(mod+1-cur)%mod);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}