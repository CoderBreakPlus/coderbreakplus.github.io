// created time: 2026-05-18 07:41:22
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
const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

int n;
vector<int>E[3005];
int f[3005],g[3005],sz[3005],son[3005];

void dfs(int x,int fa){
	sz[x]=1, son[x]=E[x].size()==1;
	for(auto y:E[x])if(y!=fa){
		dfs(y,x);
		sz[x]+=sz[y],son[x]+=son[y];
	}
}
int pw[9000005],iv[9000005],w;

void upd(int x,int y){
	for(int i=0;i<=w;i++)for(int j=0;j<=y;j++)
		g[i+j]=(g[i+j]+(ull)f[i]*iv[j*x]%mod*binom(y,j))%mod;
	w+=y;
	for(int i=0;i<=w;i++)f[i]=g[i];
}
int final_test(){
	int ans=0;
	for(int i=0;i<=w;i++)
		if(i&1) ans=(ans+(ull)(mod-f[i])*pw[n*(n-1)/2+i*(i-1)/2])%mod;
		else ans=(ans+(ull)f[i]*pw[n*(n-1)/2+i*(i-1)/2])%mod;
	return ans;
}
int solve_point(int x){
	if(E[x].size()==1) return pw[n*(n-1)/2-son[1]+1];
	memset(f,0,sizeof(f));w=0;
	for(auto y:E[x]){
		if(sz[y]>sz[x]){
			upd(sz[x],son[n]-son[x]);
		}else{
			upd(n-sz[y],son[y]);
		}
	}
	return final_test();
}
int solve_edge(int x,int y){
	if(sz[x]<sz[y]) swap(x,y);
	memset(f,0,sizeof(f));w=0;
	upd(n-sz[y],son[y]);
	upd(sz[y],son[n]-son[y]);
	return final_test();
}
void procedure(){
	n=read();
	pw[0]=1;
	for(int i=1;i<=n*n;i++)addmod(pw[i]=2*pw[i-1]);
	iv[n*n]=INV(pw[n*n]);
	for(int i=n*n-1;i>=1;i--)addmod(iv[i]=2*iv[i+1]);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	int ans=0;
	for(int x=1;x<=n;x++){
		int ans_x=solve_point(x);
		cout<<"x="<<x<<" ans_x="<<ans_x<<endl;
		addmod(ans+=ans_x);
	}

	for(int x=1;x<=n;x++)
		for(auto y:E[x]) 
			if(x<y) addmod(ans+=mod-solve_edge(x,y));
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}