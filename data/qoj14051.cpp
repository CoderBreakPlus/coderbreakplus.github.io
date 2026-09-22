// created time: 2026-09-22 08:05:11
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

int n,m;
namespace DS{
	struct LCT {
		int n, m;
		vector<int> fa, ch[2], val, min_id, tag;
		LCT(int n, int m) : n(n), m(m) {
			int tot = n + m;
			fa.assign(tot + 1, 0);
			ch[0].assign(tot + 1, 0);
			ch[1].assign(tot + 1, 0);
			val.assign(tot + 1, 0);
			min_id.assign(tot + 1, 0);
			tag.assign(tot + 1, 0);
			for (int i = 1; i <= n; ++i) {
				val[i] = 1e9;
				min_id[i] = i;
			}
			for (int i = 1; i <= m; ++i) {
				val[n + i] = i;
				min_id[n + i] = n + i;
			}
		}
		void init_val(int m, pair<int, int> *edge) {
			for (int i = 1; i <= m; ++i) {
				val[n + i] = edge[i].second;
				min_id[n + i] = n + i;
			}
		}

		bool is_root(int x) {
			return ch[0][fa[x]] != x && ch[1][fa[x]] != x;
		}

		void pushup(int x) {
			min_id[x] = x;
			if (ch[0][x] && val[min_id[ch[0][x]]] < val[min_id[x]]) {
				min_id[x] = min_id[ch[0][x]];
			}
			if (ch[1][x] && val[min_id[ch[1][x]]] < val[min_id[x]]) {
				min_id[x] = min_id[ch[1][x]];
			}
		}

		void pushdown(int x) {
			if (tag[x]) {
				if (ch[0][x]) {
					swap(ch[0][ch[0][x]], ch[1][ch[0][x]]);
					tag[ch[0][x]] ^= 1;
				}
				if (ch[1][x]) {
					swap(ch[0][ch[1][x]], ch[1][ch[1][x]]);
					tag[ch[1][x]] ^= 1;
				}
				tag[x] = 0;
			}
		}

		void update(int x) {
			if (!is_root(x)) update(fa[x]);
			pushdown(x);
		}

		void rotate(int x) {
			int y = fa[x], z = fa[y];
			int k = (ch[1][y] == x);
			if (!is_root(y)) ch[ch[1][z] == y][z] = x;
			fa[x] = z;
			ch[k][y] = ch[k ^ 1][x];
			if (ch[k ^ 1][x]) fa[ch[k ^ 1][x]] = y;
			ch[k ^ 1][x] = y;
			fa[y] = x;
			pushup(y);
			pushup(x);
		}

		void splay(int x) {
			update(x);
			while (!is_root(x)) {
				int y = fa[x], z = fa[y];
				if (!is_root(y)) {
					if ((ch[1][y] == x) ^ (ch[1][z] == y)) rotate(x);
					else rotate(y);
				}
				rotate(x);
			}
		}

		void access(int x) {
			for (int t = 0; x; t = x, x = fa[x]) {
				splay(x);
				ch[1][x] = t;
				pushup(x);
			}
		}

		void make_root(int x) {
			access(x);
			splay(x);
			swap(ch[0][x], ch[1][x]);
			tag[x] ^= 1;
		}

		int find_root(int x) {
			access(x);
			splay(x);
			while (ch[0][x]) {
				pushdown(x);
				x = ch[0][x];
			}
			splay(x);
			return x;
		}

		void split(int x, int y) {
			make_root(x);
			access(y);
			splay(y);
		}

		void link(int x, int y) {
			make_root(x);
			if (find_root(y) != x) fa[x] = y;
		}

		void cut(int x, int y) {
			make_root(x);
			if (find_root(y) == x && fa[y] == x && !ch[0][y]) {
				fa[y] = ch[1][x] = 0;
				pushup(x);
			}
		}
	};
	void solve(int n, int m, int *ans, pair<int, int> *edge) {
		for (int i = 1; i <= m; ++i)
			ans[i] = m+1;

		LCT lct(n, m);
		lct.init_val(m, edge);

		for (int i = 1; i <= m; ++i) {
			int u = edge[i].first;
			int v = edge[i].second;

			if (u == v) {
				ans[i] = i;
				continue;
			}

			if (lct.find_root(u) == lct.find_root(v)) {
				lct.split(u, v);
				int min_edge_node = lct.min_id[v];
				int del_id = min_edge_node - n;

				// 比较树上最小边与当前边的较小端点
				if (edge[i].second > edge[del_id].second) {
					ans[del_id] = i;
					int du = edge[del_id].first;
					int dv = edge[del_id].second;
					lct.cut(du, min_edge_node);
					lct.cut(dv, min_edge_node);

					int e_node = n + i;
					lct.link(u, e_node);
					lct.link(v, e_node);
				} else {
					ans[i] = i; // 当前边是最劣边，自身直接淘汰
				}
			} else {
				int e_node = n + i;
				lct.link(u, e_node);
				lct.link(v, e_node);
			}
		}
	}
}
pair<int,int> e[200005];
int to[200005],f[200005],prv[200005];
vector<int> add[200005],del[200005];

struct Seg{
	int mn[800005],tag[800005];
	pair<int,int> val[800005];

	#define mid ((l+r)>>1)
	void upd(int p,int w){
		mn[p]+=w,tag[p]+=w;
	}
	void pushdown(int p){
		upd(p<<1,tag[p]),upd(p<<1|1,tag[p]);
		tag[p]=0;
	}
	void pushup(int p){
		mn[p]=mn[p<<1],val[p]=val[p<<1];
		if(mn[p<<1|1]<mn[p]){
			mn[p]=mn[p<<1|1];
			val[p]=val[p<<1|1];
		}else if(mn[p<<1|1]==mn[p])
			chkmin(val[p],val[p<<1|1]);
	}
	void build(int l,int r,int p){
		if(l==r){ mn[p]=1e9,val[p]={1e9,l}; return; }
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		pushup(p);
	}
	void modify(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l) return;
		if(ql<=l&&r<=qr){ upd(p,v); return; }
		pushdown(p);
		modify(l,mid,ql,qr,v,p<<1),modify(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
	void update(int l,int r,int x,int v,int p){
		if(l==r){
			mn[p]=0,val[p]={v,l};
			return;
		}
		pushdown(p);
		if(x<=mid)update(l,mid,x,v,p<<1);
		else update(mid+1,r,x,v,p<<1|1);
		pushup(p);
	}
}S;
void procedure(){
	n=read(),m=read();	
	for(int i=1;i<=m;i++){
		e[i].fi=read()+1,e[i].se=read()+1;
		if(e[i].fi<e[i].se)swap(e[i].fi,e[i].se);
	}
	e[m+1]={n+1,0};
	sort(e+1,e+m+1);
	DS::solve(n,m,to,e);

	for(int i=1;i<=m;i++){
		add[e[i].fi].pb(i);
		del[e[to[i]].fi].pb(i);
	}
	S.build(0,n,1);
	for(int i=0;i<=n;i++){
		for(int x: add[i]) S.modify(0,n,0,e[x].se-1,-1,1);
		for(int x: del[i]) S.modify(0,n,0,e[x].se-1,1,1);

		if(!i){
			f[i]=0;
		}else{
			auto [x,y]=S.val[1];
			f[i]=x+1,prv[i]=y;
		}

		S.update(0,n,i,f[i],1);
		S.modify(0,n,0,i,1,1);
	}
	printf("%d\n",f[n]);
	vector<int>ans;
	while(n) ans.pb(n-prv[n]),n=prv[n];
	reverse(ans.begin(),ans.end());

	for(int x: ans) printf("%d ",x); puts("");
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