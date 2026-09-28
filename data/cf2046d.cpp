// created time: 2026-09-28 08:59:02
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

template <typename T_flow = long long, typename T_cost = long long>
struct BoundMCMF {
    static constexpr T_flow INF_FLOW = numeric_limits<T_flow>::max() / 2;
    static constexpr T_cost INF_COST = numeric_limits<T_cost>::max() / 2;

    struct Edge {
        int to;
        T_flow cap, flow;
        T_cost cost;
        int nxt;
    };

    int n;
    vector<Edge> e;
    vector<int> head;
    
    vector<T_flow> deg;
    T_cost base_cost;

    vector<T_cost> dis;
    vector<int> pre_v, pre_e;
    vector<bool> inq;

    BoundMCMF(int N) {
        n = N;
        int max_nodes = n + 3;
        head.assign(max_nodes, -1);
        deg.assign(max_nodes, 0);
        base_cost = 0;
        
        dis.resize(max_nodes);
        pre_v.resize(max_nodes);
        pre_e.resize(max_nodes);
        inq.resize(max_nodes);
    }
    void add_edge(int u, int v, T_flow cap, T_cost cost) {
        e.push_back({v, cap, 0, cost, head[u]});
        head[u] = (int)e.size() - 1;
        e.push_back({u, 0, 0, -cost, head[v]});
        head[v] = (int)e.size() - 1;
    }
    void add_bound_edge(int u, int v, T_flow L, T_flow R, T_cost cost) {
        base_cost += L * cost;
        deg[u] -= L;
        deg[v] += L;
        add_edge(u, v, R - L, cost);
    }
    bool spfa(int s, int t) {
        fill(dis.begin(), dis.end(), INF_COST);
        fill(inq.begin(), inq.end(), false);
        queue<int> q;
        dis[s] = 0;
        q.push(s);
        inq[s] = true;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            inq[u] = false;
            for (int i = head[u]; i != -1; i = e[i].nxt) {
                int v = e[i].to;
                if (e[i].cap > e[i].flow && dis[v] > dis[u] + e[i].cost) {
                    dis[v] = dis[u] + e[i].cost;
                    pre_v[v] = u;
                    pre_e[v] = i;
                    if (!inq[v]) {
                        q.push(v);
                        inq[v] = true;
                    }
                }
            }
        }
        return dis[t] != INF_COST;
    }
    pair<bool, T_cost> solve(int S, int T) {
        add_edge(T, S, INF_FLOW, 0);
        int SS = n + 1;
        int TT = n + 2;
        T_flow sum_req = 0;
        for (int i = 1; i <= n; i++) {
            if (deg[i] > 0) {
                add_edge(SS, i, deg[i], 0);
                sum_req += deg[i];
            } else if (deg[i] < 0) {
                add_edge(i, TT, -deg[i], 0);
            }
        }
        T_flow total_flow = 0;
        T_cost total_cost = 0;
        while (spfa(SS, TT)) {
            T_flow push = INF_FLOW;
            for (int u = TT; u != SS; u = pre_v[u]) {
                int p = pre_e[u];
                push = min(push, e[p].cap - e[p].flow);
            }
            for (int u = TT; u != SS; u = pre_v[u]) {
                int p = pre_e[u];
                e[p].flow += push;
                e[p ^ 1].flow -= push;
                total_cost += push * e[p].cost;
            }
            total_flow += push;
        }
        if (total_flow != sum_req) {
            return {false, -1};
        }
        return {true, base_cost + total_cost};
    }
};

int n,m,a[205],u[805],v[805],bel[205];
bool vis[205][205];
vector<int>E[205];

void dfs(int x,int s){
	if(vis[s][x])return;
	vis[s][x]=1;
	for(int y:E[x])
		dfs(y,s);
}
int S,T,now,u_in[205],u_out[205],u_0[205];
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read(),E[i].clear(),bel[i]=i,memset(vis[i],0,sizeof(vis[i]));
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();
		E[u[i]].pb(v[i]);
	}
	for(int i=1;i<=n;i++)
		dfs(i,i);

	for(int i=1;i<=n;i++)if(bel[i]==i){
		u_in[i]=++now,u_out[i]=++now,u_0[i]=++now;
		for(int j=i+1;j<=n;j++)if(vis[i][j]&&vis[j][i])
			bel[j]=i,a[i]+=a[j];
	}
	BoundMCMF<int,int>flow(now);
	for(int i=1;i<=n;i++)if(bel[i]==i){
		flow.add_edge(S,u_0[i],a[i],0);
		flow.add_edge(u_out[i],T,flow.INF_FLOW,0);
		flow.add_bound_edge(u_in[i],u_out[i],1,flow.INF_FLOW,0);
		flow.add_edge(u_0[i],u_in[i],1,1);
		flow.add_edge(u_0[i],u_out[i],flow.INF_FLOW,0);
	}

	for(int i=1,x,y;i<=m;i++){
		if((x=bel[u[i]])==(y=bel[v[i]]))continue;
		flow.add_edge(u_out[x],u_in[y],flow.INF_FLOW,0);
	}
	auto [x,y]=flow.solve(S,T);
	printf("%d\n",x?y:-1);
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