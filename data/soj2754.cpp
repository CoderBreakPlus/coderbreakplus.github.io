// created time: 2026-11-17 08:04:56
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int n; uint mod;
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

uint f[1000005],g[1000005];

void procedure(){
	n=read(),mod=read();

	f[1]=g[1]=1;
	uint sum=1;
	for(int l=2;l<=n;l<<=1){
		int r=min(l*2-1,n);

		// calc [l,r]
		// firsly: >=2 numbers

		for(int i=l+1;i<=r;i++){
			f[i]=(ull)(sum+1)*(i-l)%mod;
			int now=i^l;
			while(now){
				int t=(now&-now);
				f[i]=(0ull+f[i]+g[t-1]+mod-g[2*t-1])%mod;
				now^=t;
			}
		}

		uint cur=0;
		for(int i=l;i<=r;i++){
			addmod(f[i]+=cur);
			addmod(cur+=f[i]);
		}

		// secondly: <=1 numbers

		for(int i=l;i<=r;i++)addmod(f[i]+=sum+1);
		for(int i=l;i<=r;i++)addmod(sum+=f[i]),addmod(g[i]=g[i-1]+f[i]);
	}
	printf("%u\n",sum);
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