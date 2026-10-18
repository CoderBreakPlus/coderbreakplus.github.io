// created time: 2026-10-19 07:14:08
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
template <class T>
struct MCMF {
public:
	MCMF() : n(), dirty() {}
	MCMF(int n) : n((assert(n >= 0), n)), dirty(), ed(n + 1), par(n + 1), dis(n + 1), pi(n + 1) {}

	std::pair<int, int> add(int from, int to, T cap, T cost) {
		assert(1 <= from && from <= n);
		assert(1 <= to && to <= n);
		assert(cap >= 0);
		dirty |= (cap && pi[from] != inf && pi[from] + cost < pi[to]);
		int id = (int)ed[from].size(), rev = (int)ed[to].size() + (from == to);
		ed[from].push_back(edge(to, rev, cap, cost));
		ed[to].push_back(edge(from, id, 0, -cost));
		return {from, id};
	}

	template <class F>
	std::pair<int, int> add_convex(int from, int to, T cap, F cost) {
		assert(cap >= 0);
		auto id = add(from, to, cap, cap ? cost(T(1)) - cost(T(0)) : T(0));
		fun.emplace_back(std::move(cost));
		auto [u, i] = id;
		ed[u][i].fn = (int)fun.size();
		ed[ed[u][i].to][ed[u][i].rev].fn = -(int)fun.size();
		return id;
	}

	std::pair<T, T> max_flow(int s, int t, T lim = inf) {
		assert(1 <= s && s <= n);
		assert(1 <= t && t <= n);
		assert(s != t && lim >= 0);
		setpi(s);
		std::pair<T, T> res = {0, 0};
		while (res.first < lim && path(s, t)) {
			T flw = lim - res.first;
			for (int i = t, j, r; i != s; i = j) {
				r = ed[i][par[i]].rev, j = ed[i][par[i]].to;
				flw = std::min(flw, ed[j][r].cap);
				if (ed[j][r].fn) { flw = std::min(flw, T(1)); }
			}
			res.first += flw, res.second += flw * (pi[t] - pi[s]);
			for (int i = t, j, r; i != s; i = j) {
				r = ed[i][par[i]].rev, j = ed[i][par[i]].to;
				ed[i][par[i]].cap += flw;
				ed[j][r].cap -= flw;
				if (ed[j][r].fn) { update(j, r); }
			}
		}
		return res;
	}

	std::pair<T, T> get_flow(std::pair<int, int> id) {
		auto [u, i] = id;
		assert(1 <= u && u <= n);
		assert(0 <= i && i < (int)ed[u].size());
		edge &e = ed[u][i], &r = ed[e.to][e.rev];
		return {r.cap, e.cap + r.cap};
	}

	void reserve(int u, int m) {
		assert(1 <= u && u <= n && m >= 0);
		ed[u].reserve(m);
	}

private:
	static constexpr T inf = std::numeric_limits<T>::max() / 2;

	struct edge {
		int to, rev, fn;
		T cap, cost;
		edge() {}
		edge(int to, int rev, T cap, T cost) : to(to), rev(rev), fn(), cap(cap), cost(cost) {}
	};

	int n;
	bool dirty;

	std::vector<std::vector<edge>> ed;
	std::vector<int> par;
	std::vector<T> dis, pi;
	std::vector<std::function<T(T)>> fun;

	void update(int u, int i) {
		if (ed[u][i].fn < 0) {
			int v = ed[u][i].to, j = ed[u][i].rev;
			u = v, i = j;
		}
		edge &e = ed[u][i], &r = ed[e.to][e.rev];
		auto& cost = fun[e.fn - 1];
		T f = r.cap, val = cost(f);
		if (e.cap) { e.cost = cost(f + 1) - val; }
		if (r.cap) { r.cost = cost(f - 1) - val; }
	}

	bool path(int s, int t) {
		std::fill(dis.begin(), dis.end(), inf);
		dis[s] = 0;
		std::priority_queue<std::pair<T, int>, std::vector<std::pair<T, int>>, std::greater<std::pair<T, int>>> qu;
		qu.push({dis[s], s});
		while (!qu.empty()) {
			auto [di, u] = qu.top(); qu.pop();
			if (di != dis[u]) { continue; }
			for (edge& e : ed[u]) {
				if (!e.cap) { continue; }
				T val = di + e.cost + pi[u] - pi[e.to];
				if (dis[e.to] > val) {
					dis[e.to] = val;
					par[e.to] = e.rev;
					qu.push({dis[e.to], e.to});
				}
			}
		}
		for (int i = 1; i <= n; ++i) {
			pi[i] = (dis[i] == inf ? inf : pi[i] + dis[i]);
		}
		return dis[t] != inf;
	}

	void setpi(int s) {
		if (!dirty && pi[s] != inf) { return ; }
		dirty = 0;

		std::fill(pi.begin(), pi.end(), inf);
		pi[s] = 0;
		int t = n, flg = 1;
		while (flg-- && t--) {
			for (int i = 1; i <= n; ++i) {
				if (pi[i] != inf) {
					for (auto& e : ed[i]) {
						if (e.cap && pi[e.to] > pi[i] + e.cost) {
							pi[e.to] = pi[i] + e.cost, flg = 1;
						}
					}
				}
			}
		}
		assert(t >= 0);
	}
};

int n,k,a[200005],b[200005];
int mn[2005],mx[2005],val[4005],m;

MCMF<ll>F;
void procedure(){
	n=read(),k=read();
	for(int i=1;i<=k;i++)mx[i]=-2e9,mn[i]=2e9;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		b[i]=read();
		chkmax(mx[a[i]],b[i]);
		chkmin(mn[a[i]],b[i]);
	}
	for(int i=1;i<=k;i++)val[++m]=mn[i],val[++m]=mx[i];
	sort(val+1,val+m+1);m=unique(val+1,val+m+1)-(val+1);

	MCMF<ll>F(m+k+1);
	int S=m+k+1,T=1;
	for(int i=2;i<=m;i++){
		int w=val[i]-val[i-1];
		F.add_convex(i,i-1,1e9,[w=w](ll x){ return w*x*(x-k); });
	}
	for(int i=1;i<=k;i++){
		F.add(S,m+i,1,0);
		mx[i]=lower_bound(val+1,val+m+1,mx[i])-val;
		mn[i]=lower_bound(val+1,val+m+1,mn[i])-val;
		F.add(m+i,mx[i],1,0);
		F.add(m+i,mn[i],1,0);
	}
	printf("%lld\n",-F.max_flow(S,T).se);
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