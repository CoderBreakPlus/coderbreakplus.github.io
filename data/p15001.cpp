// created time: 2026-05-22 07:25:00
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

int n,a[65],x[65],y[65],z[65];
ll f[65][65][65][65];

ll sqr(ll u){ return u*u; }
ll calc(int l,int r,int i,int k){
	l--,r++;
	return sqr(a[l]-x[k])+sqr(a[k]-y[r])+sqr(a[r]-z[i]);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)x[i]=read();
	for(int i=1;i<=n;i++)y[i]=read();
	for(int i=1;i<=n;i++)z[i]=read();

	// 对题解的补充：为什么递归右边的子问题的时候，对应的 id[i+2] 依然是原问题的 x？
	// 因为这部分贡献等于 (a[r+1]-z[x])^2，右边的操作顺序和 [l,r] 内部的操作可以任意顺序归并。
	// 所以在最优方案中必然选择同一个 x，若选择不同的 x 则必然有一个最大的，不如都选它。
		
	// for(int i=1;i<=n;i++)
	// 	for(int j=i+2;j<=n+2;j++)
	// 		f[i][i][j][i]=f[i][i][j][i+1]=calc(i,i,j,i);
	for(int w=1;w<=n;w++)
		for(int l=1,r=w;l<=n;l++,r++)
		for(int i=r+2;i<=n+2;i++){
			for(int j=l;j<=r;j++)
			for(int k=j;k<=r;k++)for(int x=k+1;x<=r+1;x++)
				chkmax(f[l][r][i][j],f[l][k-1][x][j]+f[k+1][r][i][x]+calc(l,r,i,k));
			int j=r+1;
			for(int k=l;k<=r;k++)for(int x=k+1;x<=r+1;x++)
				chkmax(f[l][r][i][j],f[l][k-1][x][k]+f[k+1][r][i][x]+calc(l,r,i,k));
		}

	ll ans=0;
	for(int i=0;i<=n+2;i++)
	for(int j=0;j<=n+2;j++)chkmax(ans,f[1][n][i][j]);
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