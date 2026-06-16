// created time: 2026-06-16 09:40:08
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
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

int n,k,q,a[300005],l[300005],r[300005],ans[300005];
vector<int>qry[300005],upd[300005];

int vis[300005],sum[300005],ia[300005],rt[300005];

struct Node{
	int mx,mn,sum;
	Node(){ mx = mn = sum = 0; }
	Node(int a){ mx = mn = sum = a; }
	Node(int a,int b,int c){ mx = a, mn = b, sum = c; }
}t[9000005];

int lc[9000005],rc[9000005],id;
inline Node operator+ (const Node &A, const Node &B){
	return Node(max(A.mx, A.sum+B.mx), min(A.mn, A.sum+B.mn), A.sum+B.sum);
}

void pushup(int p){ t[p]=t[lc[p]]+t[rc[p]]; }
void build(int l,int r,int &p){
	p=++id;
	if(l==r) {t[p]=Node(1);return;}
	int mid=(l+r)>>1;
	build(l,mid,lc[p]),build(mid+1,r,rc[p]);
	pushup(p);
}
void modify(int l,int r,int x,int b,int &p){
	p=++id;
	if(l==r) {t[p]=Node(-1);return;}
	int mid=(l+r)>>1;
	if(x<=mid) rc[p]=rc[b],modify(l,mid,x,lc[b],lc[p]);
	else lc[p]=lc[b],modify(mid+1,r,x,rc[b],rc[p]);
	pushup(p);
}

int qsum(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l) return 0;
	if(ql<=l && r<=qr) return t[p].sum;
	int mid=(l+r)>>1;
	return qsum(l,mid,ql,qr,lc[p])+qsum(mid+1,r,ql,qr,rc[p]);
}

Node sb;
bool hv;
void query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return;
	if(ql<=l && r<=qr){
		if(!hv) sb=t[p];
		else sb=sb+t[p];
		hv=1;
		return;
	}
	int mid=(l+r)>>1;
	query(l,mid,ql,qr,lc[p]),query(mid+1,r,ql,qr,rc[p]);
}

int cur,ok;
void solve(int l,int r,int x,int w,int p){
	int mid=(l+r)>>1;
	if(r<x || ok<=n) return;
	if(x<=l && cur+t[p].mx<w){
		cur+=t[p].sum;
		return;
	}
	if(l==r){
		ok=l;
		return;
	}
	solve(l,mid,x,w,lc[p]),solve(mid+1,r,x,w,rc[p]);
}
int find(int i,int x){
	if(i+k-1>n) return n+1;
	cur=qsum(1,n,i,i+k-2,rt[x]);
	ok = n+1;
	solve(1,n,i+k-1,0,rt[x]);
	return ok;
}
int check(int i,int x,int r){
	if(i+k-1>r) return 0;
	hv=1,sb=Node(-1e9,1e9,qsum(1,n,i,i+k-2,rt[x]));
	query(1,n,i+k-1,r,rt[x]);
	return sb.mx>=0;
}
bool exist(int i,int x){
	int to = find(i,x);
	if(to>n) return 0;
	if(to==i+k-1) return 1;
	hv=0,query(1,n,i,to-k,rt[x]);
	return sb.mn>0;
}

struct BIT1{
	int c[300005];
	void upd(int x,int w){ while(x<=n){ chkmax(c[x], w);x+=(x&-x); } }
	int qry(int x){ int ret=0; while(x){ chkmax(ret,c[x]);x-=(x&-x); } return ret; }
}b1;

struct BIT2{
	int c[300005];
	void upd(int x,int w){ while(x<=n){ c[x]+=w;x+=(x&-x); } }
	int qry(int x){ int ret=0; while(x){ ret+=c[x];x-=(x&-x); } return ret; }
}b2;

void procedure(){
	n=read(),k=read(),q=read();
	for(int i=1;i<=n;i++)ia[a[i]=read()]=i;

	build(1,n,rt[1]);
	for(int i=1;i<n;i++)
		modify(1,n,ia[i],rt[i],rt[i+1]);

	for(int i=1;i<=n;i++){
		int l=1,r=n,ret=0;
		while(l<=r){
			int mid=(l+r)>>1;
			if(exist(i,mid)) ret=mid,l=mid+1;
			else r=mid-1;
		}
		upd[ret].pb(i);
	}

	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read(); int x=read();
		qry[x].pb(i);
	}
	for(int i=n;i>=1;i--){
		for(int x: upd[i]) b1.upd(x,x),b2.upd(x,1),vis[x]=1;
		if(!qry[i].size())continue;
		for(int x: qry[i]){
			int L=l[x], R=n, ret=l[x]-1;

			while(L<=R){
				int mid=(L+R)>>1;
				int ok=b1.qry(mid);
				bool flg = (ok<l[x]) || (check(ok,i,r[x]));
				if(flg) ret=mid, L=mid+1;
				else R=mid-1;
			}
			ans[x]=b2.qry(ret)-b2.qry(l[x]-1);
		}
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",ans[i]);
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
