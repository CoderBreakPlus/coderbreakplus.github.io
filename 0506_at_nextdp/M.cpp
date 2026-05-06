// created time: 2026-05-05 13:01:49
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

const int N=22;
int n,pw[(1<<N)+10],f[(1<<N)+10];
char s[(1<<N)+10];

void procedure(){
	n=read();	
	scanf("%s",s);
	pw[0]=10;
	for(int i=1;i<=n;i++)pw[i]=(ull)pw[i-1]*pw[i-1]%mod;
	
	for(int i=0;i<(1<<n);i++)f[i]=s[i]-'0';

	for(int m=1;m<(1<<n);m<<=1){
		for(int i=0;i<(1<<n);i+=(m<<1))
			for(int k=0;k<m;k++)
				f[i+m+k]=(f[i+m+k]+(ull)f[i+k]*pw[__builtin_popcount(k)])%mod;

		// for(int i=0;i<(1<<n);i++)cout<<f[i]<<" ";cout<<endl;
	}
	ll ans=0;
	for(int i=0;i<(1<<n);i++)ans+=(f[i]^i);
	printf("%lld\n",ans);
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