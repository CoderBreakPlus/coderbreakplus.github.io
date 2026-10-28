// created time: 2026-10-28 14:52:03
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

int n,f[505][505],dp[505][505];
char s[505];

void procedure(){
	n=read();
	scanf("%s",s+1);
	for(int i=1;i<n;i++)f[i][i+1]+=(s[i]=='R')+(s[i+1]=='L');
	for(int l=n-2;l>=1;l--)
		for(int r=l+2;r<=n;r++){
			if(s[l]=='R')addmod(f[l][r]+=f[l+1][r]);
			if(s[r]=='L')addmod(f[l][r]+=f[l][r-1]);
		}
	for(int l=1;l<=n;l++)
		for(int r=l+1;r<=n;r++){
			f[l][r]=(ull)f[l][r]*(r-l)%mod;
		}

	for(int r=1;r<=n;r++){
		if(s[r]=='R')break;
		f[1][r]=r;
	}
	for(int l=n;l>=1;l--){
		if(s[l]=='L')break;
		f[l][n]=(n-l+1);
	}
	dp[0][0]=fac[n];
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
		for(int k=1;k<=i;k++)
			dp[i][j]=(dp[i][j]+(ull)f[k][i]*dp[k-1][j-1]%mod*inv[i-k+1])%mod;

	for(int i=1;i<=n;i++)
		printf("%d ",dp[n][i]);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}