// created time: 2026-06-10 09:11:07
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

int n,k,lf[400005],sz[400005],lvis[400005],mk[400005],p[400005],eid,tid;
int q,uu[500005],vv[500005];
ll val[400005],ans[500005],c[400005];
vector<int>G[400005];
vector<pair<int,int>>E[400005];

int ABS(int x){ return x<0?-x:x; }
void add(int x,int y,int i,ll w){
	E[x].pb(y,i),E[y].pb(x,i),val[i]=w;
}
void build(int x){
	if(G[x].empty())return;
	add(x,G[x][0],++eid,c[G[x][0]]);
	int cur=x;
	for(int i=1;i<G[x].size();i++){
		if(i+1<G[x].size()){
			add(cur,++n,++eid,0);
			add(cur=n,G[x][i],++eid,c[G[x][i]]);
		}else{
			add(cur,G[x][i],++eid,c[G[x][i]]);
		}
	}
	for(int y:G[x]) build(y);
}

int s[400005],ff[400005],col[400005],tl; 
vector<int>qry[400005];
bool dvis[400005];
ll dis[400005];

int mn,mx;
void findcent(int x,int fa,int cc){
	s[++tl]=x,sz[x]=1,col[x]=cc,ff[x]=fa;
	if(lvis[x])chkmin(mn,x),chkmax(mx,x);
	for(auto [y,i]:E[x])if(!mk[i] && i<=tid && i!=fa){
		findcent(y,i,cc);
		sz[x]+=sz[y];
	}
}
void solve(int x){
	if(qry[x].empty()) return;
	tl=0,findcent(x,0,x);
	if(sz[x]==1) return;
	int rt=0,wh=sz[x];
	for(int i=2;i<=tl;i++)
		if(!rt || ABS(2*sz[s[i]]-wh)<ABS(2*sz[rt]-wh)) rt=s[i];
	// cout<<"solving "<<x<<endl;
	// for(int i=1;i<=tl;i++) cout<<s[i]<<" "; cout<<endl;

	// cout<<"rt = "<<rt<<endl;

	mn=n+1,mx=0;
	findcent(rt,ff[rt],rt);

	// for(int i=1;i<=tl;i++) cout<<col[s[i]]<<" "; cout<<endl;

	auto dij = [&](int bg){
		// cout<<"bg = "<<bg<<endl;
		priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>Q;
		for(int i=1;i<=tl;i++) dis[s[i]]=1e18,dvis[s[i]]=0; Q.push({dis[bg]=0,bg});
		while(!Q.empty()){
			int u=Q.top().se;Q.pop();
			if(dvis[u])continue;
			dvis[u]=1;
			for(auto [v,i]: E[u])
				if((col[v]==x||col[v]==rt) && dis[v]>dis[u]+val[i]){
					dis[v]=dis[u]+val[i];
					// cout<<"upd "<<dis[u]<<" + "<<val[i]<<" = "<<dis[v]<<endl;
					Q.push({dis[v],v});
				}
		}
		for(int i: qry[x]){
			// cout<<"upd "<<dis[uu[i]]<<" + "<<dis[vv[i]]<<endl;
			chkmin(ans[i], dis[uu[i]]+dis[vv[i]]);
		}
		for(int i=1;i<=tl;i++) dis[s[i]]=1e18;
	};
	// three edges cut

	dij(rt);
	if(mn<=mx && mn!=rt) dij(mn);
	if(mn<mx && mn!=rt) dij(mx);

	mk[ff[rt]]=1;
	vector<int>ls;
	qry[rt].clear();
	for(int i: qry[x])if(col[uu[i]]==col[vv[i]]){
		if(col[uu[i]]==x) ls.pb(i);
		else qry[rt].pb(i);
	}
	swap(ls,qry[x]);
	solve(x),solve(rt);
}
void procedure(){
	n=read();
	for(int i=2;i<=n;i++){
		p[i]=read(),c[i]=read();
		G[p[i]].pb(i);
	}
	for(int i=1;i<=n;i++)
		if(G[i].empty()) lvis[i]=1,lf[++k]=i;
	build(1);

	// cout<<"built"<<endl;

	tid=eid; // tree edges
	for(int i=1;i<=k;i++)
		add(lf[i],lf[i%k+1],++eid,read());

	q=read();
	for(int i=1;i<=q;i++)
		uu[i]=read(),vv[i]=read(),qry[1].pb(i),ans[i]=1e18;
	
	for(int i=1;i<=n;i++)dis[i]=1e18;
	solve(1);

	for(int i=1;i<=q;i++)printf("%lld\n",ans[i]);
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