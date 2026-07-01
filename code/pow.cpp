// created time: 2026-07-01 08:27:37
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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

char s[10005];
int n;

int dp[10005][10005],cf;

void solve(){
	for(int i=0;i<=n;i++)for(int j=0;j<=n;j++)
		dp[i][j]=0;

	dp[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++){
			addmod(dp[i+1][j+1]+=dp[i][j]);
			if(s[i]=='0')
				dp[i+1][j]=(dp[i+1][j]+(ull)dp[i][j]*j)%mod;
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++)
		addmod(ans+=dp[n][i]);
	ans=(ull)ans*cf%mod;
	printf("%d\n",ans);
}
void procedure(){
	scanf("%s",s);n=strlen(s);
	for(int i=0;i<n;i++)cf+=(s[i]=='0');
	cf=qpow((mod+1)/2,cf);
	solve();

	int q=read();
	while(q--){
		int i=read();swap(s[i-1],s[i]);
		solve();
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	#ifndef LOCAL
		assert(freopen("pow.in","r",stdin));
		assert(freopen("pow.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}