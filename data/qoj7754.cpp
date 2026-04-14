// created time: 2026-04-14 18:07:17
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
int n,m,a[12],b[12],dp[1<<12][1005],ok[1<<12],iv[10005],g[1005],h[1005];

inline void upd(int &a,ll b){ a=(a+b)%mod; }
void procedure(){
	n=read(),m=read();
	for(int i=0;i<m;i++)a[i]=read();
	int sta=0,ans=0;
	for(int i=0;i<m;i++){
		ans+=(b[i]=read());
		if(!b[i])sta|=(1<<i);
	}

	for(int i=0;i<(1<<m);i++){
		ok[i]=n;
		for(int k=0;k<m;k++)
			if((i>>k)&1)ok[i]-=a[k];
	}
	dp[sta][0]=1;

	for(int i=0;i+1<(1<<m);i++){
		if((i&sta)!=sta) continue;
		memset(g,0,sizeof(g));
		g[0]=1;

		int loc=0,res=0,sum=0;
		for(int j=0;j<m;j++){
			if((i>>j)&1){ loc+=a[j]-b[j]; continue; }
			memset(h,0,sizeof(h));
			res+=a[j];
			sum+=b[j]-1;
			for(int l=0;l<b[j];l++)
				for(int k=0;k+l<=sum;k++)
					upd(h[k+l], (ll)g[k]*binom(a[j],l));
			memcpy(g,h,sizeof(g));
		}
		for(int j=0;j<=ok[i];j++){
			if(!dp[i][j])continue;
			if(ok[i]>=j){
				int val=(ll)dp[i][j]*iv[ok[i]-j]%mod;
				addmod(dp[i][j+1]+=val);
				for(int k=0;k<m;k++)if(((~i>>k)&1)&&j+1>=b[k]){
					upd(dp[i^(1<<k)][j+1-b[k]], (ll)val*binom(j,b[k]-1)%mod*perm(a[k],b[k]));
				}
			}
		}
		
		for(int j=0;j<=res;j++){
			int cf=(ll)dp[i][j]*g[j]%mod*fac[j]%mod;
			int exp=(ll)loc*iv[res-j]%mod;
			upd(ans, (ll)cf*exp);
		}
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	for(int i=1;i<=10000;i++)iv[i]=INV(i);
	math_init();
	while(T--) procedure();
	return 0;
}