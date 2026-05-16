// created time: 2026-05-16 11:12:19
// #pragma GCC optimize(3,"inline")
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int n,m,q;
int u[100005],v[100005]; ull w[100005],ee[100005];
int pt[100005];

struct dsu{
	int fa[505];
	inline int find(int x){ if(x!=fa[x]) fa[x]=find(fa[x]); return fa[x]; }
	inline void init(){
		for(int i=1;i<=n;i++) fa[i]=i;
	}
	inline void merge(int x,int y){ fa[find(x)]=find(y); }
	bool check(int x,int y){ return find(x)!=find(y); }
}ds[100005];

vector<int>vec[100005];

struct Edge{
	int to,nxt;
	ull w,ee;
}e[1005];
int hd[505], dfn[505], tot, tim;
ull tmp[505];
void add(int u,int v,ull w,ull ee){
	e[++tot]=(Edge){v,hd[u],w,ee};
	hd[u]=tot;
}

ull qz[100005][505],ans;

void dfs(int x,int f){
	dfn[x]=++tim;
	for(int i=hd[x];i;i=e[i].nxt){
		if((i^f)==1) continue;
		int y=e[i].to;
		if(!dfn[y]){
			dfs(y,i);
			tmp[x]^=tmp[y];
			if(tmp[y]==e[i].ee) ans+=e[i].w;
		}
	}
}
void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read(),w[i]=read(),ee[i]=rnd();
		memcpy(qz[i],qz[i-1],sizeof(qz[i]));
		qz[i][u[i]]^=ee[i],qz[i][v[i]]^=ee[i];
	}
	for(int i=1;i<=m;i++) vec[i].reserve(n-1),ds[i].init();

	for(int i=1;i<=m;i++){
		int L=1, R=i-1; pt[i]=i;
		while(L<=R){
			int mid=(L+R)>>1;
			if(ds[mid].check(u[i],v[i])) pt[i]=mid,R=mid-1;
			else L=mid+1;
		}
		for(int j=pt[i];j<=i;j++){
			vec[j].pb(i);
			ds[j].merge(u[i],v[i]);
		}
	}

	while(q--){
		int l=read(), r=read();
		tot=1, tim=ans=0;
		memset(hd,0,sizeof(hd));
		memset(dfn,0,sizeof(dfn));

		// cout<<"l="<<l<<" find "<<vec[l].size()<<endl;
		for(auto x: vec[l]){
			if(x>r)break;
			// cout<<"add edge "<<u[x]<<" "<<v[x]<<" "<<w[x]<<" "<<ee[x]<<endl;
			add(u[x],v[x],w[x],ee[x]);
			add(v[x],u[x],w[x],ee[x]);
		}
		for(int x=1;x<=n;x++) tmp[x]=qz[r][x]^qz[l-1][x];
		for(int x=1;x<=n;x++)
			if(!dfn[x]) dfs(x,0);

		printf("%llu\n",ans);
	}
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