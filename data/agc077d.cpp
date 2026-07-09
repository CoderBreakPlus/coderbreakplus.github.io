// created time: 2026-07-09 14:44:40
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

int n,f[5005],g[5005];
int h0[5005],h1[5005];

void procedure(){
	n=read(),mod=read();
	f[0]=g[0]=1, h0[0]=mod-1;

	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			h1[i]=(h1[i]+(ull)(mod-g[max(j-2,0)])*h0[i-j])%mod;
		}
		for(int j=1;j<=i;j++){
			h0[i]=(h0[i]+(ull)f[j]*h1[i-j]%mod*(j+1)%mod*(j+1))%mod;
		}
		addmod(h0[i]+=h1[i]);

		f[i]=h1[i];
		for(int j=1;j<i;j++){
			f[i]=(f[i]+(ull)h1[i-j]*(j+1)%mod*f[j])%mod;
		}

		g[i]=g[i-1];
		for(int j=1;j<=i;j++)
			g[i]=(g[i]+(ull)f[j]*g[max(0,i-j-1)])%mod;

		h0[i]=(h0[i]+(ull)(mod-f[i])*(i+1))%mod;
	}
	printf("%d\n",g[n]);
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