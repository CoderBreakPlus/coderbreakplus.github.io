// created time: 2026-04-18 07:50:20
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
int n,m,p[3005],v[3005],w[3005];

double dp[3005][3005];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)p[i]=read(),v[i]=read(),w[i]=read();
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			if(v[i]>v[j])swap(p[i],p[j]),swap(v[i],v[j]),swap(w[i],w[j]);
		}

	for(int i=1;i<=n;i++){
		for(int j=0;j<=m;j++){
			dp[i][j]=dp[i-1][j];
			if(j>=w[i]) dp[i][j]=max(dp[i][j],(100-p[i])/100.0*dp[i-1][j-w[i]]+p[i]/100.0*v[i]);
		}
	}
	printf("%.10lf\n",dp[n][m]);
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