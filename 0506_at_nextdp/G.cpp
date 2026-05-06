// created time: 2026-05-05 13:11:42
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,q,a[100005];
struct Node{
	ll ls,rs,sum,val;
}t[400005];

Node operator+(const Node &A,const Node &B){
	Node C;
	C.ls=max(A.ls,A.sum+B.ls);
	C.rs=max(B.rs,B.sum+A.rs);
	C.sum=A.sum+B.sum;
	C.val=max({A.val,B.val,A.rs+B.ls});
	return C;
}
void pushup(int p){
	t[p]=t[p<<1]+t[p<<1|1];
}
void update(int l,int r,int x,int v,int p){
	if(l==r){
		t[p].ls=t[p].rs=t[p].sum=v;
		t[p].val=max(v,0);
		return;
	}
	int mid=(l+r)>>1;
	if(x<=mid)update(l,mid,x,v,p<<1);
	else update(mid+1,r,x,v,p<<1|1);
	pushup(p);
}
void procedure(){
	n=read(),q=read();
	ll sum=0;
	for(int i=1;i<=n;i++)
		a[i]=read(),sum+=a[i],update(1,n,i,a[i]?a[i]:-1,1);

	// cout<<t[1].val<<endl;
	while(q--){
		int i=read(),v=read();
		sum-=a[i]; a[i]=v; sum+=a[i];
		update(1,n,i,a[i]?a[i]:-1,1);
		printf("%lld\n",sum-t[1].val);
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