// created time: 2026-08-20 12:15:08
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

int n,m,a[200005];

struct Info{
	int l,r,c;
}t[800005];
int cov[800005],tag[800005];
Info operator+ (const Info &A, const Info &B){
	return (Info){A.l,B.r,A.c+(A.r^B.l)+B.c};
}
void pushup(int p){
	t[p]=t[p<<1]+t[p<<1|1];
}
void cover(int p,int v){
	cov[p]=v,tag[p]=0;
	t[p]=(Info){v,v,0};
}
void rev(int p){
	tag[p]^=1,t[p].l^=1,t[p].r^=1;
}
void pushdown(int p){
	if(~cov[p])
		cover(p<<1,cov[p]),cover(p<<1|1,cov[p]),cov[p]=-1;
	if(tag[p])
		rev(p<<1),rev(p<<1|1),tag[p]=0;
}
void upd_cover(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l)return;
	if(ql<=l && r<=qr){ cover(p,v); return; }
	int mid=(l+r)>>1; pushdown(p);
	upd_cover(l,mid,ql,qr,v,p<<1);
	upd_cover(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
void upd_rev(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return;
	if(ql<=l && r<=qr){ rev(p); return; }
	int mid=(l+r)>>1; pushdown(p);
	upd_rev(l,mid,ql,qr,p<<1);
	upd_rev(mid+1,r,ql,qr,p<<1|1);
	pushup(p);
}
Info query(int l,int r,int ql,int qr,int p){
	if(ql<=l&&r<=qr) return t[p];
	int mid=(l+r)>>1; pushdown(p);
	if(qr<=mid) return query(l,mid,ql,qr,p<<1);
	else if(mid<ql) return query(mid+1,r,ql,qr,p<<1|1);
	else return query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1);
}
void build(int l,int r,int p){
	if(l==r){
		t[p]=(Info){a[l],a[l],0};
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
}
void procedure(){
	memset(cov,-1,sizeof(cov));
	memset(tag,0,sizeof(tag));
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,n,1);
	while(m--){
		int op=read(),l=read(),r=read();
		if(op==1){
			int x=read();
			upd_cover(1,n,l,r,x,1);
		}else if(op==2){
			upd_rev(1,n,l,r,1);
		}else
			printf("%d\n", query(1,n,l,r,1).c);
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