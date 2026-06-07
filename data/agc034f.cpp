// created time: 2026-06-07 07:35:35
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

int n,p[1<<18],f[1<<18],ivn;

void fwt(int *a){
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)if((~j>>i)&1){
			int p=a[j],q=a[j^(1<<i)];
			addmod(a[j]=p+q);
			addmod(a[j^(1<<i)]=p+mod-q);
		}
}
int g[1<<18],h[1<<18];

void procedure(){
	n=read(),ivn=INV(1<<n);
	int sum=0;
	for(int i=0;i<(1<<n);i++)
		sum+=(p[i]=read());
	sum=INV(sum);
	for(int i=0;i<(1<<n);i++){
		p[i]=(ull)p[i]*sum%mod;
		addmod(f[i]=mod-p[i]+(!i));
		g[i]=f[i];
	}

	fwt(f);
	// for(int i=0;i<(1<<n);i++)cout<<f[i]<<" ";cout<<endl;
	for(int i=0;i<(1<<n);i++)f[i]=INV(f[i]);
	fwt(f);
	// for(int i=0;i<(1<<n);i++)cout<<f[i]<<" ";cout<<endl;

	for(int i=0;i<(1<<n);i++)
		printf("%d\n",(mod+f[0]-f[i])%mod);
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