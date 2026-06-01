// created time: 2026-06-01 06:58:26
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int mod;
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

int n,dp[705],f[705],S[705][705],C[705][705];
void procedure(){
	n=read(),mod=read();
	S[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=i;j++)
			S[i][j]=(S[i-1][j-1]+(ull)j*S[i-1][j])%mod;
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			addmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
	}

	f[0]=1;
	for(int i=0;i<n;i++){
		for(int j=1;i+j<=n;j++){
			int pw=qpow(2,i);
			for(int k=1,v=(ull)f[i]*pw%mod*C[i+j][j]%mod;k<=j;k++,v=(ull)v*(mod-pw)%mod)
				f[i+j]=(f[i+j]+(ull)v*S[j][k])%mod;
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++)
		ans=(ans+(ull)f[i]*C[n][i])%mod;
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