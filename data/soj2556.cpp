// created time: 2026-04-25 11:16:47
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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
const ull K=15ull*mod*mod;

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

int n,q;
int f[10005];
int a[10005],m[10005],iv[10005];
ull ans[10005];
const int B=8192;
ull pw[B+5], pwb[B+5];
void procedure(){	
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=a[n];i++)iv[i]=INV(i);
	for(int i=1;i<=q;i++) m[i]=read();
	f[1]=1;
	for(int i=2;i<=n;i++){
		ull tmp=0;
		for(int j=1;j<i;j++){
			tmp+=(ull)f[j]*iv[a[i]-a[j]];
			if(__builtin_expect(tmp>=K,0))tmp-=K;
			f[j]=(ull)f[j]*a[j]%mod*(mod-iv[a[i]-a[j]])%mod;
		}
		f[i]=tmp%mod*a[i]%mod;
	}
	for(int i=1;i<=n;i++){
		pw[0]=1;
		for(int j=1;j<=B;j++){
			pw[j]=(ull)pw[j-1]*a[i]%mod;
		}
		pwb[0]=1;
		for(int j=1;j<=B;j++){
			pwb[j]=(ull)pwb[j-1]*pw[B]%mod;
		}
		auto getpw = [&](int v){
			return (ull)pwb[v/B]*pw[v%B]%mod;
		};
		for(int j=1;j<=q;j++){
			ans[j]+=(ull)f[i]*getpw(m[j]);
			if(__builtin_expect(ans[j]>=K,0))ans[j]-=K;
		}
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]%mod);
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