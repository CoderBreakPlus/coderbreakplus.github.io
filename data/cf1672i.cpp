// created time: 2026-08-24 10:40:09
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

const int M = (1<<20)+5;
const int N = 500005;

int n,vis[N],p[N];
int ta,tb,ans;
pair<int,int> a[N],b[N];

struct BIT{
	int c[N];
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
	void clear(){ for(int i=1;i<=n;i++) c[i]=0; }
}bx,by;

int vis[N];
namespace L{
	struct S0{
		int mn[M],m;
		void pushup(int p){ mn[p]=min(mn[p<<1],mn[p<<1|1]); }
		void init(){
			m=1;
			while(m<=n+1)m<<=1;
			for(int i=1;i<=2*m;i++)mn[i]=1e9;
		}
		void upd(int x,int v){
			mn[x+=m]=v;
			for(x>>=1;x;x>>=1)pushup(x);
		}
		void findr(int x,int v){

		}
	}s0;
	struct S1{
		int mn[M],val[M],id[M],tag[M];
		void pushup(int p){
			if(val[p<<1]<val[p<<1|1])
				val[p]=val[p<<1],id[p]=id[p<<1];
			else
				val[p]=val[p<<1|1],id[p]=id[p<<1|1];
		}
		void upd(int p,int v){ val[p]+=v,tag[p]+=v; }
		void pushdown(int p){ if(tag[p]) upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=0; }
		void build(int l,int r,int p){
			tag[p]=0;
			if(l==r){
				val[p]=mn[p]=1e9;
				return;
			}
			int mid=(l+r)>>1;
			build(l,mid,p<<1),build(mid+1,r,p<<1|1);
			pushup(p);
		}
		void modify(int l,int r,int x,int op,int p){
			if(l==r){
				if(op) mn[p]=by.qry(p[l]),val[p]=mn[p]-bx.qry(l);
				else val[p]=mn[p]=1e9;
				return;
			}
			int mid=(l+r)>>1;pushdown(p);
			if(x<=mid)modify(l,mid,x,op,p<<1);
			else modify(mid+1,r,x,op,p<<1|1);
			pushup(p);
		}
		void update(int l,int r,int ql,int qr,int v,int p){
			if(r<ql||qr<l) return;
			if(ql<=l && r<=qr){ upd(p,v);return; }
			int mid=(l+r)>>1;pushdown(p);
			update(l,mid,ql,qr,v,p<<1);
			update(mid+1,r,ql,qr,v,p<<1|1);
			pushup(p);
		}
		void update2(int l,int r,int ql,int qr,int v,int p){

		}
	}s1;
	void init(){
		int cur=1e9;
		s0.init(),s1.build(1,n,1);
		for(int i=1;i<=ta;i++){
			auto [x,y]=a[i];
			if(y<cur){
				vis[i]=1,cur=y;
				s1.modify(1,n,x,1,1);
			}else{
				s0.upd(a[i].fi,a[i].se);
			}
		}
	}
	void del(int i){
		s1.modify(1,n,i,0,1);
		// pi - i
		// for every j >= i, val ++
		s1.update(1,n,i,n,1,1);

	}
}

void del(int i){
	int x=bx.qry(i),y=by.qry(p[i]);
	bx.upd(i,-1),by.qry(p[i],-1);
	chkmax(ans, max(x-y,y-x));
	
	vis[i]=2;
	if(i<=p[i]) L::del(i);
	else R::del(i);
}
void procedure(){
	n=read();
	ans=ta=tb=0;
	for(int i=1;i<=n;i++){
		p[i]=read(),vis[i]=0;
		if(i<=p[i]) a[++ta]={i,p[i]};
		else b[++tb]={i,p[i]};
	}
	reverse(a+1,a+ta+1);
	L::init();

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