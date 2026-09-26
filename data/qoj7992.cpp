// created time: 2026-09-24 09:46:22
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

int n,q,a[200005];
const int M=19;
uint C[200005][M+1];

struct Node{
	int len;
	uint a[M+1];
	Node(){ memset(a,0,sizeof(a));len=0; }
	uint& operator[](int x){ return a[x]; }
	const uint& operator[](int x)const{ return a[x]; }
}t[800005];
uint tag[800005];
inline Node operator+ (const Node &A,const Node &B){
	Node C;
	C.len=A.len+B.len;
	for(int i=0;i<=min(M,A.len);i++)
		for(int j=0;j<=min(M-i,B.len);j++)
			C[i+j]+=A[i]*B[j];
	return C;
}
void pushup(int p){
	t[p]=t[p<<1]+t[p<<1|1];
}
void upd(int p,uint v){
	tag[p]+=v;
	for(int i=0;i<min(M,t[p].len);i++){
		uint k=1;
		for(int j=i+1;j<=min(M,t[p].len);j++){
			k*=v;
			t[p][i]+=t[p][j]*C[j][i]*k;
		}
	}
}
void pushdown(int p){
	if(tag[p]){
		upd(p<<1,tag[p]);
		upd(p<<1|1,tag[p]);
		tag[p]=0;
	}
}
#define mid ((l+r)>>1)
void update(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr) {upd(p,v);return;}
	pushdown(p);
	update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
Node tmp;
void query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){ tmp=tmp+t[p]; return;}
	pushdown(p);
	query(l,mid,ql,qr,p<<1),query(mid+1,r,ql,qr,p<<1|1);
	pushup(p);
}
void build(int l,int r,int p){
	if(l==r){
		t[p].len=1;
		t[p][0]=a[l],t[p][1]=1;
		return;
	}
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	build(1,n,1);
	while(q--){
		int o=read();
		if(o==1){
			int l=read(),r=read(),x=read();
			update(1,n,l,r,x,1);
		}else{
			int l=read(),r=read();
			tmp=Node(); tmp[0]=1;
			query(1,n,l,r,1);
			printf("%u\n",tmp[0]&1048575u);
		}
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	for(int i=0;i<=M;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}