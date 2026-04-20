// created time: 2026-04-20 19:21:18
// http://10.49.18.71/problem/2512
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

int n,m;
struct Fuck{
	int tmp[2000005],cnt;
	void add(int x){ tmp[++cnt]=x; }
	void init(){ sort(tmp+1,tmp+cnt+1); cnt=unique(tmp+1,tmp+cnt+1)-(tmp+1); }
	void get(int &x){ x=lower_bound(tmp+1,tmp+cnt+1,x)-tmp; }
}X,Y;
struct Node{
	int x,y,v;
}a[1000005],b[1000005];

struct Tree{
	ll s0,s1,mx;
	Tree(){ s0=s1=mx=0; }
};
Tree operator+ (const Tree &A, const Tree &B){
	Tree C;
	C.s0=A.s0+B.s0;
	C.mx=max(A.mx+B.s0,B.mx);
	return C;
}
struct Seg{
	Tree t[8000005];
	void pushup(int p){
		t[p]=t[p<<1]+t[p<<1|1];
	}
	void upd0(int l,int r,int x,int v,int p){
		if(l==r){
			t[p].s0+=v;
			return;
		}
		int mid=(l+r)>>1; 
		if(x<=mid) upd0(l,mid,x,v,p<<1);
		else upd0(mid+1,r,x,v,p<<1|1);
		pushup(p);
	}
	void upd1(int l,int r,int x,ll v,int p){
		if(l==r){
			t[p].s1=t[p].mx=max(t[p].s1,(ll)v);
			return;
		}
		int mid=(l+r)>>1; 
		if(x<=mid) upd1(l,mid,x,v,p<<1);
		else upd1(mid+1,r,x,v,p<<1|1);
		pushup(p);
	}
	Tree query(int l,int r,int ql,int qr,int p){
		if(r<ql||qr<l) return Tree();
		if(ql<=l&&r<=qr) return t[p];
		int mid=(l+r)>>1;
		return query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1);
	}
}S;
ll dp[1000005];

void procedure(){
	n=read(),m=read();	
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read(),a[i].v=read();
		X.add(a[i].x),Y.add(a[i].y);
	}
	for(int i=1;i<=m;i++){
		b[i].x=read(),b[i].y=read(),b[i].v=read();
		X.add(b[i].x),Y.add(b[i].y);
	}
	X.init(),Y.init();
	for(int i=1;i<=n;i++) X.get(a[i].x),Y.get(a[i].y);
	for(int i=1;i<=m;i++){
		X.get(b[i].x),Y.get(b[i].y);
		S.upd0(0,Y.cnt,b[i].y,b[i].v,1);
	}

	sort(a+1, a+n+1, [](const Node &A, const Node &B){
		return A.x<B.x;
	});
	sort(b+1, b+m+1, [](const Node &A, const Node &B){
		return A.x<B.x;
	});
	int pt=m;

	ll ans=0;
	a[n+1].x=X.cnt+1,a[n+1].y=0;
	for(int i=n;i>=1;i--){
		while(pt>=1 && b[pt].x>a[i].x){
			S.upd0(0,Y.cnt,b[pt].y,-b[pt].v,1),--pt;
		}
		dp[i]=S.query(0,Y.cnt,0,a[i].y,1).mx-a[i].v;
		ans=max(ans, dp[i]);
		S.upd1(0,Y.cnt,a[i].y,dp[i],1);
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