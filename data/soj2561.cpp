// created time: 2026-06-03 18:31:09
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

int n,a[1<<16],f[1<<16];
void procedure(){
	n=read();
	int sum=0;
	a[0]=0;for(int i=1;i<(1<<n);i++)a[i]=read();
	for(int m=1;m<(1<<n);m<<=1){
		for(int i=0;i<m;i++)for(int j=0;j<(1<<n);j+=(m<<1)){
			int p=a[i+j],q=a[i+j+m];
			addmod(a[i+j]=p+q);
			addmod(a[i+j+m]=p+mod-q);
		}
	}
	for(int i=0;i<(1<<n);i++){
		f[i]=1;
		for(int j=0;j<(1<<n);j++)if(i^j){
			f[i]=(ull)f[i]*(a[i]-a[j]+mod)%mod;
		}
	}
	for(int m=1;m<(1<<n);m<<=1){
		for(int i=0;i<m;i++)for(int j=0;j<(1<<n);j+=(m<<1)){
			int p=f[i+j],q=f[i+j+m];
			addmod(f[i+j]=p+q);
			addmod(f[i+j+m]=p+mod-q);
		}
	}
	for(int i=0;i<(1<<n);i++)printf("%d ",(ull)f[i]*INV((1ull<<2*n)%mod)%mod);puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}