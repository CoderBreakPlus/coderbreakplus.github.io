// created time: 2026-05-22 14:44:06
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

int n,m,c[400005],t[400005],s[400005],tmp[400005],tc;
int u[400005],v[400005],id;

int fa[400005],sz[400005],mx[400005],tp;
int x[400005],y[400005],vx[400005],vy[400005];

int find(int x){
	while(x!=fa[x])x=fa[x];
	return x;
}
void merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return;
	if(sz[x]>sz[y])swap(x,y);
	::x[++tp]=x, ::y[tp]=y, vx[tp]=mx[x], vy[tp]=mx[y];
	fa[x]=y,sz[y]+=sz[x],chkmax(mx[y],mx[x]);
}
void undo(){
	fa[x[tp]]=x[tp],sz[y[tp]]-=sz[x[tp]];
	mx[x[tp]]=vx[tp],mx[y[tp]]=vy[tp]; tp--;
}
void undo(int w){ while(tp>w) undo(); }

vector<pair<int,int>>tr[1600005];
vector<int>vec[400005],E[400005];

int ans[400005];
void ins(int l,int r,int ql,int qr,int u,int v,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){tr[p].pb(u,v);return;}
	int mid=(l+r)>>1;
	ins(l,mid,ql,qr,u,v,p<<1),ins(mid+1,r,ql,qr,u,v,p<<1|1);
}
void solve(int l,int r,int p){
	int bef=tp;
	for(auto [u,v]:tr[p]) merge(u,v);
	if(l==r){
		for(int x:vec[l]){
			ans[x]=mx[find(x)];
			for(auto y:E[x])if(c[x]>c[y]){
				++id; fa[id]=id, sz[id]=1, mx[id]=ans[x];
				ins(1,tc,1,c[x]-1,y,id,1);
			}
		}
	}else{
		int mid=(l+r)>>1;
		solve(mid+1,r,p<<1|1),solve(l,mid,p<<1);
	}
	undo(bef);
}
void procedure(){
	n=id=read(),m=read();
	for(int i=1;i<=n;i++){
		c[i]=read(),t[i]=read(),mx[i]=s[i]=read(),fa[i]=i,sz[i]=1;
		tmp[++tc]=c[i];
	}
	sort(tmp+1,tmp+tc+1);tc=unique(tmp+1,tmp+tc+1)-(tmp+1);
	for(int i=1;i<=n;i++){
		t[i]=upper_bound(tmp+1,tmp+tc+1,t[i])-(tmp+1);
		c[i]=upper_bound(tmp+1,tmp+tc+1,c[i])-(tmp+1);
		vec[c[i]].pb(i);
	}

	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		if(c[u]>c[v])swap(u,v);
		E[u].pb(v),E[v].pb(u);
		ins(1,tc,max(c[u],c[v]),min(t[u],t[v]),u,v,1);
	}

	solve(1,tc,1);
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);puts("");
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