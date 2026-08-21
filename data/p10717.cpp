// created time: 2026-08-21 08:11:49
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

int n,k,M;
vector<int>E[105];
int f[105][1<<16],g[1<<16],h[1<<16];
int p[8][105],a[105][1<<8];

int pool[1<<20], *_p=pool;
void conv(int *a,int *b,int *c,int n){
	if(!n){
		c[0]=(ull)a[0]*b[0]%mod;
		return;
	}

	int M=(1<<2*n-2);
	int *_a=_p; _p+=M;
	int *_b=_p; _p+=M;
	int *_c=_p; _p+=M;
	for(int i=0;i<(M<<2);i++)c[i]=0;

	// (0,0)->0
	for(int i=0;i<M;i++) _a[i]=a[i<<2],_b[i]=b[i<<2];
	conv(_a,_b,_c,n-1);
	for(int i=0;i<M;i++) addmod(c[i<<2]+=_c[i]);

	// (0,1)->0
	for(int i=0;i<M;i++) _a[i]=a[i<<2],_b[i]=b[i<<2|1];
	conv(_a,_b,_c,n-1);
	for(int i=0;i<M;i++) addmod(c[i<<2|1]+=_c[i]);
	
	// (1,0)->0
	for(int i=0;i<M;i++) _a[i]=a[i<<2|1],_b[i]=b[i<<2];
	conv(_a,_b,_c,n-1);
	for(int i=0;i<M;i++) addmod(c[i<<2|1]+=_c[i]);
	
	// (0,2)->2
	for(int i=0;i<M;i++) _a[i]=a[i<<2|2],_b[i]=b[i<<2];
	conv(_a,_b,_c,n-1);
	for(int i=0;i<M;i++) addmod(c[i<<2|2]+=_c[i]);
	
	// (2,0)->2
	for(int i=0;i<M;i++) _a[i]=a[i<<2],_b[i]=b[i<<2|2];
	conv(_a,_b,_c,n-1);
	for(int i=0;i<M;i++) addmod(c[i<<2|2]+=_c[i]);
	
	// (0/2/3,0/2)->3
	for(int i=0;i<M;i++) _a[i]=(0ull+a[i<<2]+a[i<<2|2]+a[i<<2|3])%mod,addmod(_b[i]=b[i<<2]+b[i<<2|2]);
	conv(_a,_b,_c,n-1);
	for(int i=0;i<M;i++) c[i<<2|3]=(_c[i]+2ull*mod-c[i<<2]-c[i<<2|2])%mod;

	_p-=3*M;
}
void dfs(int x,int fa){
	for(int y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
	}

	memset(h,0,sizeof(h));
	h[0]=1;
	for(int y:E[x]){
		if(y==fa)continue;
		memset(g,0,sizeof(g));
		conv(h,f[y],g,k);
		memcpy(h,g,sizeof(h));
	}

	for(int i=1,w=0;i<M;i<<=2,w++){
		int P = p[w][x], Q = (mod+1-p[w][x])%mod;
		for(int j=0;j<i;j++)
		for(int k=0;k<M;k+=(i<<2)){
			auto [a0,a1,a2,a3]=(array<int,4>){h[j+k],h[j+i+k],h[j+2*i+k],h[j+3*i+k]};
			h[j+k]=(ull)a0*Q%mod;
			h[j+i+k]=(ull)a1*Q%mod;
			h[j+2*i+k]=(ull)a2*Q%mod;
			h[j+3*i+k]=(a3+(ull)(a0+a2)*P)%mod;
		}
	}
	for(int i=0;i<M;i++){
		int sta=0;
		for(int w=0;w<k;w++)
			sta^=(((i>>2*w+1)&1)<<w);
		f[x][i]=(ull)h[i]*a[x][sta]%mod;
	}
	for(int i=1;i<M;i<<=2)
		for(int j=0;j<i;j++)
		for(int k=0;k<M;k+=(i<<2)){
			addmod(f[x][j+i+k]+=f[x][j+3*i+k]);
			addmod(f[x][j+2*i+k]+=f[x][j+3*i+k]);
			f[x][j+3*i+k]=0;
		}
}
void procedure(){
	n=read(),k=read();
	M=(1<<2*k);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	for(int i=0;i<k;i++)
		for(int j=1;j<=n;j++)p[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=0;j<(1<<k);j++)a[i][j]=read();
	dfs(1,0);
	
	int ans=0;
	for(int i=0;i<M;i++){
		bool flg=0;
		for(int j=1;j<2*k;j+=2)
			if((i>>j)&1)flg=1;
		if(!flg) addmod(ans+=f[1][i]);
	}
	printf("%d\n",ans);
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