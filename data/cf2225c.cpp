// created time: 2026-04-25 09:58:27
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

int n,dp[200005];
char s[2][200005];

void procedure(){
	n=read();
	scanf("%s",s[0]+1);
	scanf("%s",s[1]+1);

	dp[0]=0;
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1]+(s[0][i]!=s[1][i]);
		if(i>=2)
			dp[i]=min(dp[i],dp[i-2]+(s[0][i-1]!=s[0][i])+(s[1][i-1]!=s[1][i]));
		// cout<<i<<" dp="<<dp[i]<<endl;
	}
	printf("%d\n",dp[n]);
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