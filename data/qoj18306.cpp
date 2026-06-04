// created time: 2026-06-04 07:41:49
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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
const int B=17,N=1e5+5;
int n,f[N][B+1],g[N][B+1],dp[N];
vector<int>E[N];

void dfs(int x,int fa){
	if(fa)E[x].erase(find(E[x].begin(),E[x].end(),fa));
	// calc f
	f[x][0]=1;
	for(int y:E[x]){
		// cout<<"here "<<y<<endl;
		dfs(y,x);
		f[x][0]=(ull)f[x][0]*dp[y]%mod;
	}
	for(int i=1;i<B;i++){
		int f0=1,f1=0,f2=0;
		for(int y:E[x]){
			f2=((ull)f2*dp[y]+(ull)f1*f[y][i-1])%mod;
			f1=((ull)f1*dp[y]+(ull)f0*f[y][i-1])%mod;
			f0=(ull)f0*dp[y]%mod;
		}
		f[x][i]=f2;
		g[x][i-1]=f1;
	}
	// calc g
	for(int i=0;i<B;i++){
		int f0=1,f1=0,f2=0,f3=0;
		for(int y:E[x]){
			f3=((ull)f3*dp[y]+(ull)f1*g[y][i+1]+(ull)f2*f[y][i])%mod;
			f1=((ull)f1*dp[y]+(ull)f0*f[y][i])%mod;
			f2=((ull)f2*dp[y]+(ull)f0*g[y][i+1])%mod;
			f0=(ull)f0*dp[y]%mod;
		}
		addmod(g[x][i]+=f3);
	}
	// calc dp
	for(int i=0;i<B;i++) addmod(dp[x]+=f[x][i]);
	{
		int f0=1,f1=0;
		for(int y:E[x]){
			f1=((ull)f1*dp[y]+(ull)f0*g[y][0])%mod;
			f0=(ull)f0*dp[y]%mod;
		}
		addmod(dp[x]+=f1);
	}
	for(int i=1;i<B;i++){
		int f00=1,f01=0,f02=0,f10=0,f11=0,f12=0;
		for(int y:E[x]){
			f12=((ull)f12*dp[y]+(ull)f11*f[y][i-1]+(ull)f02*g[y][i])%mod;
			f11=((ull)f11*dp[y]+(ull)f10*f[y][i-1]+(ull)f01*g[y][i])%mod;
			f10=((ull)f10*dp[y]+(ull)f00*g[y][i])%mod;

			f02=((ull)f02*dp[y]+(ull)f01*f[y][i-1])%mod;
			f01=((ull)f01*dp[y]+(ull)f00*f[y][i-1])%mod;
			f00=(ull)f00*dp[y]%mod;
		}
		addmod(dp[x]+=f12);
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		E[i].clear();
		memset(f[i],0,sizeof(f[i])),memset(g[i],0,sizeof(g[i]));
		dp[i]=0;
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	printf("%d\n", dp[1]);
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