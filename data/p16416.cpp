// created time: 2026-05-03 14:56:39
// // https://www.luogu.com.cn/problem/P16416
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

int n,c[5005],a[5005],b[5005],dp[5005][5005],buc[5005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)c[i]=min(n+1,(int)read()),buc[c[i]]++;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();

	dp[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<i;j++){
			if(!dp[i-1][j]) continue;
			// cout<<i-1<<","<<j<<" dp = "<<dp[i-1][j]<<endl;
			int v=dp[i-1][j];
			for(int k=i;k<=n&&k-i<=buc[i];k++){
				// cout<<"at "<<k<<" v="<<v<<endl;
				int tmp=((ull)a[k]*i+b[k])%mod;
				dp[k][j+1]=(dp[k][j+1]+(ull)v*perm(buc[i],k-i)%mod*tmp)%mod;
				dp[k][j]=(dp[k][j]+(ull)(mod-v)*perm(buc[i],k-i+1)%mod*tmp)%mod;
				v=((ull)a[k]*(k+1)+b[k])%mod*v%mod;
			}
			dp[n][j]=(dp[n][j]+(ull)v*perm(buc[i],n-i+1))%mod;
		}
	}
	int ans=0;
	for(int i=0;i<=n;i++)
		ans=(ans+(ull)dp[n][i]*fac[i])%mod;
	printf("%d\n",ans);
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