// created time: 2026-06-03 07:50:52
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

char s[305];
int n;
int seq[305],t;
int dp[305][305][305];

int f[305][305][305],g[305][305][305];

void procedure(){
	scanf("%s",s);
	n=strlen(s);if(n>30)return;

	int v0=0;
	for(int i=0;i<n;i++)v0+=(s[i]=='0');

	memset(dp,0xc0,sizeof(dp));
	dp[0][0][0]=0;
	for(int i=0;i<n;i++){
		for(int j=0;j<=i;j++)for(int k=0;j+k<=i;k++){
			chkmax(dp[i+1][j][k], dp[i][j][k]);
			if(s[i]=='1'){
				if(j) chkmax(dp[i+1][j-1][k+1], dp[i][j][k]+1);
				chkmax(dp[i+1][j][k+1], dp[i][j][k]+1);
			}else{
				if(k) chkmax(dp[i+1][j+1][k-1], dp[i][j][k]+1);
				chkmax(dp[i+1][j+1][k], dp[i][j][k]+1);
			}
		}
	}
	// for(int j=0;j<=n;j++)cout<<dp[n][0][j]<<" ";cout<<endl;
	f[0][0][0]=1;
	for(int i=n;i>=1;i--){
		memset(g,0,sizeof(g));
		for(int j=0;j<=n;j++)for(int k=0;k<=n;k++)for(int x=0;x<=v0;x++){
			if(!f[j][k][x])continue;
			for(int l=0;k+i*l<=n;l++){
				addmod(g[j+l][k+i*l][x+(i/2)*l]+=f[j][k][x]);
				if(k+i*(l+1)>dp[n][0][j+l+1])break; 
			}
		}
		memcpy(f,g,sizeof(f));
		// cout<<"i="<<i<<endl;
		// for(int j=0;j<=n;j++)for(int k=0;k<=n;k++){
		// 	if(f[j][k])cout<<j<<" "<<k<<" f="<<f[j][k]<<endl;
		// }
	}
	int ans=0;
	for(int i=1;i<=n;i++)addmod(ans+=f[i][n][v0]);
	printf("%d\n",(ans+mod-10)%mod);
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