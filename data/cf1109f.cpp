// created time: 2026-09-20 19:16:25
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

int n,m,N,a[1005][1005];
vector<int>E[200005];
int code(int i,int j){ return (i-1)*m+j; }
void add(int x,int y){ E[x].pb(y),E[y].pb(x); }
namespace dsu{
	int fa[200005],sz[200005],a[200005],b[200005],tp;
	int find(int x){ while(x!=fa[x])x=fa[x];return fa[x]; }
	void init(){
		for(int i=1;i<=N;i++)fa[i]=i,sz[i]=1;
	}
	bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return 0; if(sz[x]<sz[y])swap(x,y);
		a[++tp]=x,b[tp]=y;
		sz[x]+=sz[y],fa[y]=x;
		return 1;
	}
	void undo(){ sz[a[tp]]-=sz[b[tp]],fa[b[tp]]=b[tp]; tp--; }
	void undo(int x){ while(tp>x) undo(); }
}

int cl,cr;

bool add(int x){
	if(!x) return 0;
	bool ret=1;	
	for(int y:E[x]) if(cl<=y&&y<=cr) ret&=dsu::merge(x,y);
	return ret;
}
bool addL(){ return add(--cl); }
bool addR(){ return add(++cr); }

void adjust(int L,int R){
	if(L>R)return;
	if(cl>=cr) cl=L,cr=L;
	while(cl>L) addL();
	while(cr<R) addR();
}
int far[200005];
void solve(int l,int r,int ql,int qr){
	if(l>r)return;
	int mid=(l+r)>>1;
	int sl=cl,sr=cr,stp=dsu::tp;

	auto backup=[&](){ cl=sl,cr=sr,dsu::undo(stp); };
	
	adjust(mid,max(mid,ql));
	while(cr<=qr&&addR());
	far[mid]=cr-1; backup();

	adjust(mid-1,ql),solve(l,mid-1,ql,qr),backup();
	adjust(r,far[mid]),solve(mid+1,r,ql,qr),backup();
}
struct Node{
	int x,y;
};
Node operator+ (const Node &A,const Node &B){
	Node C;
	C.x=min(A.x,B.x);
	C.y=A.y*(A.x==C.x)+B.y*(B.x==C.x);
	return C;
}
#define mid ((l+r)>>1)
struct Seg{
	Node t[800005];
	int tag[800005];

	void pushup(int p){
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void upd(int p,int w){ tag[p]+=w,t[p].x+=w; }

	void pushdown(int p){
		if(tag[p])upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=0;
	}
	void build(int l,int r,int p){
		if(l==r){ t[p]={l,1}; return; }
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		pushup(p);
	}
	void update(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr){upd(p,v);return;}
		pushdown(p);
		update(l,mid,ql,qr,v,p<<1);
		update(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
	Node query(int l,int r,int ql,int qr,int p){
		if(r<ql||qr<l) return (Node){(int)1e9,-1};
		if(ql<=l&&r<=qr) return t[p];
		pushdown(p);
		return query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1);
	}
}S;
void procedure(){
	n=read(),m=read();N=n*m;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[i][j]=read();

	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++){
			if(i<n) add(a[i][j],a[i+1][j]);
			if(j<m) add(a[i][j],a[i][j+1]);
		}
	dsu::init();
	solve(1,N,1,N);

	// for(int i=1;i<=N;i++) printf("%d ",far[i]);
	S.build(1,N,1);
	ll ans=0;
	for(int i=N;i>=1;i--){
		for(int y:E[i])
			if(y>i) S.update(1,N,y,N,-1,1);

		auto [a,b]=S.query(1,N,i,far[i],1);
		if(a==i) ans+=b;
	}
	printf("%lld\n",ans);
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