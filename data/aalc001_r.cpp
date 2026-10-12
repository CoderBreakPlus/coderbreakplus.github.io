// created time: 2026-10-12 15:34:00
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
int n,w,q;
char init[100005][11];

struct dsu{
	char L[11],R[11];
	int fa[40],v0,v1,equal;
	dsu(){ for(int i=0;i<4*w;i++) fa[i]=i; v0=v1=equal=-1; }
	int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x];}
	void merge(int x,int y){ fa[find(x)]=find(y); }
}t[400005];

int buc[40];
dsu operator+ (const dsu &A,const dsu &B){
	dsu C,D;
	for(int i=0;i<2*w;i++) C.fa[i]=A.fa[i];
	for(int i=0;i<2*w;i++) C.fa[i+2*w]=B.fa[i]+2*w;
	for(int i=0;i<w;i++)if(A.R[i]==B.L[i])
		C.merge(A.fa[w+i],B.fa[i]+2*w);

	memcpy(D.L,A.L,sizeof(D.L));
	memcpy(D.R,B.R,sizeof(D.R));

	memset(buc,-1,sizeof(buc));
	for(int i=0;i<w;i++){
		int now=C.find(i);
		if(!~buc[now])buc[now]=i;
		D.fa[i]=buc[now];
	}
	for(int i=w;i<2*w;i++){
		int now=C.find(i+2*w);
		if(!~buc[now])buc[now]=i;
		D.fa[i]=buc[now];
	}

	if(~A.equal) D.equal = A.equal;
	else if(~B.equal) D.equal = B.equal;
	// cout<<"was "<<D.equal<<endl;

	if(~A.v0) D.v0=C.find(A.v0);
	if(~A.v1) D.v1=C.find(A.v1);
	if(~B.v0) D.v0=C.find(B.v0+2*w);
	if(~B.v1) D.v1=C.find(B.v1+2*w);

	if(~D.v0&&~D.v1&&D.v0==D.v1)D.equal=1;

	if(~D.v0) D.v0=buc[D.v0];
	if(~D.v1) D.v1=buc[D.v1];
	return D;
}
void pushup(int p){ t[p]=t[p<<1]+t[p<<1|1]; }
void locate(int p,char* s){
	t[p]=dsu();
	memcpy(t[p].L,s,sizeof(t[p].L));
	memcpy(t[p].R,s,sizeof(t[p].R));
	for(int i=0;i<w;i++)t[p].merge(i,i+w);
	for(int i=1;i<w;i++)
		if(t[p].L[i]==t[p].L[i-1]) t[p].merge(i-1,i);
}
void build(int l,int r,int p){
	if(l==r) return locate(p,init[l]);
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
}
void upd(int l,int r,int x,int p){
	if(l==r) return locate(p,init[l]);
	if(x<=mid) upd(l,mid,x,p<<1);
	else upd(mid+1,r,x,p<<1|1);
	pushup(p);
}
void del(int l,int r,int x,int p){
	if(l==r){ t[p].v0=t[p].v1=-1; return; }
	if(x<=mid) del(l,mid,x,p<<1);
	else del(mid+1,r,x,p<<1|1);
	pushup(p);
}
void fuck0(int l,int r,int x,int c,int p){
	if(l==r){ t[p].v0=t[p].find(c); return; }
	if(x<=mid) fuck0(l,mid,x,c,p<<1);
	else fuck0(mid+1,r,x,c,p<<1|1);
	pushup(p);
}
void fuck1(int l,int r,int x,int c,int p){
	if(l==r){ t[p].v1=t[p].find(c); return; }
	if(x<=mid) fuck1(l,mid,x,c,p<<1);
	else fuck1(mid+1,r,x,c,p<<1|1);
	pushup(p);
}
void print(int l,int r,int p){
	if(l==r) return;
	cout<<"here "<<l<<"->"<<r<<" "<<t[p].L<<" "<<t[p].R<<endl;
	cout<<"two node "<<t[p].v0<<" "<<t[p].v1<<" equal="<<t[p].equal<<endl;
	for(int i=0;i<w;i++) cout<<t[p].find(i)<<" "; cout<<endl;
	for(int i=0;i<w;i++) cout<<t[p].find(i+w)<<" "; cout<<endl;
	
	print(l,mid,p<<1),print(mid+1,r,p<<1|1);
}


void procedure(){
	n=read(),w=read(),q=read();
	for(int i=1;i<=n;i++) scanf("%s",init[i]);
	build(1,n,1);
	while(q--){
		int o=read();
		if(o==1){
			int i=read();
			scanf("%s",init[i]);
			upd(1,n,i,1);
		}else{
			int a=read(),b=read()-1,c=read(),d=read()-1;
			if(a>c)swap(a,c),swap(b,d);

			int base=0;
			if(a==c){
				if(b>d)swap(b,d);
				base=1;
				for(int i=b+1;i<=d;i++)base&=(init[a][i]==init[a][i-1]);
			}
			fuck0(1,n,a,b,1),fuck1(1,n,c,d,1);
			// print(1,n,1);
			puts((base||t[1].equal==1)?"Yes":"No");
			del(1,n,a,1),del(1,n,c,1);
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