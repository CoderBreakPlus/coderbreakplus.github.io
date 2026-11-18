// created time: 2026-11-18 08:18:15
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

int n,M,q,a[500005],b[500005],l[200005],r[200005];

int lf[500005],rh[500005];
#define mid ((l+r)>>1)
struct Seg{
	int o;
	int get(int x,int y){
		if(!x||!y)return x^y;
		return o?min(x,y):max(x,y);
	}
	int t[2200005],tag[2200005];
	void pushup(int p){ t[p]=get(t[p<<1],t[p<<1|1]); }
	void upd(int p,int v){ t[p]=tag[p]=v; }
	void pushdown(int p){
		if(tag[p]){
			upd(p<<1,tag[p]);
			upd(p<<1|1,tag[p]);
			tag[p]=0;
		}
	}
	int modify(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return 0;
		if(ql<=l&&r<=qr){
			int ret=t[p];
			upd(p,v);
			return ret;
		}
		pushdown(p);
		int ret=get(modify(l,mid,ql,qr,v,p<<1),modify(mid+1,r,ql,qr,v,p<<1|1));
		pushup(p);
		return ret;
	}
	void build(int l,int r,int p){
		t[p]=tag[p]=0;
		if(l==r)return;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	}
}S;

struct T{
	int c[500005];
	void upd(int x,int w){
		while(x<=n){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	int qry(int x){
		int ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
}T;

vector<tuple<int,int,int>>E[500005];
vector<int>qry[500005];

int ans[200005];

void procedure(){
	n=read(),M=2*n;	
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();

	S.o=0,S.build(1,M,1);
	for(int i=1;i<=n;i++)lf[i]=S.modify(1,M,b[i],a[i],i,1);

	S.o=1,S.build(1,M,1);
	for(int i=n;i>=1;i--){
		rh[i]=S.modify(1,M,b[i],a[i],i,1);
		if(!rh[i])rh[i]=n+1;
	}
	for(int i=1;i<=n;i++){
		E[lf[i]+1].pb(i,rh[i]-1,1);
		E[i+1].pb(i,rh[i]-1,-1);
	}
	q=read();
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read();
		qry[l[i]].pb(i);
	}

	for(int i=1;i<=n;i++){
		for(auto [l,r,v]:E[i]){
			T.upd(l,v),T.upd(r+1,-v);
		}
		for(int o:qry[i]){
			ans[o]=T.qry(r[o]);
		}
	}
	for(int i=1;i<=q;i++)
		if(ans[i])puts("No");
		else puts("Yes");
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