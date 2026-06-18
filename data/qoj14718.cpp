// created time: 2026-06-18 10:58:30
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

int n,m,k,a[300005],vis[300005];
ll d1[300005],ans[300005];
pair<ll,int> dis[300005];
vector<pair<int,int>>E[300005];


void procedure(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<=k;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read()*2;
		E[u].pb(v,w),E[v].pb(u,w);
	}
	ll mx=0;
	{
		for(int i=1;i<=n;i++)vis[i]=0,d1[i]=1e18;
		priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>q;
		q.push({0,1}); d1[1]=0;
		while(!q.empty()){
			int x=q.top().se; q.pop();
			if(vis[x])continue; vis[x]=1;
			for(auto [y,w]:E[x])
				if(d1[y]>d1[x]+w){
					d1[y]=d1[x]+w;
					q.push({d1[y],y});
				}
		}
		for(int i=1;i<=k;i++)chkmax(mx,d1[a[i]]);
	}

	// for(int i=1;i<=n;i++)cout<<d1[i]<<" ";cout<<endl;

	{
		for(int i=1;i<=n;i++)vis[i]=0,dis[i]={1e18,0};
		priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>q;

		for(int i=1;i<=k;i++)dis[a[i]]={0,i},q.push({dis[a[i]].fi,a[i]});
		while(!q.empty()){
			int x=q.top().se; q.pop();
			if(vis[x])continue; vis[x]=1;
			for(auto [y,w]:E[x])
				if(dis[y].fi>dis[x].fi+w){
					dis[y]=dis[x]; dis[y].fi+=w;
					q.push({dis[y].fi,y});
				}
		}
	}
	// cout<<"mx="<<mx<<endl;
	for(int i=1;i<=n;i++) ans[i]=1e18;
	for(int u=1;u<=n;u++)
		for(auto [v,w]: E[u])
		if(dis[u].se!=dis[v].se&&min(dis[u].fi+w+d1[v],dis[v].fi+w+d1[u])<=mx){
			chkmin(ans[dis[u].se],(dis[u].fi+w+dis[v].fi)/2);
			// cout<<"edge "<<u<<" "<<v<<" "<<w<<" have "<<dis[u].se<<" "<<dis[v].se<<endl;
			// cout<<"val="<<(dis[u].fi+w+dis[v].fi)/2<<endl;
		}

	for(int i=1;i<=k;i++){
		// cout<<"at "<<i<<" ans = "<<ans[i]<<endl;
		ans[i]=mx-ans[i];
		if(ans[i]&1) printf("%lld.5 ",ans[i]/2);
		else printf("%lld.0 ",ans[i]/2);
	}

	puts("");
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