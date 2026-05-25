// created time: 2026-05-25 10:59:50
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 509;
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
const int N=254500;
int n,a[N+5],f[N+5],g[N+5],C[mod][mod],tmp[N+5],h[N+5];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	C[0][0]=1;
	for(int i=1;i<mod;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			addmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
	}
	for(int i=0;i<=n;i++)f[i]=1;

	for(int i=mod,p=0;i<=n;i+=mod,p+=mod){
		memcpy(g,f,sizeof(g));
		for(int j=mod;j<=n;j++)addmod(f[j]+=f[j-mod]);
		for(int j=1;j<=mod;j++){
			tmp[j]=0;
			for(int k=0;k<mod&&k<=a[p+j];k++)
				tmp[j]=(tmp[j]+(ull)f[a[p+j]-k]*C[(k+j-1)%mod][j-1])%mod;
			for(int k=1;k<j;k++)
				if(a[p+j]>=a[p+k])
				tmp[j]=(tmp[j]+(ull)(mod-tmp[k])*C[(a[p+j]-a[p+k]+j-k)%mod][j-k])%mod;
		}
		for(int k=1;k<=mod;k++)
			for(int x=0;x<k;x++)
				g[a[p+k]+x]=(g[a[p+k]+x]+(ull)(mod-tmp[k])*C[x+mod-k][mod-k])%mod;
		for(int j=mod;j<=n;j++)addmod(g[j]+=g[j-mod]);
		memcpy(f,g,sizeof(f));
	}
	printf("%d\n",f[n]);
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