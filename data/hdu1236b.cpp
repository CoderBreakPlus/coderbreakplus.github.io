// created time: 2026-08-13 14:31:55
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

int n,m,a[500005],b[500005];
ull s0[2000005],s1[2000005],t0[2000005],t1[2000005],t2[2000005],len[2000005];
void apply(int p,ull v0,ull v1,ull v2){
	s1[p]+=v1*s0[p]+v2*len[p];
	s0[p]+=v0*len[p];

	t2[p]+=t0[p]*v1+v2;
	t0[p]+=v0,t1[p]+=v1;
}
void pushup(int p){
	s0[p]=s0[p<<1]+s0[p<<1|1];
	s1[p]=s1[p<<1]+s1[p<<1|1];
}
void pushdown(int p){
	apply(p<<1,t0[p],t1[p],t2[p]);
	apply(p<<1|1,t0[p],t1[p],t2[p]);
	t0[p]=t1[p]=t2[p]=0;
}
void update(int l,int r,int ql,int qr,ull v,int p){
	if(r<ql || qr<l) return;
	if(ql<=l && r<=qr) {
		apply(p,v,0,0);
		return;
	}
	int mid=(l+r)>>1;pushdown(p);
	update(l,mid,ql,qr,v,p<<1);update(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
ull query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr) return s1[p];
	int mid=(l+r)>>1;pushdown(p);
	return query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1);
}
void build(int l,int r,int p){
	len[p]=r-l+1;
	t0[p]=t1[p]=t2[p]=0;
	if(l==r){
		s1[p]=a[l],s0[p]=b[l];
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
}

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read(),b[i]=read();
	build(1,n,1);

	while(m--){
		apply(1,0,1,0);
		int op=read(),l=read(),r=read();
		if(op==1){
			update(1,n,l,r,read(),1);
		}else{
			printf("%llu\n",query(1,n,l,r,1));
		}
	}
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