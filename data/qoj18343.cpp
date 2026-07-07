// created time: 2026-07-07 17:22:17
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

int n,q,l[5005],r[5005],f[5005][5005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)l[i]=read(),r[i]=read();
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=i;j<=n;j++){
			f[i][j]=(sum+j-i)/(j-i+1);
			sum+=l[j+1]-r[j];
		}
	}
	for(int i=n;i>=1;i--)
		for(int j=i;j<=n;j++)
			chkmax(f[i][j],max(f[i][j-1],f[i+1][j]));

	while(q--){
		int l=read(),r=read();
		printf("%d\n",f[l][r]);
	}
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