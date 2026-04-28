// created time: 2026-04-28 08:28:19
// 
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

int n; char s[50005];
int dp[5005][5005],tmp[5005];

void procedure(){
	n=read();
	scanf("%s",s+1);
	dp[0][0]=1;

	for(int i=1;i<=n;i++){
		if(s[i]!='0'){
			memset(tmp,0,sizeof(tmp));
			for(int j=0;j<i;j++){
				tmp[j+1]=dp[i-1][j];
			}
			for(int j=1;j<=i;j++)addmod(tmp[j]+=tmp[j-1]);
			for(int j=0;j<=i;j++)addmod(dp[i][j]+=tmp[j]);
		}
		if(s[i]!='1'){
			// for(int j=0;j<i;j++)
			// 	for(int k=0;k<=j;k++)addmod(dp[i][j-k]+=dp[i-1][j]);
			memset(tmp,0,sizeof(tmp));
			for(int j=0;j<i;j++)
				tmp[j]=dp[i-1][j];
			for(int j=i;j>=1;j--)addmod(tmp[j-1]+=tmp[j]);
			for(int j=0;j<=i;j++)addmod(dp[i][j]+=tmp[j]);
		}
	}
	int ans=0;
	for(int j=0;j<=n;j++)addmod(ans+=dp[n][j]);
	printf("%d\n",ans);
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