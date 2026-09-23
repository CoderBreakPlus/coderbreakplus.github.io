// created time: 2026-09-23 08:06:34
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int n,k,a[3005][3005],p[3005],q[3005];
int code(int i,int j){ return (i-1)*n+j; }
int fa[9000005],sz1[9000005],sz[9000005];

int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	// cout<<"merge "<<x<<","<<y<<endl;
	sz[x]+=sz[y],sz1[x]+=sz1[y];
	fa[y]=x;
}
void procedure(){
	n=read(),k=read();
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++)a[i][j]=read();

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)fa[code(i,j)]=code(i,j),sz1[code(i,j)]=i>j,sz[code(i,j)]=1;

	int T=50;
	while(T--){
		for(int i=1;i<=n;i++)p[i]=i;

		int t=rng(1,n);
		while(t--){
			int x=rng(1,k);
			for(int i=1;i<=n;i++)q[i]=a[x][p[i]];
			swap(p,q);
		}

		for(int i=1;i<=n;i++)q[p[i]]=i;

		for(int i=1;i<=n;i++)
			for(int j=1;j<=n;j++){
				merge(code(i,j),code(q[i],q[j]));
			}
	}
	int ans=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			int x=find(code(i,j));
			// cout<<"at "<<x<<" find "<<sz1[x]<<","<<sz[x]<<endl;
			ans=(ans+(ull)sz1[x]*INV(sz[x]))%mod;
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