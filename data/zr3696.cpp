// created time: 2026-11-10 09:10:14
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

const int N=500005;
int n,q,a[N],fa[N],zero[N];
vector<int>E[N];
pair<ll,int>f[N],g[N];

int val(int x){ return zero[x]?0:f[x].se; }
int factor(int y){
	int v=val(y)+(f[y].fi==0);
	addmod(v);return v;
}
void link(int x,int y){
	if(f[y].fi<0) return;
	f[x].fi+=f[y].fi;
	int v=factor(y);
	if(v==0) ++zero[x];
	else f[x].se=(ull)f[x].se*v%mod;
}
void cut(int x,int y){
	if(f[y].fi<0) return;
	f[x].fi-=f[y].fi;
	int v=factor(y);
	if(v==0) --zero[x];
	else if(v!=1) f[x].se=(ull)f[x].se*INV(v)%mod;
}
void dfs(int x,int fa){
	f[x]={a[x],1}; ::fa[x]=fa;
	for(int y:E[x])if(y!=fa){
		dfs(y,x);
		link(x,y);
	}
}
void dfs2(int x){
	for(int y:E[x])if(y!=fa[x])cut(x,y);
	g[x]={f[x].fi,val(x)};
	for(int y:E[x])if(y!=fa[x])link(x,y);
	for(int y:E[x])if(y!=fa[x]){
		cut(x,y),link(y,x);
		dfs2(y);
		cut(y,x),link(x,y);
	}
}
int m,lsh[N],tot;
struct Node{
	ll b;
	int k,lc,rc,val;
}t[N*20];
#define mid ((l+r)>>1)
void pushup(int p){
	t[p].b=t[t[p].lc].b+t[t[p].rc].b;
	t[p].k=t[t[p].lc].k+t[t[p].rc].k;
}
int merge(int p,int q,int l,int r){
	if(!p||!q) return p|q;
	if(l==r){
		t[p].b+=t[q].b;
		t[p].k+=t[q].k;
		t[p].val=(ull)t[p].val*t[q].val%mod;
	}else{
		t[p].lc=merge(t[p].lc,t[q].lc,l,mid);
		t[p].rc=merge(t[p].rc,t[q].rc,mid+1,r);
		pushup(p);
	}
	return p;
}
int getval(int p,int pos){
	int l=1,r=m;
	while(p && l<r){
		if(pos<=mid) p=t[p].lc,r=mid;
		else p=t[p].rc,l=mid+1;
	}
	return t[p].val;
}
int solve(int p,int l,int r,ll b,int k){
	if(!p){
		p=++tot;
		t[p].val=1;
	}
	if(l==r){
		t[p].b+=b,t[p].k+=k;
		ll val=t[p].b+(ll)t[p].k*lsh[l];
		if(val<0) return 0;
		else if(val==0) addmod(t[p].val+=1);
		return p;
	}
	ll mb=b+t[t[p].lc].b;
	int mk=k+t[t[p].lc].k;
	if(mb+(ll)mk*lsh[mid]>=0) t[p].lc=solve(t[p].lc,l,mid,b,k);
	else{
		t[p].lc=0;
		t[p].rc=solve(t[p].rc,mid+1,r,mb,mk);
	}
	pushup(p);
	return p;
}
vector<pair<int,int>> qry[N];
int ans[N];
int dfs3(int x){
	int rt=0;
	for(int y:E[x])if(y!=fa[x])
		rt=merge(rt,dfs3(y),1,m);
	for(auto [w,id]:qry[x]){
		int pos=lower_bound(lsh+1,lsh+m+1,w)-lsh;
		ans[id]=(ull)g[x].se*getval(rt,pos)%mod;
	}
	return solve(rt,1,m,a[x],1);
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	dfs2(1);

	for(int i=1;i<=q;i++){
		int u=read(),x=read();
		qry[u].pb(x,i);
		lsh[i]=x;
	}
	sort(lsh+1,lsh+q+1);
	m=unique(lsh+1,lsh+q+1)-lsh-1;

	t[0].val=1;
	dfs3(1);
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
}
int main(){
	assert(freopen("subsidy.in","r",stdin));
	assert(freopen("subsidy.out","w",stdout));
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}
