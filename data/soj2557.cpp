// created time: 2026-05-15 08:18:27
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

int n;
struct Tree{
	vector<int>E[500005];
	void add(int x,int y){
		E[x].pb(y),E[y].pb(x);
	}
	int dfn[500005],tim,seq[500005],sz[500005];

	void dfs(int x,int fa){
		vector<int>g; sz[x]=1;
		for(auto y:E[x]){
			if(y==fa)continue;
			dfs(y,x); sz[x]+=sz[y]; g.emplace_back(y);
		}
		sort(g.begin(),g.end(),[&](int x,int y){ return sz[x]>sz[y]; });
		swap(g,E[x]);
	}
	void dfs2(int x){
		seq[dfn[x]=++tim]=x;
		for(auto y:E[x]) dfs2(y);
	}
}T1,T2;
vector<pair<int,int>>upd[500005],qry[500005];

int sb[500005],ans[500005];

void ins(int p,int q,int c){
	upd[p].pb(q,c);
}
void add(int l,int r,int s,int t){
	ins(r,t,1), ins(l-1,s-1,1);
	ins(l-1,t,-1), ins(r,s-1,-1);
}

struct BIT{
	int c[500005];
	void upd(int x,int w){
		while(x<=n){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	int qry(int x){
		int ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
}B;

void procedure(){
	n=read();
	for(int i=1;i<n;i++) T1.add(read(),read());
	for(int i=1;i<n;i++) T2.add(read(),read());
	T1.dfs(1,0); T2.dfs(1,0);
	T1.dfs2(1); T2.dfs2(1);

	for(int x=1;x<=n;x++){
		int pt=0, sz2=T2.E[x].size();
		for(auto y:T1.E[x]){
			while(pt<sz2 && T2.sz[T2.E[x][pt]]>T1.sz[y]) pt++;
			add(T1.dfn[y],T1.dfn[y]+T1.sz[y]-1,T2.dfn[x]+1,(pt==sz2?(T2.dfn[x]+T2.sz[x]):T2.dfn[T2.E[x][pt]])-1);
			if(n-T1.sz[y]>T2.sz[x]){
				add(T1.dfn[y],T1.dfn[y]+T1.sz[y]-1,1,T2.dfn[x]-1);
				add(T1.dfn[y],T1.dfn[y]+T1.sz[y]-1,T2.dfn[x]+T2.sz[x],n);
			}
		}
		for(auto y:T2.E[x]){
			if(T1.sz[x]>n-T2.sz[y]){
				add(1,T1.dfn[x]-1,T2.dfn[y],T2.dfn[y]+T2.sz[y]-1);
				add(T1.dfn[x]+T1.sz[x],n,T2.dfn[y],T2.dfn[y]+T2.sz[y]-1);
			}
		}
		if(T1.sz[x]>T2.sz[x]){
			add(1,T1.dfn[x]-1,1,T2.dfn[x]-1);
			add(1,T1.dfn[x]-1,T2.dfn[x]+T2.sz[x],n);
			add(T1.dfn[x]+T1.sz[x],n,1,T2.dfn[x]-1);
			add(T1.dfn[x]+T1.sz[x],n,T2.dfn[x]+T2.sz[x],n);
		}
	}

	for(int i=1;i<=n;i++) qry[T1.dfn[i]].pb(T2.dfn[i],i);
	for(int i=n;i>=1;i--){
		for(auto [x,y]: upd[i]) B.upd(n-x+1,y);
		for(auto [x,y]: qry[i]) ans[y]=B.qry(n-x+1);
	}
	for(int i=1;i<=n;i++)
		printf("%d ", ans[i]);
	puts("");
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