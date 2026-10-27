// created time: 2026-10-27 08:27:21
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
const int INF=1e9;
int n,a[500005],fa[500005],dep[500005];
vector<int>buc[500005],E[500005];
void dfs(int x,int fa){
	::fa[x]=fa,dep[x]=dep[fa]+1;
	for(int y:E[x]) if(y!=fa)dfs(y,x);
}
bool vis[500005],in[500005];
#define mid ((l+r)>>1)
int tag[2000005],ans[500005];
void upd(int p,int l,int r,int v){
	chkmin(tag[p],v);
	if(l==r&&vis[l]){
		chkmin(ans[l],v);
	}
}
void pushdown(int p,int l,int r){
	upd(p<<1,l,mid,tag[p]),upd(p<<1|1,mid+1,r,tag[p]);
	tag[p]=INF;
}
void build(int l,int r,int p){
	tag[p]=INF;
	if(l==r)return;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
}
void modify(int l,int r,int x,int p){
	if(l==r) return;
	pushdown(p,l,r);
	if(x<=mid) modify(l,mid,x,p<<1);
	else modify(mid+1,r,x,p<<1|1);
}
void release(int l,int r,int p){
	if(l==r) return;
	pushdown(p,l,r);
	release(l,mid,p<<1),release(mid+1,r,p<<1|1);
}
void change(int x){
	modify(1,n,x,1);
	vis[x]^=1;
}

int out;
void solve(int x,int val){
	chkmin(val,dep[x]+ans[x]-1);
	out+=(dep[x]<=val);
	for(int y:E[x])if(y!=fa[x])
		solve(y,val);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)buc[i].clear(),E[i].clear(),vis[i]=in[i]=0,ans[i]=INF;
	build(1,n,1);
	int rt=1;
	for(int i=1;i<=n;i++)a[i]=read(),buc[a[i]].pb(i);
	for(int i=2;i<=n;i++)
		if(a[i]<a[rt])rt=i;
	// cout<<"READ"<<endl;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(rt,0);
	in[rt]=1;
	for(int y:E[rt])change(y);

	int sz=1;
	for(int v=a[rt];v<=n;v++){
		// cout<<"v="<<v<<endl;
		for(int x:buc[v]){
			while(!in[x]){
				in[x]=1,sz++;
				// cout<<"ins node "<<x<<endl;
				for(int y:E[x])if(y!=fa[x])change(y);
				change(x),x=fa[x];
			}
		}
		if(sz>v){
			puts("0");
			return;
		}
		// for(int i=1;i<=n;i++)if(vis[i]) cout<<i<<","; cout<<endl;
		// cout<<"upd for "<<v-sz<<endl;
		upd(1,1,n,v-sz);
	}
	release(1,n,1);
	// for(int i=1;i<=n;i++)cout<<ans[i]<<" ";cout<<endl;
	out=0;
	solve(rt,INF);
	printf("%d\n",out);
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