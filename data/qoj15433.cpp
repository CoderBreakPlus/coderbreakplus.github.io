// created time: 2026-09-10 07:38:36
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

vector<pair<int,int>>E[2005];
int n,sz[2005];
ll f[2005][4005],sum[2005],t0[4005][3],t1[4005][3],ans[4005];

void dfs(int x,int fa,int w){
	sz[x]=1;
	for(auto [y,w2]:E[x])if(y!=fa)
		dfs(y,x,w2);

	memset(t0,0xc0,sizeof(t0));
	t0[1][0]=sum[x]=w;
	for(auto [y,w2]:E[x])if(y!=fa){
		sum[x]+=sum[y];
		memcpy(t1,t0,sizeof(t1));
		// cout<<"sb "<<t1[1][0]<<endl;
		for(int i=1;i<2*sz[x];i++)for(int ii=0;ii<3;ii++){
			if(ii<2)
				for(int j=1;j<2*sz[y];j++)
					chkmax(t0[i+j][ii+1], t1[i][ii]+f[y][j]);
			chkmax(t0[i+2*sz[y]][ii], t1[i][ii]+2*sum[y]);
			// cout<<"merging "<<t1[i][ii]<<" + "<<2*sum[y]<<endl;
		}
		sz[x]+=sz[y];
	}
	// cout<<"sum = "<<sum[x]<<" t0 = "<<t0[2*sz[x]-1]
	for(int i=1;i<2*sz[x];i++){
		chkmax(ans[i-1], max({t0[i][0],t0[i][1],t0[i][2]})-w);
		// if(i-1==8){
		// 	cout<<"at "<<x<<" find "<<t0[i][0]<<","<<t0[i][1]<<","<<t0[i][2]<<" - "<<w<<endl;
		// }
		f[x][i]=max(t0[i][0],t0[i][1]);
	}
	// cout<<"at "<<x<<" w = "<<w<<endl;
	// for(int i=1;i<2*sz[x];i++) cout<<f[x][i]<<" "; cout<<endl;
	// cout<<"at "<<x<<" full = "<<f[x][2*sz[x]-1]<<endl;
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)E[i].clear();
	memset(ans,0xc0,sizeof(ans));
	ll tot=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		E[u].pb(v,w),E[v].pb(u,w); tot+=w;
	}
	dfs(1,0,0);
	for(int i=0;i<=2*n-2;i++) printf("%lld ",2*tot-ans[i]);
	puts("");
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