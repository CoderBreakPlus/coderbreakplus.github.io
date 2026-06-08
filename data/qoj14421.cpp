// created time: 2026-05-14 08:50:47
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

int n,m,q,a[100005],dis[405][100005],rt[100005];
vector<int>E[100005];

void dfs(int x,int fa){
	for(auto y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
	}
}
int que[100005],hd,tl;
int fa[100005],sz[100005];

int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x!=y)
	sz[x]+=sz[y],fa[y]=x;
}
void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
		merge(u,v);
	}
	for(int i=1;i<=n;i++) rt[i]=i;
	shuffle(rt+1,rt+n+1,rnd);
	int K=min(200,n);

	for(int i=1;i<=K;i++){
		que[hd=tl=1]=rt[i];
		dis[i][rt[i]]=1;

		while(hd<=tl){
			int x=que[hd++];
			for(auto y:E[x]){
				if(dis[i][y])continue;
				dis[i][y]=dis[i][x]+1;
				que[++tl]=y;
			}
		}
	}
	while(q--){
		int u=read(),v=read(),ok=0;
		if(find(u)!=find(v)){
			puts("YES");
			continue;
		}
		if(sz[find(u)]<=20000){
			puts("NO");
			continue;
		}
		for(int i=1;i<=K;i++)
			if(dis[i][u]&&dis[i][v])
			ok|=(dis[i][u]+dis[i][v]-2<=20000);
		puts(ok?"NO":"YES");
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	// math_init();
	procedure();
	return 0;
}