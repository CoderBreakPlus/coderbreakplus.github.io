// created time: 2026-05-05 12:07:24
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

int n,t[3]; char s[3][15];
int dp[1005][15][15][15];

void procedure(){
	n=read();for(int i:{0,1,2})scanf("%s",s[i]),t[i]=strlen(s[i]);

	dp[0][0][0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<t[0];j++)for(int k=0;k<t[1];k++)for(int l=0;l<t[2];l++)
			for(int ch='a';ch<='z';ch++)
				addmod(dp[i+1][s[0][j]==ch?j+1:j][s[1][k]==ch?k+1:k][s[2][l]==ch?l+1:l]+=dp[i][j][k][l]);
	}
	int ans=0;
	for(int j=0;j<t[0];j++)for(int k=0;k<t[1];k++)for(int l=0;l<t[2];l++)
		addmod(ans+=dp[n][j][k][l]);
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