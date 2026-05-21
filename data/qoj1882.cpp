// created time: 2026-05-21 08:32:29
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

int n,p,iv;
int F[10005],G[10005];
int *f=F+5000;
int *g=G+5000;
int ans;

void procedure(){
	n=read(),p=read()*INV(100)%mod;
	ans=iv=INV(2*n+1);
	for(int i=-n;i<=n;i++)if(i)f[i]=iv;

	for(int i=1;i<=n;i++){
		int x=read();
		memset(G,0,sizeof(G));
		for(int j=-n;j<=n;j++){
			if(!f[j])continue;
			g[j]=(g[j]+(ull)p*f[j])%mod;
			if(j+x==0)ans=(ans+(ull)(mod+1-p)*f[j])%mod;
			else g[j+x]=(g[j+x]+(ull)(mod+1-p)*f[j])%mod;
		}
		memcpy(F,G,sizeof(F));
	}
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