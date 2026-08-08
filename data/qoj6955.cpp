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
// 假了,一定要记得手模样例!!

int n,k,a[105],b[105],A[105][105];
int f[105][105][15],g[105][15],dp[105][15];

void procedure(){
	n=read(),k=read();
	memset(f,0x3f,sizeof(f));
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			A[i][j]=read();
			for(int k=1;k<j;k++)chkmin(A[i][j],A[i][k]+A[i][j-k]);
		}

	for(int i=1;i<=n+1;i++)f[i][i-1][0]=0;
	for(int l=n;l>=1;l--){
		memset(g,0x3f,sizeof(g));
		g[l-1][0]=0;

		int c=b[l];
		for(int r=l;r<=n;r++){
			for(int s=0;s<=k;s++){
				int w=(b[r]!=c);
				if(s>=w)g[r][s]=g[r-1][s-w];
				for(int x=l;x<=r;x++)
					for(int t=0;t<=s;t++)
						chkmin(g[r][s],g[x-1][s-t]+f[x][r][t]);
			}
		}

		for(int r=l;r<=n;r++){
			for(int s=0;s<=k&&s<=r-l+1;s++){
				f[l][r][s]=g[r][s]+A[c][r-l+1];
				if(s) chkmin(f[l][r][s],min(f[l][r-1][s-1],f[l+1][r][s-1]));
				// for(int x=l;x<r;x++)for(int t=0;t<=s;t++)
				// 	chkmin(f[l][r][s],f[l][x][t]+f[x+1][r][s-t]);
			}
		}
	}
	memset(dp,0x3f,sizeof(dp));
	dp[0][0]=0;

	for(int i=1;i<=n;i++){
		for(int s=0;s<=k;s++){
			int w=(a[i]!=b[i]);
			if(s>=w)dp[i][s]=dp[i-1][s-w];

			for(int j=1;j<=i;j++)for(int t=0;t<=s;t++)
				chkmin(dp[i][s],dp[j-1][s-t]+f[j][i][t]);
		}
	}

	int mn=2e9;
	for(int s=0;s<=k;s++){
		chkmin(mn,dp[n][s]);
		printf("%d ",mn);
	}
	puts("");
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