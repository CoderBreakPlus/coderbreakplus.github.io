// created time: 2026-05-23 13:40:29
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
int n,mod;
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

int C[2005][2005],f[2005][2005];

void procedure(){
	n=read(),mod=read();
	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			addmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
	}
	f[0][0]=1;
	for(int i=1;i<=n;i++){
		for(int j=0;j<=i-1;j++){
			f[i][j]=(f[i][j]+(ull)f[i-1][j]*j)%mod;
			f[i][j+1]=(f[i][j+1]+(ull)f[i-1][j]*(i-1-j))%mod;
		}
		if(i>=2)
		for(int j=0;j<=i-2;j++)
			f[i][j+1]=(f[i][j+1]+(ull)f[i-2][j]*(i-1))%mod;
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<=n-i;j++){
			int cur=(ull)C[n][i+j]*f[i+j][j]%mod;
			printf("%d ",cur);
		}
		puts("");
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