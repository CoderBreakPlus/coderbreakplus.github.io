// created time: 2026-09-02 09:55:26
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

int n,m,c,l[10005],r[10005],vis[105][105][105];

int f[105][105],g[105][105];

void procedure(){
	n=read(),m=read(),c=read();
	for(int l=1;l<=n+1;l++)f[l][l-1]=1;

	for(int i=1;i<=m;i++){
		l[i]=read(),r[i]=read();
		for(int k=l[i];k<=r[i];k++)vis[k][l[i]][r[i]]=1;
	}	
	
	for(int k=1;k<=n;k++){
		for(int i=n;i>=1;i--)
			for(int j=i;j<=n;j++)if(vis[k][i][j]){
				if(j<n)vis[k][i][j+1]=1;
				if(i>1)vis[k][i-1][j]=1;
			}
	}
	for(int l=n;l>=1;l--){
		memset(g,0,sizeof(g));
		g[l-1][l-1]=1;
		for(int r=l;r<=n;r++){
			for(int i=l-1;i<r;i++){
				for(int j=l-1;j<=i;j++){
					if(vis[i][j+1][r-1]) continue;
					g[r][j]=(g[r][j]+(ull)g[i][j]*f[i+1][r-1])%mod;
					g[r][i]=(g[r][i]+(ull)g[i][j]*f[i+1][r-1]%mod*(c-1))%mod;
				}
			}
			f[l][r]=qpow(c,r-l+1);
			for(int i=l;i<=r;i++)
				for(int j=l-1;j<=i;j++)if(!vis[i][j+1][r]){
					f[l][r]=(f[l][r]+(ull)(mod-g[i][j])*f[i+1][r])%mod;
				}
		}
	}
	printf("%d\n",f[1][n]);
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