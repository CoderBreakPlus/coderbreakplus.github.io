// created time: 2026-09-14 10:24:59
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

void upd(int &a, ull b){ a=(a+b)%mod; }

int n,w[85],C[85][85];

int f[85][85][85],ans[85],out[85],g[85][85],fac[85];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)w[i]=read()+1;

	for(int x=1;x<=n;x++){ // x 个可空上升段
		memset(f,0,sizeof(f));
		memset(g,0,sizeof(g));
		// cout<<"x="<<x<<endl;
		f[0][0][0]=1;

		for(int a=0;a<n;a++)
			for(int b=0;a+b<n;b++){
				for(int i=1;i<=x;i++)
					upd(g[a][b], (ull)qpow(x-i,a)*qpow(x-i+1,b));
				g[a][b]=(ull)g[a][b]*fac[a+b]%mod;
			}
		int F;
		for(int i=0;i<=n;i++)
			for(int j=0;j<=i;j++)
				for(int k=0;k<=n-i;k++)if(F=f[i][j][k]){
					if(i==n)continue;

					addmod(f[i+1][j][k] += F);
					if(j) addmod(f[i+1][j+1][k-1] += F);

					int FF = (ull)F*w[i+1]%mod;
					for(int a=0;a<=i-j;a++){
						int FFF = (ull)FF*C[i-j][a]%mod;
						for(int b=0;b+k<=n-i-1;b++)
							upd(f[i+1][j+a+1][b+k], (ull)FFF*C[b+k][b]%mod*g[a][b]);
					}
				}
		ans[x]=f[n][n][0];
	}
	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			upd(ans[i], (ull)(mod-ans[j])*C[i][j]);

	for(int i=1;i<=n;i++)
		for(int j=1;j<i;j++)
			upd(ans[i], (ull)(mod-ans[j])*C[n-j][i-j]);

	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	fac[0]=1;
	for(int i=1;i<=80;i++)fac[i]=(ull)fac[i-1]*i%mod;
	for(int i=0;i<=80;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			addmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);		
	}
	// math_init();
	while(T--) procedure();
	return 0;
}