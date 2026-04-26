// created time: 2026-04-26 19:03:50
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
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,m,q,u[300005],v[300005],ww[300005],fa[300005],c[300005],sz[300005],vis[300005];
vector<int>tr[1200005];

int sx[300005],sy[300005],cx[300005],cy[300005],tp;

int find(int x){ return x==fa[x]?x:find(fa[x]); }
ll ans=0;
struct DSU{
	int fa[300005];
	void init(){
		for(int i=1;i<=n;i++)fa[i]=i;
	}
	int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
	void merge(int x,int y,int w){
		if(!x||!y)return;x=find(x),y=find(y);
		if(x^y){
			// cout<<"merge "<<x<<","<<y<<" w="<<w<<endl;
			fa[x]=y,ans+=w;
		}
	}
}d;

void modify(int l,int r,int ql,int qr,int i,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){
		tr[p].pb(i);
		return;
	}
	int mid=(l+r)>>1;modify(l,mid,ql,qr,i,p<<1),modify(mid+1,r,ql,qr,i,p<<1|1);
}
void merge(int x,int y,int w){
	x=find(x),y=find(y);
	if(x==y)return;
	if(sz[x]>sz[y])swap(x,y);
	// cout<<"add edge "<<x<<","<<y<<" w="<<w<<endl;

	sx[++tp]=x,sy[tp]=y;
	cx[tp]=c[x],cy[tp]=c[y];
	d.merge(c[x],c[y],w);
	c[y]=max(c[x],c[y]),sz[y]+=sz[x],fa[x]=y;
}
void undo(){
	// cout<<"delete edge "<<sx[tp]<<","<<sy[tp]<<endl;
	c[sx[tp]]=cx[tp],c[sy[tp]]=cy[tp];
	sz[sy[tp]]-=sz[sx[tp]]; fa[sx[tp]]=sx[tp];
	tp--;
}
void undo(int x){while(tp>x)undo();}
void solve(int l,int r,int p){
	int ok=tp;
	// cout<<"at "<<l<<"->"<<r<<endl;
	for(auto i:tr[p]){
		merge(u[i],v[i],l);
	}
	int mid=(l+r)>>1;
	if(l<r)solve(l,mid,p<<1),solve(mid+1,r,p<<1|1);
	undo(ok);
}
void procedure(){
	ans=tp=0;
	n=read(),m=read(),q=read();
	for(int i=1;i<=((m+1)<<2);i++)tr[i].clear();
	for(int i=1;i<=n;i++)vis[i]=0;

	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read(),ww[i]=read();
		modify(0,m,0,ww[i]-1,i,1);
		modify(0,m,ww[i]+1,m,i,1);
	}
	int rt;
	for(int i=1;i<=q;i++)vis[rt=read()]=1;
	for(int i=1;i<=n;i++){
		fa[i]=i,sz[i]=1;
		if(vis[i])c[i]=i;
		else c[i]=0;
	}
	d.init();
	solve(0,m,1);

	for(int i=1;i<=n;i++)
		if(vis[i] && d.find(i)!=d.find(rt)){
			puts("-1");
			return;
		}
	printf("%lld\n",ans);
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