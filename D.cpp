// created time: 2026-06-15 07:06:29
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

int n; ull a[5005],b[5005],c[65][65];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();

	if(n>60){
		puts("0");
		return;
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)c[i][j]=a[i]^b[j];

	int rev=1;
	for(int i=1;i<=n;i++){
		int p=i;
		for(int j=i+1;j<=n;j++)
			if(c[j][i])p=j;
		if(i^p)rev=mod-rev,swap(c[i],c[p]);
		if(!c[i][i]){
			puts("0");
			return;
		}
		int inv = INV(c[i][i]);
		for(int j=i+1;j<=n;j++)
			for(int k=i;k<=n;k++)
				c[j][k]=(c[j][k]+(ull)c[i][k]*c[j][i]%mod*inv)%mod;
	}
	for(int i=1;i<=n;i++)
		rev=(ull)rev*c[i][i]%mod;
	printf("%d\n",rev);
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