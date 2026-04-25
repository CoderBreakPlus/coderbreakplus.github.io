// created time: 2026-04-25
#include<bits/stdc++.h>
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
inline ull read(){
	ull x=0, f=1; int ch=getchar();
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }
ull a[200005];

int n,m,B,vis[200005],dfn[200005],sz[200005],tim,fa[200005],fa2[200005];
int x[200005],y[200005],z1[200005],z2[200005],jp[200005];
ull val[200005],ex1[200005],ex[200005];

int seq[200005],tl;
ull ans[200005];

vector<int>E[200005],G[200005],H[200005];
vector<pair<int,int>>tmp1,tmp2;

struct sbLCA{
	vector<int>* E;
	int dfn[200005],tim,f[20][200005];
	void dfs(int x,int fa){
		f[0][dfn[x]=++tim]=fa;
		for(auto y:E[x]){
			if(y==fa)continue;
			dfs(y,x);
		}
	}
	int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
	void init(){
		dfs(1,0);
		for(int i=1;(1<<i)<=n;i++)
			for(int j=1;j<=n-(1<<i)+1;j++)
				f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
	}
	int LCA(int x,int y){
		if(x==y)return x;
		if((x=dfn[x])>(y=dfn[y]))swap(x,y);
		int p=lg2(y-x++);
		return get(f[p][x],f[p][y-(1<<p)+1]);
	}
}T1,T2;

void getdfn(int x,int fa){
	dfn[x]=(++tim);
	for(auto y:G[x]){
		if(y==fa)continue;
		getdfn(y,x);
	}
}
void dfs1(int x,int f){
	fa[x]=f;
	for(auto y:E[x]){
		if(y==f) continue;
		dfs1(y,x);
	}
}
void dfs2(int x){
	sz[x]=1;
	for(auto y:H[x])
		dfs2(y),sz[x]+=sz[y];
}
int findnode(int x,int fa){
	int mx=0;
	for(auto y:E[x]){
		if(y==fa)continue;
		mx=max(findnode(y,x),mx);
	}
	mx++;
	if(mx>=B||x==1) {
		seq[++tl]=x;
		return 0;
	}
	return mx;
}
struct Extra{
	ull tag1[200005],tag2[200005];
	int bl[200005],lf[200005],rh[200005];
	void init(){
		for(int i=0;i<=n+1;i++)bl[i]=(i-1)/B+1,rh[bl[i]]=i;
		for(int i=n+1;i>=0;i--)lf[bl[i]]=i;
	}
	void upd(int l,int r,ull v){
		if(bl[l]<bl[r]){
			tag1[bl[l]+1]+=v,tag1[bl[r]]-=v;
			tag2[l]+=v;
			tag2[lf[bl[r]]]+=v,tag2[r]-=v;
		}else{
			tag2[l]+=v,tag2[r]-=v;
		}
	}
	ull qry(int x){
		ull ret=0;
		for(int i=1;i<=bl[x];i++)ret+=tag1[i];
		for(int i=lf[bl[x]];i<=x;i++)ret+=tag2[i];
		return ret;
	}
}Ex;

void procedure(){
	n=read(),m=read(),B=sqrt(n)*0.8;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		tmp1.pb(u,v);
	}
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		tmp2.pb(u,v);
		G[u].pb(v),G[v].pb(u);
	}
	Ex.init();
	getdfn(1,0);
	for(auto [x,y]: tmp1){
		x=dfn[x],y=dfn[y];
		E[x].pb(y),E[y].pb(x);
	}
	for(auto [x,y]: tmp2){
		x=dfn[x],y=dfn[y];if(x>y)swap(x,y);
		H[x].pb(y);fa2[y]=x;
	}

	dfs1(1,0);
	dfs2(1);
	T1.E=E,T2.E=H;
	T1.init(),T2.init();
	// 预处理两棵树

	auto mdf_point = [&](int x,ull v){
		Ex.upd(x,x+sz[x],v);
		ex[x]+=v;
	};

	for(int i=1;i<=n;i++) mdf_point(dfn[i],a[i]);

	findnode(1,0);
	
	for(int i=1;i<=tl;i++) vis[seq[i]]=1;
	for(int i=1;i<=n;i++){
		jp[i]=i;
		while(!vis[jp[i]]){
			jp[i]=fa[jp[i]];
		}
	}
	for(int i=1;i<=m;i++){
		x[i]=dfn[read()],y[i]=dfn[read()],val[i]=read();
		z1[i]=T1.LCA(x[i],y[i]);
		z2[i]=T2.LCA(x[i],y[i]);
	}
	auto upd = [&](int x,ull v){
		while(x!=jp[x]){
			mdf_point(x,v),x=fa[x];
		}
	};
	auto upd2 = [&](int x,ull v){
		mdf_point(x,v),x=fa[x],v*=2;
		while(x!=jp[x]){
			mdf_point(x,v),x=fa[x];
		}
	};
	auto qry = [&](int x){
		return Ex.qry(x);
	};
	for(int i=1;i<=m;i++){
		upd(x[i],val[i]),upd(y[i],val[i]);
		if(jp[z1[i]]==z1[i]){
			upd(fa[z1[i]],-val[i]);
		}else{
			upd2(z1[i],-val[i]);
		}
		ans[i]+=qry(x[i])+qry(y[i])-2*qry(z2[i])+ex[z2[i]];
	}
	for(int w=1;w<=tl;w++){
		memset(vis,0,sizeof(vis));
		int u=seq[w];
		int cur=u;while(cur)vis[cur]=1,cur=fa[cur];
		for(int i=2;i<=n;i++)vis[i]+=vis[fa2[i]];

		ull tag=0;
		for(int i=1;i<=m;i++){
			if(jp[x[i]]==u)tag+=val[i];
			if(jp[y[i]]==u)tag+=val[i];
			if(jp[z1[i]]==u)tag-=val[i];
			if(jp[fa[z1[i]]]==u)tag-=val[i];
			ans[i]+=(vis[x[i]]+vis[y[i]]-vis[z2[i]]-vis[fa2[z2[i]]])*tag;
		}
	}
	for(int i=1;i<=m;i++)
		printf("%llu\n",ans[i]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}