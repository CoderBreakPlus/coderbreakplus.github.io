// created time: 2026-04-27 17:32:44
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
const int N = 200000;
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
const int K=17;
const int V=200000;
int n,a[200005],pt[200005],dp[200005][K+1][K+1],ans;
void upd(int &a,ull b){ a=(a+b)%mod; }

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=n-1;i>=1;i--)a[i]=min(a[i],a[i+1]);

	for(int i=1;i<=V;i++) {
		pt[i]=pt[i-1];
		while(pt[i]<n && a[pt[i]+1]<i) pt[i]++;
	}
	dp[1][0][0]=1;
	for(int i=1;i<=V;i++){
		for(int j=0;j<=K;j++)for(int k=0;k<=j;k++){
			if(!dp[i][j][k])continue;
			// cout<<i<<","<<j<<","<<k<<" dp="<<dp[i][j][k]<<endl;
			for(int l=2*i;l<=V;l+=i){
				int val=pt[l]-pt[i];
				// cout<<"trans to "<<l<<" val="<<val<<endl;
				for(int s=0;k+s<=j;s++){
					// cout<<"s="<<s<<" coef="<<binom(val,s)<<endl;
					upd(dp[l][j+1][k+s], (ull)dp[i][j][k]*binom(val,s));
				}
			}
		}
	}
	for(int i=1;i<=V;i++)
		for(int j=0;j<=K;j++)for(int k=0;k<=j;k++)
		upd(ans, (ull)dp[i][j][k]*binom(n-pt[i],j-k));
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