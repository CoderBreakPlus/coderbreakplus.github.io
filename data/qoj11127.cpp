// created time: 2026-05-18 11:13:28
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int n,mod;
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
const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

int dp[2][505][505][2],tmp[505][505][2];
char s[505];

int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	n=read(),mod=read();
	math_init();
	// scanf("%s",s+1);
	dp[1][1][0][0]=1;

	for(int i=2,op=0;i<=n;i++,op^=1){
		memset(dp[op],0,sizeof(dp[op]));
		memset(tmp,0,sizeof(tmp));
		for(int j=1;j<=n;j++)
			for(int k=0;k<=n;k++) for(int o:{0,1}){
				if(!dp[op^1][j][k][o]) continue;
				int ff=dp[op^1][j][k][o];
				// for(int l=1;l<j;l++)addmod(dp[op][j-l][k][1]+=ff);
				addmod(dp[op][j][k][o]+=ff);
				addmod(tmp[j-1][k][1]+=ff);
			}
		for(int j=n;j>=1;j--)
			for(int k=0;k<=n;k++) for(int o:{0,1}){
				addmod(tmp[j][k][o]+=tmp[j+1][k][o]);
				addmod(dp[op][j][k][o]+=tmp[j][k][o]);
			}

		for(int j=1;j<=n;j++)
			for(int k=0;k<=n;k++)
				if(dp[op^1][j][k][1])
					addmod(dp[op^1][j][k+1][0]+=dp[op^1][j][k][1]);

		for(int j=1;j<=n;j++)
			for(int k=n;k>=1;k--)
				addmod(dp[op^1][j][k-1][0]+=dp[op^1][j-1][k][0]);

		for(int j=1;j<=n;j++)
			for(int k=0;k<=n;k++){
				addmod(dp[op][j+1][k][0]+=dp[op^1][j][k][0]);
			}
	}
	int ans=0;
	for(int j=1;j<=n;j++)
		for(int k=0;k<=n;k++) for(int o:{0,1})
			addmod(ans+=dp[n&1][j][k][o]);
	printf("%d\n",ans);
	return 0;
}