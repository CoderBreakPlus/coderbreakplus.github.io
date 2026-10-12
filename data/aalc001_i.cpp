// created time: 2026-10-12 13:36:49
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
int n,q,a[100005];
struct Seg{
	int l,r; ll v;
	Seg(){ }
	Seg(int L,int R,ll V){ l=L,r=R,v=V; }
};
bool operator< (const Seg &A,const Seg &B){ return A.v<B.v;  }
Seg operator+ (const Seg &A,const Seg &B){ return Seg(A.l,B.r,A.v+B.v); }

struct Info{
	Seg ls,rs,mx,sum;
	Info(){ }
	Info(Seg A,Seg B,Seg C,Seg D){ ls=A,rs=B,mx=C,sum=D; }
}t[400005][2];
Info operator+ (const Info &A,const Info &B){
	return Info(max(A.ls,A.sum+B.ls),max(B.rs,A.rs+B.sum),max({A.mx,B.mx,A.rs+B.ls}),A.sum+B.sum);
}
bool tag[400005];

void pushup(int p){ for(int o:{0,1}) t[p][o]=t[p<<1][o]+t[p<<1|1][o]; }
void upd(int p){ tag[p]^=1; swap(t[p][0],t[p][1]); }
void build(int l,int r,int p){
	if(l==r){
		Seg pos=Seg(l,l,a[l]),neg=Seg(l,l,-a[l]);
		t[p][0]={pos,pos,pos,pos},t[p][1]={neg,neg,neg,neg};
		return;
	}
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
}
void pushdown(int p){
	if(tag[p])
		upd(p<<1),upd(p<<1|1),tag[p]=0;
}
void update(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr) return upd(p);
	pushdown(p);
	update(l,mid,ql,qr,p<<1),update(mid+1,r,ql,qr,p<<1|1);
	pushup(p);
}
void modify(int l,int r,int x,int v,int p){
	if(l==r){
		a[l]=v;
		Seg pos=Seg(l,l,a[l]),neg=Seg(l,l,-a[l]);
		t[p][0]={pos,pos,pos,pos},t[p][1]={neg,neg,neg,neg};
		return;
	}
	pushdown(p);
	if(x<=mid) modify(l,mid,x,v,p<<1);
	else modify(mid+1,r,x,v,p<<1|1);
	pushup(p);
}
Info query(int l,int r,int ql,int qr,int p){
	if(ql<=l&&r<=qr) return t[p][0];
	pushdown(p);
	if(qr<=mid) return query(l,mid,ql,qr,p<<1);
	else if(mid<ql) return query(mid+1,r,ql,qr,p<<1|1);
	else return query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1);
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	build(1,n,1);
	// cout<<"done"<<endl;
	
	while(q--){
		int op=read();
		if(op==1){
			int x=read(),y=read();
			modify(1,n,x,y,1);
		}else{
			int l=read(),r=read();
			auto [L,R,V]=query(1,n,l,r,1).mx;
			// cout<<"here "<<L<<" "<<R<<" "<<V<<endl;
			if(V<=0){
				puts("0");
				continue;
			}

			update(1,n,L,R,1);
			printf("%lld\n",V+max(0ll,query(1,n,l,r,1).mx.v));
			update(1,n,L,R,1);
		}
	}
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