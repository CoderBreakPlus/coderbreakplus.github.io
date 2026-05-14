// created time: 2026-05-14 09:13:59
// https://qoj.ac/contest/2559/problem/14416
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); };

ll n,a[505],sz[505],f[505][505],g[505][505],tmp[505],tmp2[505];
vector<ll>E[505];

void dfs(ll x,ll fa){
	sz[x]=1;
	for(auto y: E[x]){
		if(y==fa) continue;
		dfs(y, x);
		sz[x]+=sz[y];
	}

	for(int v=1; v<=n; v++){
		memset(tmp,0x3f,sizeof(tmp));
		tmp[1]=a[x]*v; int cur=1;
		for(auto y: E[x]){
			if(y==fa) continue;
			memset(tmp2,0x3f,sizeof(tmp2));
			for(int i=1;i<=cur;i++) tmp2[i]=min(tmp2[i], tmp[i]+g[y][v]);
			for(int i=1;i<=cur;i++)
				for(int j=1;j<=sz[y];j++)
					tmp2[i+j]=min(tmp2[i+j], tmp[i]+f[y][j]);
			memcpy(tmp,tmp2,sizeof(tmp));
			cur+=sz[y];
		}
		f[x][v] = tmp[v];
		for(int i=1;i<=cur && i<=v;i++){
			g[x][v-i] = min(g[x][v-i], tmp[i]);
		}
	}
}
void procedure(){
	memset(f,0x3f,sizeof(f)); memset(g,0x3f,sizeof(g));
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(), E[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	printf("%lld\n", g[1][0]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}
