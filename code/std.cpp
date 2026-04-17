
// created time: 2026-04-17 07:15:46
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

const int M = 24;
int n,seed,c0[1<<M],c1[1<<M],iv[M+1];
void ifwt(int *a,int m){
	for(int t=1;t<(1<<m);t<<=1)
		for(int j=0;j<(1<<m);j+=(t<<1))
			for(int k=0;k<t;k++){
				int p=a[j+k], q=a[j+k+t];
				addmod(a[j+k]=p+q);
				addmod(a[j+k+t]=p+mod-q);
			}
	for(int j=0;j<(1<<m);j++) a[j]=(ull)a[j]*iv[m]%mod;
}
void procedure(){
	n=read(),seed=read();
	mt19937_64 rnd(seed);
	for(int i=0;i<(1<<n);i++){
		c0[i]=rnd()%mod;
		c1[i]=mod-c0[i];
		c0[i]++,c1[i]++;
	}
	for(int t=1;t<(1<<n);t<<=1)
		for(int j=0;j<(1<<n);j+=(t<<1))
			for(int k=0;k<t;k++){
				int p0=c0[j+k],p1=c1[j+k],q0=c0[j+k+t],q1=c1[j+k+t];
				c0[j+k]=(ull)p0*q0%mod;
				c1[j+k]=(ull)p1*q1%mod;
				c0[j+k+t]=(ull)p0*q1%mod;
				c1[j+k+t]=(ull)p1*q0%mod;
			}
	ifwt(c0,n);
	int ans=0;
	for(int i=0;i<(1<<n);i++) {
		ans=(1337ull*ans+c0[i])%mod;
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	iv[0]=1;
	for(int i=1;i<=M;i++)iv[i]=(ull)iv[i-1]*((mod+1)/2)%mod;
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}