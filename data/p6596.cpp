// created time: 2026-04-17 14:20:45
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

int n,m,dp[55],f[55][55],g[55];

void procedure(){
	n=read(),m=read();

	g[1]=1;
	for(int i=2;i<=n;i++){
		g[i]=qpow(2,i*(i-1)/2);
		for(int j=1;j<i;j++){
			g[i]=(g[i]+(ull)(mod-g[j])*binom(i-1,j-1)%mod*qpow(2,(i-j)*(i-j-1)/2))%mod;
			// cout<<"reduce "<<g[j]<<" * "<<binom(i-1,j-1)<<" * "<<qpow(2,(i-j)*(i-j-1)/2)<<endl;
		}
		// cout<<g[i]<<endl;
	}

	// for(int i=1;i<=n;i++)cout<<g[i]<<" ";cout<<endl;

	f[0][0]=1;
	for(int i=1;i<=n;i++){
		dp[i]=(ull)g[i]*inv[i]%mod;
		for(int j=2;j<=i;j++){
			dp[i]=(dp[i]+(ull)(mod-f[i][j])*qpow(i,j-2))%mod;
			// cout<<"reduce "<<(ull)f[i][j]*fac[i]%mod<<" * "<<qpow(i,j-2)<<endl;
		}
		
		// cout<<"n="<<i<<" "<<(ull)dp[i]*fac[i]%mod<<endl;
		int val=(ull)dp[i]*i%mod;
		for(int j=n;j>=0;j--)
			for(int k=1,v=val;j+k*i<=n;k++,v=(ull)v*val%mod*INV(k)%mod)
				for(int t=0;t+k<=n;t++)
					f[j+k*i][t+k]=(f[j+k*i][t+k]+(ull)v*f[j][t])%mod;
	}
	int ans=0;
	for(int i=1;i<=min(n,m+1);i++){
		ans=(ans+(ull)f[n][i]*qpow(n,i+mod-3))%mod;
	}
	printf("%d\n",(ull)ans*fac[n]%mod);
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