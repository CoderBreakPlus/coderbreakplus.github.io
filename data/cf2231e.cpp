// created time: 2026-06-04 15:59:24
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

int n,d;

ll f[2005][2005][4],sz[2005],tmp[2005][4],ans;
vector<int>E[2005];

void dfs(int x,int fa){
	if(fa)E[x].erase(find(E[x].begin(),E[x].end(),fa));
	sz[x]=1;
	memset(f[x],0,sizeof(f[x]));

	f[x][1][0]=f[x][1][1]=1;
	for(int y:E[x]){
		dfs(y,x);
		memset(tmp,0,sizeof(tmp));
		for(int i=1;i<=sz[x];i++)for(int p=0;p<=2;p++)
			for(int j=1;j<=sz[y];j++)for(int q=1;q<=2&&p+q<=3;q++)
				tmp[i+j][p+q]+=f[x][i][p]*f[y][j][q];

		sz[x]+=sz[y];
		for(int i=1;i<=sz[x];i++)
			for(int o:{0,1,2,3})f[x][i][o]+=tmp[i][o];
	}
	// cout<<"x="<<x<<endl;
	// for(int i=1;i<=sz[x];i++){
	// 	cout<<f[x][i][0]<<" "<<f[x][i][1]<<" "<<f[x][i][2]<<" "<<f[x][i][3]<<endl;
	// }
	ans+=f[x][d][3];
}
void procedure(){
	n=read(),d=read();
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	ans=0;
	dfs(1,0);
	printf("%lld\n",ans);
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