// created time: 2026-08-19 07:43:19
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

int n,k,dfn[500005],out[500005],seq[500005],sz[500005],fa[500005],val[500005],son[500005],idx;
int sid[500005];
vector<pair<int,int>>E[500005];

void repre(int x,int fa){
	::fa[x]=fa;
	vector<pair<int,int>>G;
	for(auto [y,w]:E[x]){
		if(y==fa)continue;
		repre(y,x);
		G.pb(y,w);
	}
	sort(G.begin(),G.end(),[](pair<int,int> A,pair<int,int> B){ return A.se<B.se; });
	swap(E[x],G);

	for(int i=0;i<E[x].size();i++)
		sid[E[x][i].fi]=i;
}
void dfs(int x){
	if(E[x].size()==0)
		sz[x]=1,dfn[x]=++idx,seq[idx]=x;
	else
		dfn[x]=idx+1;
	for(auto [y,w]:E[x]){
		val[y]=w,dfs(y);
		sz[x]+=sz[y];
	}
	out[x]=idx;
}

ll t[2000005],tag[2000005]; int id[2000005];
void upd(int p,ll w){
	t[p]+=w,tag[p]+=w;
}
void pushdown(int p){
	if(tag[p]){
		upd(p<<1,tag[p]);
		upd(p<<1|1,tag[p]);
		tag[p]=0;
	}
}
void pushup(int p){
	if(t[p<<1]>t[p<<1|1]) t[p]=t[p<<1],id[p]=id[p<<1];
	else t[p]=t[p<<1|1],id[p]=id[p<<1|1];
}
void build(int l,int r,int p){
	if(l==r){
		id[p]=l;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
}
void update(int l,int r,int ql,int qr,ll v,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){ upd(p,v); return; }
	int mid=(l+r)>>1;pushdown(p);
	update(l,mid,ql,qr,v,p<<1);update(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
void upd(int l,int r,int v){
	update(1,idx,l,r,v,1);
}
bool link(int v){
	int u=fa[v];
	if(son[u]){
		if(val[v] > val[son[u]]){		
			upd(dfn[son[u]],out[u],val[son[u]]);
			// 还原
			for(int x=sid[son[u]];x<sid[v];x++){
				auto [y,w]=E[u][x];
				upd(dfn[y],out[y],-w);
			}
			// 清空
			upd(dfn[v],out[u],-val[v]);
			// 加上
			son[u]=v;
		}
		return 0;
	}
	for(int x=0;x<sid[v];x++){
		auto [y,w]=E[u][x];
		upd(dfn[y],out[y],-w);
	}
	upd(dfn[v],out[u],-val[v]);
	son[u]=v; return 1;
}
void procedure(){
	n=read(),k=read();
	ll sum=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		E[u].pb(v,w),E[v].pb(u,w);
		sum+=w;
	}
	repre(1,0);dfs(1);
	build(1,idx,1);
	for(int i=2;i<=n;i++){
		update(1,idx,dfn[i],out[i],val[i],1);
	}

	ll ans=0;
	while(k--){
		if(t[1]>=0){
			ans+=t[1];
			int x=seq[id[1]];
			while(x>1&&link(x)) x=fa[x];
		}
		printf("%lld\n",2*sum-ans);
	}
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