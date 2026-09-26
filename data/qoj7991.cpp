// created time: 2026-09-24 09:04:52
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
const ll INF=1e18;
int n,m;
ll ans=INF;
map<int,ll>e[300005];
bool vis[300005];

void add(int u,int v){ if(!e[u].count(v)) e[u][v]=INF; }
ll dis[300005];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(); ll w=read();
		if(u==v){
			chkmin(ans,w);
			continue;
		}
		add(u,v),add(v,u);
		chkmin(e[u][v],w);
	}
	queue<int>q;
	for(int i=1;i<=n;i++){
		// cout<<"at "<<i<<" size = "<<e[i].size()<<endl;
		if(e[i].size()<=2) q.push(i);
	}
	while(!q.empty()){
		int x=q.front(); q.pop();
		if(vis[x])continue; vis[x]=1;
		if(e[x].empty())continue;

		// cout<<"fuck node "<<x<<endl;
		if(e[x].size()==1){
			auto [y,v]=*e[x].begin();
			chkmin(ans, v+e[y][x]);
			e[y].erase(x);
			if(e[y].size()<=2) q.push(y);
		}else{
			auto [y1,v1]=*e[x].begin();
			auto [y2,v2]=*e[x].rbegin();
			chkmin(ans,min(e[y1][x]+v1,e[y2][x]+v2));

			add(y1,y2),add(y2,y1);
			chkmin(e[y1][y2],e[y1][x]+v2);
			chkmin(e[y2][y1],e[y2][x]+v1);

			e[y1].erase(x),e[y2].erase(x);
			if(e[y1].size()<=2) q.push(y1);
			if(e[y2].size()<=2) q.push(y2);
		}
	}
	vector<int>node;
	for(int i=1;i<=n;i++)if(!vis[i]){
		node.pb(i);
		// for(auto [j,v]:e[i]){
		// 	cout<<i<<"->"<<j<<" v="<<v<<endl;
		// }
	}

	for(int x: node){
		for(int y: node) dis[y]=INF,vis[y]=0; dis[x]=0;
		priority_queue<pair<ll,int>>q;
		q.push({dis[x],x});

		while(!q.empty()){
			int x=q.top().se;q.pop();
			for(auto [y,v]: e[x]){
				if(dis[y]>dis[x]+v){
					dis[y]=dis[x]+v;
					q.push({-dis[y],y});
				}
			}
		}
		for(int y: node)
			if(e[y].count(x))chkmin(ans, e[y][x]+dis[y]);
	}
	printf("%lld\n", ans<INF?ans:-1);
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