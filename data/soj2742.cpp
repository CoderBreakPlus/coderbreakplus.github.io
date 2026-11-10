// created time: 2026-11-10 15:21:01
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
const int M=200005;
const ull INF=1e18;
int n,q; ll a[M];
struct Num{
	ll val;
	int cnt,k;
	void upd(ll w){ val+=k*w; }
	ll calc(ll w){ return val+k*w; }
	Num(){ val=k=0; cnt=1; }
	Num(ll a,int b,int c){ val=a,cnt=b,k=c; }
};
inline Num operator+(const Num &A, const Num &B){
	return Num(A.val+B.val,(ull)A.cnt*B.cnt%mod,A.k+B.k);
}
inline Num getmax(const Num &A,const Num &B){
	if(A.val>B.val) return A;
	if(A.val<B.val) return B;
	Num C=A; C.k=max(A.k,B.k); addmod(C.cnt+=B.cnt);
	return C;
}
Num upd(const Num &A,const Num &B,ll &tim){
	int dk=B.k-A.k;
	if(B.val<=A.val&&dk>0){
		ll dv=A.val-B.val;
		chkmin(tim,dv?(dv+dk-1)/dk:1);
	}
	return getmax(A,B);
}

struct Tree{
	Num sum,pre;
}t[M];
int lc[M],rc[M],fa[M],op[M],L[M],R[M],id;
bool vis[M];
ll tim[M],tag[M];

int ff[M],sz[M],son[M],atom[M],ti;

vector<int>E[M];
void dfs(int x,int f){
	ff[x]=f,sz[x]=1;
	for(int y:E[x])if(y!=f){
		if(y==f)continue;
		dfs(y,x);
		sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
}
void pushup(int p){
	int l=lc[p],r=rc[p];
	tim[p]=min(tim[l],tim[r]);
	if(op[p]){
		t[p].sum=t[l].sum+t[r].sum;
		t[p].pre=upd(t[l].pre,t[l].sum+t[r].pre,tim[p]);
	}else{
		Num nl=vis[l]?upd(Num(),t[l].pre,tim[p]):t[l].sum;
		Num nr=vis[r]?upd(Num(),t[r].pre,tim[p]):t[r].sum;
		t[p].sum=t[p].pre=nl+nr;
	}
}
int newnode(int l,int r,int o){
	int p=++id;
	lc[p]=l,rc[p]=r,op[p]=o;
	fa[l]=fa[r]=p;
	L[p]=L[l],R[p]=R[r];
	pushup(p); return p;
}
int seq[M],tp;
int build(int l,int r,int o){
	if(l>r) return 0;
	if(l==r) return seq[l];
	int mid=(L[seq[l]]+R[seq[r]])/2;
	int m=l;while(m<r-1&&R[seq[m]]<mid)m++;
	return newnode(build(l,m,o),build(m+1,r,o),o);
}
int build(int x){
	int beg=tp;
	for(;x;x=son[x]){
		L[x]=R[x]=++ti;
		t[x].sum=t[x].pre=Num(a[x],1,1);
		tim[x]=INF;

		int now=tp;
		for(int y:E[x])if(y!=ff[x]&&y!=son[x]){
			int son=build(y);
			vis[son]=1;
			seq[++tp]=son;
		}
		atom[x]=x;
		if(now<tp) atom[x]=newnode(x,build(now+1,tp,0),0);
		tp=now;
		seq[++tp]=atom[x];
	}
	int ret=build(beg+1,tp,1);
	tp=beg; return ret;
}
void upd(int p,ll w){
	if(!p)return;
	t[p].sum.upd(w);t[p].pre.upd(w);
	if(tim[p]!=INF)tim[p]-=w;
	tag[p]+=w;
}
void pushdown(int p){
	upd(lc[p],tag[p]);
	upd(rc[p],tag[p]);
	tag[p]=0;
}
void modify(int p,int l,int r,ll w){
	if(!p||R[p]<l||r<L[p])return;
	if(l<=L[p]&&R[p]<=r&&w<tim[p]){
		upd(p,w);
		return;
	}
	pushdown(p);
	modify(lc[p],l,r,w),modify(rc[p],l,r,w);
	pushup(p);
}
void pushpath(int x){
	if(fa[x]) pushpath(fa[x]);
	pushdown(x);
}
int query(int x){
	x=atom[x]; pushpath(x);
	auto [sum,pre]=t[x];
	while(fa[x]&&op[fa[x]]){
		int f=fa[x];
		if(x==lc[f]){
			int y=rc[f];
			pre=getmax(pre,sum+t[y].pre);
			sum=sum+t[y].sum;
		}
		x=f;
	}
	return pre.cnt;
}
void procedure(){
	n=id=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	int rt=build(1);
	while(q--){
		int u=read(); ll x=read();
		if(x) modify(rt,L[u],L[u]+sz[u]-1,x);
		printf("%d\n",query(u));
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	tim[0]=INF;
	// math_init();
	while(T--) procedure();
	return 0;
}