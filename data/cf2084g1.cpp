// created time: 2026-04-23 09:46:24
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

int n,a[5005];
ll dp[5005][5005];

void procedure(){	
	n=read();
	for(int i=1;i<=n;i++)a[i]=0;
	for(int i=1;i<=n;i++){
		a[read()]=i;
	}	
	// memset(dp,0xc0,sizeof(dp));
	for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)dp[i][j]=-1e18;
	dp[0][0]=0;

	int s=(n+1)/2,t=n/2;
	for(int i=1;i<=n;i++){
		if(!a[i]){
			dp[i][0]=dp[i-1][0];
			for(int j=1;j<=i;j++)
				dp[i][j]=max(dp[i-1][j],dp[i-1][j-1]);
		}else if(a[i]&1){
			for(int j=1;j<=i;j++)
				dp[i][j]=dp[i-1][j-1];
		}else{
			for(int j=0;j<i;j++)
				dp[i][j]=dp[i-1][j];
		}
		for(int j=0;j<=i;j++)
			dp[i][j]+=j*(s-j)+(i-j)*(t-i+j);
	}
	ll ans=dp[n][s];
	// cout<<"ans="<<ans<<endl;
	for(int i=1;i<=n;i++)
		ans+=i*(n-i+1);
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