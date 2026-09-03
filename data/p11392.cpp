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
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
int n,q,v[500005],stk[500005],l[500005],r[500005],ans[500005],pt;

vector<pair<int,int>>up[500005], qry[500005];

inline void push(int a,int b){
	int W = 2*b-a-1;
	if(W<n) up[a].pb(W,v[a]+v[b]);
}
struct Node{
	int lm,rm,m;
	Node(){ lm=rm=m=-1e9; }
	Node(int x,int y,int z){ lm=x, rm=y, m=z; }
}tr[2000005];
inline Node operator+ (Node A, Node B){
	return Node(max(A.lm,B.lm), max(A.rm,B.rm), max({A.m,B.m,A.lm + B.rm}));
}
inline void pushup(int pos){
	tr[pos] = tr[pos<<1] + tr[pos<<1|1];
}
inline void build(int l,int r,int pos){
	if(l == r){
		tr[pos].rm = v[l];
		return;
	}
	int mid = (l+r)>>1;
	build(l,mid,pos<<1); build(mid+1,r,pos<<1|1);
	pushup(pos);
}
inline void update(int l,int r,int x,int w,int pos){
	if(l==r){
		tr[pos].lm = max(tr[pos].lm, w);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid) update(l,mid,x,w,pos<<1);
	else update(mid+1,r,x,w,pos<<1|1);
	pushup(pos);
}
Node glo;
inline void query(int l,int r,int ql,int qr,int pos){
	if(r<ql || qr<l) return;
	if(ql<=l && r<=qr){
		glo = glo + tr[pos];
		return;
	}
	int mid = (l+r)>>1;
	query(l,mid,ql,qr,pos<<1);
	query(mid+1,r,ql,qr,pos<<1|1);
}
int fjy666(int l,int r){
	glo = Node();
	query(1,n,l,r,1);
	return glo.m;
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++) v[i]=read(),r[i]=n+1;
	build(1,n,1);
	int tp = 0;
	for(int i=1;i<=n;i++){
		while(tp && v[stk[tp]]<v[i]) r[stk[tp--]]=i;
		l[i]=stk[tp]; stk[++tp]=i;
	}
	for(int i=1;i<=n;i++){
		if(l[i]>=1) push(l[i],i);
		if(r[i]<=n) push(i,r[i]);
	}
	q=read();
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		qry[l].pb(r,i);
	}
	for(int i=n;i>=1;i--){
		for(auto [x,w]: up[i]) update(1,n,x,w,1);
		for(auto [r,id]: qry[i]){
			ans[id] = fjy666(i,r);
		}
	}
	for(int i=1;i<=q;i++) printf("%d\n", ans[i]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("input.txt","r",stdin));
		assert(freopen("output.txt","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}