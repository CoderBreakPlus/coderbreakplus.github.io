// created time: 2026-10-04 20:18:01
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
#define mid ((l+r)>>1)
int n,q,x[N+5],mx[20][N+5],mn[20][N+5],bl[N+5];
int lf[N+5],rh[N+5],l[N+5],r[N+5];

int getmx(int i,int j){ if(!i||!j)return i+j; return x[i]>x[j]?i:j; }
int getmn(int i,int j){ if(!i||!j)return i+j; return x[i]<x[j]?i:j; }

int qrymx(int l,int r){
	if(l>r)return 0;
	int p=lg2(r-l+1);
	return getmx(mx[p][l],mx[p][r-(1<<p)+1]);
}
int qrymn(int l,int r){
	if(l>r)return 0;
	int p=lg2(r-l+1);
	return getmn(mn[p][l],mn[p][r-(1<<p)+1]);
}

ll ans[N+5],qz[N+5];

vector<tuple<int,int,int,int>>t[N<<2][4];
vector<int>lf[N<<2],rh[N<<2];
vector<ll>slf[N<<2],srh[N<<2],ss[N<<2];

void build(int l,int r,int p){
	lf[p].resize(r-l+1),rh[p].resize(r-l+1);
	slf[p].resize(r-l+1),srh[p].resize(r-l+1);
	ss[p].resize(r-l+1);
	for(int i=l;i<=r;i++)
		lf[p][i-l]=slf[p][i-l]=qrymx(l,i-1),
		rh[p][i-l]=srh[p][i-l]=qrymn(i+1,r),
		ss[p][i-l]=x[i];

	for(int i=1;i<=r-l;i++)
		slf[p][i]+=slf[p][i-1],srh[p][i]+=srh[p][i-1],ss[p][i]+=ss[p][i-1];

	if(l==r) return;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
}
void ins(int p,int l,int r,int vl,int vr,int id){
	int sz=r-l+1, pL=-1, pR=sz;
	{
		int L=0,R=sz-1;
		while(L<=R){
			int M=(L+R)>>1;
			if(getmx(vl,lf[M])!=lf[M]) pL=M,L=M+1;
			else R=M-1; 
		}
	}
	{
		int L=0,R=sz-1;
		while(L<=R){
			int M=(L+R)>>1;
			if(getmn(rh[M],vr)!=rh[M]) pR=M,R=M-1;
			else L=M+1;
		}
	}
	// range: 0~sz-1
	// basically: x - Lmax
	ans[id]+=ss[p][sz-1]-slf[p][sz-1]+slf[p][pL]-(ll)(pL+1)*x[vl];
	if(pL<pR){
		if(0<=pL) t[p][1].pb(pL,x[vl],id,1);
		if(pR<sz){
			if(0<pR) t[p][2].pb(pR-1,x[vr],id,-1);
			t[p][2].pb(sz-1,x[vr],id,1);
		}
		if(pL+1<pR) t[p][0].pb(pL,0,id,-1),t[p][0].pb(pR-1,0,id,1);
	}else{
		if(0<pR) t[p][1].pb(pR-1,x[vl],id,1);
		if(pL+1<sz){
			if(0<=pL) t[p][2].pb(pL,x[vr],id,-1);
			t[p][2].pb(sz-1,x[vr],id,1);
		}
		if(pR<=pL) t[p][3].pb(pR-1,x[vl]+x[vr],id,-1),t[p][3].pb(pL,x[vl]+x[vr],id,1);
	}
}
void modify(int l,int r,int ql,int qr,int id,int p){
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr) return ins(p,l,r,qrymx(ql-1,l-1),qrymn(r+1,qr+1),id);
	modify(l,mid,ql,qr,id,p<<1),modify(mid+1,r,ql,qr,id,p<<1|1);
}
int seq[4][N+5];

void solve(int l,int r,int p){
	int sz=r-l+1;
	for(int i=0;i<sz;i++){
		seq[0][i]=x[lf[p][i]]+x[rh[p][i]]-2*x[i];
		seq[1][i]=x[rh[p][i]]-2*x[i];
		seq[2][i]=x[lf[p][i]]-2*x[i];
		seq[3][i]=-2*x[i];
	}
	for(int o=0;o<4;o++){
		for(auto [i,v,id,cf]: t[p][o]){
			for(int j=0;j<=i;j++) 
		}
	}
	if(l==r)return p;
	solve(l,mid,p<<1),solve(mid+1,r,p<<1|1);
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		x[i]=read(),mx[0][i]=mn[0][i]=i;
		qz[i]=qz[i-1]+x[i];
	}
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++){
			mx[i][j]=getmx(mx[i-1][j],mx[i-1][j+(1<<i-1)]);
			mn[i][j]=getmn(mn[i-1][j],mn[i-1][j+(1<<i-1)]);
		}
	build(1,n,1);
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read();
		ans[i]=x[r[i]]-x[l[i]];
		modify(1,n,l[i]+1,r[i]-1,i,1);
	}
	solve(1,n,1);
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