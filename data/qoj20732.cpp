// created time: 2026-10-04 13:48:36
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

int n,a[200005],w[200005];
ll ans;
struct zkw{
	int t[800005],o,m;
	int get(int i,int j){
		if(!i||!j)return i^j;
		if(!o) return a[i]<a[j]?i:j;
		else return a[i]>a[j]?i:j;
	}
	void pushup(int p){ t[p]=get(t[p<<1],t[p<<1|1]); }
	void init(){
		m=1;while(m<=n+1) m<<=1;
		for(int i=1;i<=2*m;i++) t[i]=0;
	}
	void upd(int x,int w){ for(t[x+=m]=w;x>1;) pushup(x>>=1); }
	int qry(int l,int r){
		// cout<<"fuck "<<l<<"->"<<r<<endl;
		if(l>r)return 0;
		int ret=0;
		for(l+=m-1,r+=m+1;l^r^1;l>>=1,r>>=1){
			if(~l&1) ret=get(ret,t[l^1]);
			if( r&1) ret=get(ret,t[r^1]);
		}
		// cout<<"query "<<l<<"->"<<r<<" ret="<<ret<<endl;
		return ret;
	}
}T0,T1;
struct sgt{
	int mn[800005],ls[800005],rs[800005],tag[800005];
	void pushup(int p){
		if(mn[p<<1]!=mn[p<<1|1]){
			int o=(p<<1)+(mn[p<<1|1]<mn[p<<1]);
			mn[p]=mn[o],ls[p]=ls[o],rs[p]=rs[o];
		}else{
			mn[p]=mn[p<<1],ls[p]=ls[p<<1],rs[p]=rs[p<<1|1];
		}
	}
	void upd(int p,int w){ tag[p]+=w,mn[p]+=w; }
	void pushdown(int p){
		if(tag[p]){
			upd(p<<1,tag[p]);
			upd(p<<1|1,tag[p]);
			tag[p]=0;
		}
	}
	void update(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr){ upd(p,v); return; }
		pushdown(p); int mid=(l+r)>>1;
		update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
	void build(int l,int r,int p){
		if(l==r){ mn[p]=0, ls[p]=rs[p]=l; return; }
		int mid=(l+r)>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		pushup(p);
	}
}S;
void change(int i,int x){
	if(w[i]<=0) T1.upd(i,0);
	if(w[i]>=0) T0.upd(i,0);
	w[i]+=x;
	// cout<<"change "<<i<<" "<<x<<endl;
	if(w[i]<=0) T1.upd(i,i);
	if(w[i]>=0) T0.upd(i,i);
}
void procedure(){
	n=read(); T0.init(),T1.o=1,T1.init();
	for(int i=1;i<=n;i++)a[i]=read();
	S.build(0,n,1);
	for(int i=1;i<=n;i++){
		int x=read();
		T0.upd(x,x),T1.upd(x,x);
		int final=0; int delta=0, jc1=0, jc2=0;
		// first try
		// cout<<"add "<<x<<endl;
		{
			S.update(0,n,x,n,1,1);
			int pos = S.rs[1];
			// cout<<T0.t[1]<<endl;
			jc1 = T0.qry(pos+1,n);
			// cout<<"find "<<jc1<<" val="<<a[x]-a[jc1]<<endl;
			if(jc1 && a[x]-a[jc1] > delta){
				delta = a[x]-a[jc1];
				final = 1;
			}
			S.update(0,n,x,n,-1,1);
		}
		{
			S.update(0,n,x,n,-1,1);
			int pos = S.mn[1]==-1?S.ls[1]:n;
			// cout<<"pos="<<pos<<endl;
			jc2 = T1.qry(1,pos);
			if(jc2 && a[jc2]-a[x] > delta){
				delta = a[jc2]-a[x];
				final = -1;
			}
			S.update(0,n,x,n,1,1);
		}

		if(final == 1){
			change(x,1), change(jc1,-1);
			S.update(0,n,x,n,1,1), S.update(0,n,jc1,n,-1,1);
		}else if(final == -1){
			change(x,-1), change(jc2,1);
			S.update(0,n,x,n,-1,1), S.update(0,n,jc2,n,1,1);
		}
		// for(int i=1;i<=n;i++) cout<<w[i]<<" "; cout<<endl;
		ans += delta;
		printf("%lld ", ans);
	}
	puts("");
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