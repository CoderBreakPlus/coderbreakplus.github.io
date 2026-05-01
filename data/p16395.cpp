// created time: 2026-05-01
// https://www.luogu.com.cn/problem/P16395
#include<bits/extc++.h>
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

int n,q,a[100005],u,v,x[100005],y[100005],k[100005],lca[100005],dis[100005],dep[100005],dep2[100005];
int rt,wh,mxs[100005],jp[100005],sz[100005],dfn[100005],f[20][100005],vis[100005],tim;

int head[100005], to[200005], nxt[200005], edge_cnt = 0;
inline void add_edge(int u, int v) {
    to[++edge_cnt] = v;
    nxt[edge_cnt] = head[u];
    head[u] = edge_cnt;
}

vector<int> son[100005], tag[100005];
__gnu_pbds::gp_hash_table<int, __gnu_pbds::null_type> st[100005];
__gnu_pbds::gp_hash_table<int,int> mp[100005];
vector<pair<int,int>> vec[100005];

inline void dfss(int x,int fa){
	dfn[x]=(++tim);
	f[0][dfn[x]]=fa;
	for(int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if(y==fa) continue;
		dep[y]=dep[x]+1;
		dfss(y,x);
	}
}
inline int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
inline int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
inline int dist(int x,int y){
	return dep[x]+dep[y]-2*dep[LCA(x,y)]+1;
}
inline void findcent(int x,int fa){
	mxs[x]=0,sz[x]=1;
	for(int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if(y==fa||vis[y]) continue;
		findcent(y,x);
		sz[x]+=sz[y];
		mxs[x]=max(mxs[x],sz[y]);
	}
	mxs[x]=max(mxs[x],wh-sz[x]);
	if(mxs[x]<mxs[rt]) rt=x;
}
inline void solve(int x){
	vis[x]=1;
	int cur=wh;
	for(int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if(vis[y]) continue;
		rt=0, wh=(sz[y]<sz[x] ? sz[y] : cur-sz[x]);
		findcent(y,x);
		dep2[rt]=dep2[x]+1;
		jp[rt]=x;
		solve(rt);
	}
}
set<pair<int,int>,greater<pair<int,int>>> S;
int buc[100005];

inline void dfs(int x,int fa){
	S.erase({buc[a[x]], a[x]});
	S.insert({++buc[a[x]], a[x]});

	for(auto i:tag[x]){
		auto it=S.begin();
		while(it!=S.end()&&(ll)(it->fi)*2*k[i]>dis[i]){
			st[i].insert(it->se);
			it++;
		}
	}
	for(int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if(y!=fa && vis[y]) dfs(y,x);
    }

	S.erase({buc[a[x]], a[x]});
	S.insert({--buc[a[x]], a[x]});
}
inline void dfs2(int x,int fa){
	++buc[a[x]];
	for(auto i:tag[x])
		for(auto c:st[i]) mp[i][c]+=buc[c];
	for(int i = head[x]; i; i = nxt[i]) {
        int y = to[i];
        if(y!=fa && vis[y]) dfs2(y,x);
    }
	--buc[a[x]];
}
void procedure(){
	n=read(),q=read();
	tim=0;
	edge_cnt = 0; 
	memset(head, 0, sizeof(head));
	for(int i=1;i<=n;i++) vec[i].clear(), tag[i].clear(), son[i].clear(), vis[i]=jp[i]=dep[i]=dep2[i]=0;
	for(int i=1;i<=q;i++) st[i].clear(), mp[i].clear();

	for(int i=1;i<=n;i++) a[i]=read();

	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add_edge(u, v);
		add_edge(v, u);
	}
	dfss(1,0);
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	mxs[0]=wh=n;
	findcent(1,0); solve(rt);

	for(int i=1;i<=n;i++){
		int x=i;
		while(x){
			son[x].push_back(i);
			x=jp[x];
		}
	}

	for(int i=1;i<=q;i++){
		x[i]=read(),y[i]=read(),k[i]=read();
		dis[i]=dist(x[i],y[i]);

		if(dep2[x[i]]<dep2[y[i]]) swap(x[i],y[i]);
		int xx=x[i], yy=y[i];

		while(dep2[xx]>dep2[yy]) xx=jp[xx];
		while(xx!=yy) xx=jp[xx], yy=jp[yy];

		vec[xx].push_back({x[i],i});
		vec[xx].push_back({y[i],i});

		lca[i]=xx;
	}

	for(int i=1;i<=n;i++) vis[i]=0;
	for(int i=1;i<=n;i++){
		S.clear();
		for(auto x: son[i]) tag[x].clear(), vis[x]=1;
		for(auto [a,b]: vec[i]) tag[a].push_back(b);

		dfs(i,0);
		for(auto x: son[i]) vis[x]=0;
	}

	for(int i=1;i<=q;i++)
		mp[i][a[lca[i]]]--;

	for(int i=1;i<=n;i++){
		for(auto x: son[i]) tag[x].clear(), vis[x]=1;
		for(auto [a,b]: vec[i]) tag[a].push_back(b);

		dfs2(i,0);
		for(auto x: son[i]) vis[x]=0;
	}

	for(int i=1;i<=q;i++){
		vector<int> out;
		for(auto [x,y]: mp[i])
			if((ll)y*k[i] > dis[i]) out.push_back(x);
		sort(out.begin(), out.end());
		if(!out.size()) puts("-1");
		else{
			for(auto x:out) printf("%d ",x);
			puts("");
		}
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	while(T--) procedure();
	return 0;
}