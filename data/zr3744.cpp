// created time: 2026-11-14 10:08:56
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

int n,a[200005];
int ABS(int x){ return max(x,-x); }
typedef pair<ll,int> P;

P f[2][200005];

inline int reduce(int x){ return x>=mod?x-mod:x; }
inline P merge(const P &A,const P &B){
	if(A.fi==B.fi) return {A.fi, reduce(A.se+B.se)};
	else return A.fi<B.fi?A:B;
}

struct Seg{
	P t[800005];
	ll tag[800005];
	Seg(){
		for(int i=0;i<=8e5;i++)t[i]={1e18,0};
	}
	void pushup(int p){
		t[p]=merge(t[p<<1],t[p<<1|1]);
	}
	void upd(int p,ll v){
		t[p].fi+=v;
		tag[p]+=v;
	}
	void pushdown(int p){
		if(tag[p]){
			upd(p<<1,tag[p]);
			upd(p<<1|1,tag[p]);
			tag[p]=0;
		}
	}
	P query(int l,int r,int ql,int qr,int p){
		if(r<ql||qr<l)return {1e18,0};
		if(ql<=l&&r<=qr)return t[p];
		int mid=(l+r)>>1;
		pushdown(p);
		return merge(query(l,mid,ql,qr,p<<1),query(mid+1,r,ql,qr,p<<1|1));
	}
	void modify(int l,int r,int x,P v,int p){
		if(l==r){
			t[p]=v;
			return;
		}
		int mid=(l+r)>>1;pushdown(p);
		if(x<=mid)modify(l,mid,x,v,p<<1);
		else modify(mid+1,r,x,v,p<<1|1);
		pushup(p);
	}
	// void update(int l,int r,int ql,int qr,ll v,int p){
	// 	if(r<ql||qr<l)return;
	// 	if(ql<=l&&r<=qr){tag[p]+=v;return;}
	// 	int mid=(l+r)>>1;pushdown(p);
	// 	if(x<=mid)update(l,mid,ql,qr,v,p<<1);
	// 	else update(mid+1,r,ql,qr,v,p<<1|1);
	// 	pushup(p);
	// }
}S0[2],S1[2];

void upd(P &A, P B){
	if(B.fi<A.fi)A=B;
	else if(B.fi==A.fi)addmod(A.se+=B.se);
}

void modify(int i){
	S0[0].modify(1,n,i,{f[0][i].fi+i,f[0][i].se},1);
	S0[1].modify(1,n,i,{f[0][i].fi-i,f[0][i].se},1);

	S1[0].modify(1,n,a[i],{f[1][i].fi+a[i],f[1][i].se},1);
	S1[1].modify(1,n,a[i],{f[1][i].fi-a[i],f[1][i].se},1);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	if(n==1){
		puts("0 1");
		return;
	}
	a[0]=a[1];

	f[0][0]={1e18,0};
	f[1][0]={0,1};
	// modify(0);

	for(int i=2;i<=n;i++){
		// go diff
		// f[0][i-1].fi=f[1][i-1].fi=1e18;
		// for(int j=0;j<i-1;j++){
		// 	upd(f[0][i-1], {f[1][j].fi+ABS(i-a[j]), f[1][j].se});
		// 	upd(f[1][i-1], {f[0][j].fi+ABS(j-a[i]), f[0][j].se});
		// }
		{
			P s1=S1[0].query(1,n,i+1,n,1);s1.fi-=i;
			P s2=S1[1].query(1,n,1,i,1);s2.fi+=i;
			f[0][i-1]=merge(merge(s1,s2),{f[1][0].fi+ABS(i-a[0]), f[1][0].se});
		}
		{
			P s1=S0[0].query(1,n,a[i]+1,n,1);s1.fi-=a[i];
			P s2=S0[1].query(1,n,1,a[i],1);s2.fi+=a[i];
			f[1][i-1]=merge(merge(s1,s2),{f[0][0].fi+ABS(0-a[i]), f[0][0].se});
		}

		// go same
		S0[0].upd(1,ABS(i-a[i-1]));
		S0[1].upd(1,ABS(i-a[i-1]));
		S1[0].upd(1,ABS(i-1-a[i]));
		S1[1].upd(1,ABS(i-1-a[i]));

		modify(i-1);
		// for(int j=0;j<i-1;j++){
			f[0][0].fi+=ABS(i-a[i-1]);
			f[1][0].fi+=ABS(i-1-a[i]);
		// }
	}
	P s1=S0[0].query(1,n,a[n]+1,n,1);s1.fi-=a[n];
	P s2=S0[1].query(1,n,1,a[n],1);s2.fi+=a[n];
	
	P ans=merge(s1,s2);
	// for(int i=1;i<n;i++)
	// 	upd(ans,{f[0][i].fi+ABS(i-a[n]),f[0][i].se});
	printf("%lld %d\n",ans.fi,ans.se);
}
int main(){
	assert(freopen("bandtree.in","r",stdin));
	assert(freopen("bandtree.out","w",stdout));
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}