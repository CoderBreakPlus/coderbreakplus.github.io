// created time: 2026-10-12 14:31:39
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
const uint M = ((1u<<30)-1);
int n,q,a[200005];
struct Info{
	uint a,a2,b;
}t[800005];
Info operator+ (const Info &A, const Info &B){
	Info C;
	C.a=B.a2^((~A.a)&B.b);
	C.a2=B.a2^((~A.a2)&B.b);
	C.b=(A.b&B.b);
	return C;
}
void pushup(int p){ t[p]=t[p<<1]+t[p<<1|1]; }

void update(int l,int r,int x,uint y,int p){
	if(l==r){
		t[p].a=y,t[p].b=~y,t[p].a2=0;
		return;
	}
	if(x<=mid) update(l,mid,x,y,p<<1);
	else update(mid+1,r,x,y,p<<1|1);
	pushup(p);
}
Info query(int l,int r,int ql,int qr,int p){
	if(ql<=l&&r<=qr) return t[p];
	if(qr<=mid) return query(l,mid,ql,qr,p<<1);
	else if(mid<ql) return query(mid+1,r,ql,qr,p<<1|1);
	else return query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1);
}
void build(int l,int r,int p){
	if(l==r){
		t[p].a=a[l],t[p].b=~a[l],t[p].a2=0;
		return;
	}
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
	// cout<<"here "<<l<<"->"<<r<<" info = "<<(t[p].a&M)<<" "<<(t[p].a2&M)<<" "<<(t[p].b&M)<<endl;
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=~read();
	build(1,n,1);
	while(q--){
		int op=read(),l=read(),r=read();
		if(op==1){
			update(1,n,l,~r,1);
		}else{
			printf("%u\n",(~query(1,n,l,r,1).a)&M);
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