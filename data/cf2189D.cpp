// created time: 2026-04-19 19:07:19
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

int n,k,v[50],dp[50][50];

int calc(){
	int m=lg2(2*n-1);
	if(__builtin_popcount((1<<m)-n)<=k) return 1;
	memset(dp,0x3f,sizeof(dp));

	dp[0][0]=0;
	for(int i=0;i<=m;i++){
		for(int x=0;x<=k;x++){
			if((n>>i)&1){
				dp[i+1][x]=min(dp[i][x]+1,dp[i+1][x]);
			}else
				dp[i+1][x]=min(dp[i][x],dp[i+1][x]);

			for(int j=i+1;j<=m+1;j++){
				int val=__builtin_popcount((1<<j-i)-((n>>i)&((1<<j-i)-1)));
				if(x+val<=n)
					dp[j][x+val]=min(dp[j][x+val],dp[i][x]+1);
			}
		}
	}
	int ans=1e9;
	for(int i=0;i<=k;i++)ans=min(ans,dp[m+1][i]);
	return ans;
}
void procedure(){
	n=read(),k=read();
	printf("%d\n", k+__builtin_popcount(n)-calc());
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