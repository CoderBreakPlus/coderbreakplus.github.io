// created time: 2026-07-31 19:00:34
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
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
const int N = 2e5+5;
const int M = 6e6+5;
int n,q,c[N],u[N],v[N],dfn[N],ans[N],sz[N],son[N],ord[N],tim;
vector<int> E[N];
int seq[M],tl,pos[N];

int stk[N],tp;
void dfs(int x,int fa){
	dfn[x]=++tim,ord[tim]=x;
	sz[x]=1;
	for(int y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
		sz[x]+=sz[y];
		if(!son[x]||sz[son[x]]<sz[y])son[x]=y;
	}
}
void build(int x,int fa){
	int cur=tp;
	for(int y:E[x]){
		if(y==fa||y==son[x])continue;
		build(y,x);
		while(tp>cur)seq[++tl]=-stk[tp--];
	}
	if(son[x]) build(son[x],x);
	seq[++tl]=stk[++tp]=x;
	for(int y:E[x]){
		if(y==fa||y==son[x])continue;
		for(int i=dfn[y];i<dfn[y]+sz[y];i++)
			seq[++tl]=stk[++tp]=ord[i];
	}
	pos[x]=tl;
}
int B,ordq[N];
namespace DS{
	const int B = 450, w = 2e5;
	int buc[N],bl[N],lf[N],rh[N],mx[N/B+5],x,y;
	int ct[N/B+5][N];
	void init(){
		for(int i=1;i<=w;i++) bl[i]=(i-1)/B+1,rh[bl[i]]=i;
		for(int i=w;i>=1;i--) lf[bl[i]]=i;
	}
	void add(int x){
		int o=bl[x];
		ct[o][buc[x]]--;
		buc[x]++;
		ct[o][buc[x]]++;
		chkmax(mx[o], buc[x]);
	}
	void del(int x){
		int o=bl[x];
		ct[o][buc[x]]--;
		buc[x]--;
		ct[o][buc[x]]++;
		if(!ct[o][mx[o]]) mx[o]--;
	}
	void Add(int x){ if(x<0) del(c[-x]); else add(c[x]); }
	void Del(int x){ if(x<0) add(c[-x]); else del(c[x]); }
	void move(int X,int Y){
		while(x<X) Add(seq[++x]); while(x>X) Del(seq[x--]);
		while(y<Y) Add(seq[++y]); while(y>Y) Del(seq[y--]);
	}
	int query(){
		int mxa=0;
		for(int i=1;i<=bl[w];i++) chkmax(mxa,mx[i]);
		for(int i=1;i<=bl[w];i++){
			if(mx[i]==mxa) {
				for(int j=lf[i];j<=rh[i];j++)
					if(buc[j]==mxa) return j;
			}
		}
		return -1;
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++) c[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);build(1,0);
	q=read();
	for(int i=1;i<=q;i++){
		u[i]=read(),v[i]=read(),ordq[i]=i;
		if(pos[u[i]]>pos[v[i]])swap(u[i],v[i]);
	}

	B=tl/sqrtl(q);

	sort(ordq+1,ordq+q+1,[&](int x,int y)->bool{
		int bx = pos[u[x]]/B;
		int by = pos[u[y]]/B;
		if(bx != by) return pos[u[x]] < pos[u[y]];
		else return (bx & 1) ^ (pos[v[x]] < pos[v[y]]);
	});

	DS::init();
	int x=0,y=0;
	for(int i=1;i<=q;i++){
		int o=ordq[i];
		DS::move(pos[u[o]],pos[v[o]]);
		ans[o]=DS::query();
	}
	for(int i=1;i<=q;i++) printf("%d\n", ans[i]);
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