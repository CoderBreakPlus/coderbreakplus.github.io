// created time: 2026-04-28 19:20:09
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

int n,x,dp[2][200005];
void procedure(){
	n=read(),x=read();
	if(n==1){
		printf("%d\n",x);
		return;
	}
	x++;

	if((ll)n*(n+1)/2>x){
		puts("0");
		return;
	}
	x-=(ll)n*(n+1)/2;


	memset(dp[0],0,sizeof(int)*(x+1));
	dp[0][0]=1;
	for(int i=1,op=1;i<=n-1;i++,op^=1){
		memset(dp[op],0,sizeof(int)*(x+1));
		for(int j=0;j<=x;j++){
			dp[op][j]=dp[op^1][j];
			if(j>=i)addmod(dp[op][j]+=dp[op][j-i]);
		}
	}
	int ans=0;
	for(int j=0;j<=x;j++){
		ans=(ans+(ull)(x-j+1)*dp[(n-1)&1][j])%mod;
	}
	printf("%d\n",ans);
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