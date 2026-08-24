// created time: 2026-08-24
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
const int N=5e5+5,INF=1e9;
int n,ans,p[N];
int ABS(int x){ return x<0?-x:x; }
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
}bx,by;

struct Seg{
	bool op;
	int val[N*4],mn[N*4],mx[N*4],id[N*4],tag[N*4];
	void upd(int p,int w){
		val[p]+=w,tag[p]+=w;
	}
	void pushup(int p){
		val[p]=min(val[p<<1],val[p<<1|1]);
		mn[p]=min(mn[p<<1],mn[p<<1|1]);
		mx[p]=max(mx[p<<1],mx[p<<1|1]);
		id[p]=id[p<<1|(val[p]==val[p<<1|1])];
	}
	void pushdown(int p){
		if(tag[p])
			upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=0;
	}
	void modify(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr){ upd(p,v); return; }
		int mid=(l+r)>>1; pushdown(p);
		modify(l,mid,ql,qr,v,p<<1);
		modify(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
	void update(int l,int r,int x,int a,int b,int c,int p){
		if(l==r){
			val[p]=a,mn[p]=b,mx[p]=c;
			return;
		}
		int mid=(l+r)>>1; pushdown(p);
		if(x<=mid)update(l,mid,x,a,b,c,p<<1);
		else update(mid+1,r,x,a,b,c,p<<1|1);
		pushup(p);
	}
	int active(int l,int r,int ql,int qr,int cur,int p){
		if(r<ql||qr<l||cur<=mn[p])return cur;
		if(l==r){
			int pos=op?n-l+1:l;
			cur=mn[p];
			mx[p]=mn[p],mn[p]=INF;
			val[p]=ABS(bx.qry(pos)-by.qry(::p[pos]));
			return cur;
		}
		int mid=(l+r)>>1;pushdown(p);
		cur=active(mid+1,r,ql,qr,cur,p<<1|1);
		cur=active(l,mid,ql,qr,cur,p<<1);
		pushup(p);
		return cur;
	}
	int qry(int l,int r,int v,int p){
		if(mx[p]<v)return n+1; 
		if(l==r) return l;
		int mid=(l+r)>>1;
		if(mx[p<<1]>=v) return qry(l,mid,v,p<<1);
		else return qry(mid+1,r,v,p<<1|1);
	}
	int find(int l,int r,int x,int p){
		if(mx[p]<0) return 0;
		if(l==r) return l;
		int mid=(l+r)>>1;
		if(x>mid){
			int ret=find(mid+1,r,x,p<<1|1);
			if(ret)return ret;
		}
		return find(l,mid,x,p<<1);
	}
	int find_right(int l,int r,int x,int p){
	    if(mx[p]<0) return n+1;
	    if(l==r) return l;
	    int mid=(l+r)>>1;
	    if(x<=mid){
	        int ret=find_right(l,mid,x,p<<1);
	        if(ret<=n)return ret;
	    }
	    return find_right(mid+1,r,x,p<<1|1);
	}
	void build(int l,int r,int p){
		tag[p]=0;
		if(l==r){
			val[p]=INF,mn[p]=INF,mx[p]=-INF,id[p]=l;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		pushup(p);
	} 
}T1,T2;
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)p[i]=read();
	for(int i=1;i<=n;i++)bx.upd(i,1),by.upd(i,1);

	T2.op=1;
	T1.build(1,n,1),T2.build(1,n,1);
	for(int i=1;i<=n;i++){
		if(i<p[i])T1.update(1,n,i,INF,p[i],-INF,1);
		else T2.update(1,n,n-i+1,INF,n-p[i]+1,-INF,1);
	}
	T1.active(1,n,1,n,INF,1);
	T2.active(1,n,1,n,INF,1);

	for(int i=1;i<=n;i++){
		if(T1.val[1]<T2.val[1]){
			chkmax(ans,T1.val[1]);
			int pos=T1.id[1];

			T1.update(1,n,pos,INF,INF,-INF,1);
			bx.upd(pos,-1),by.upd(p[pos],-1);

			int tmp=T1.qry(1,n,p[pos],1);
			T1.modify(1,n,tmp,pos,-1,1);

			tmp=T2.qry(1,n,n-p[pos]+1,1);
			T2.modify(1,n,tmp,n-pos+1,-1,1);

			tmp=T1.find(1,n,pos,1);
			int tmp2=T1.find_right(1,n,pos,1);
			T1.active(1,n,tmp+1,pos-1,(tmp2<=n)?p[tmp2]:INF,1);
		}else{
			chkmax(ans,T2.val[1]);
			int pos=T2.id[1];

			T2.update(1,n,pos,INF,INF,-INF,1);
			pos=n-pos+1;

			bx.upd(pos,-1),by.upd(p[pos],-1);

			int tmp=T1.qry(1,n,p[pos],1);
			T1.modify(1,n,tmp,pos,-1,1);

			tmp=T2.qry(1,n,n-p[pos]+1,1);
			T2.modify(1,n,tmp,n-pos+1,-1,1);

			tmp=T2.find(1,n,n-pos+1,1);
			int tmp2=T2.find_right(1,n,n-pos+1,1);
			T2.active(1,n,tmp+1,n-pos,(tmp2<=n)?(n-p[n-tmp2+1]+1):INF,1);
		}
	}
	printf("%d\n",ans);
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