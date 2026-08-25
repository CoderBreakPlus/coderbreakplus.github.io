// created time: 2026-08-25 18:33:55
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

int n,q,a[300005],buc[300005];

int rt[300005];
int lc[30000005],rc[30000005],val[30000005],cnt;

int clone(int x){
	++cnt;
	lc[cnt]=lc[x],rc[cnt]=rc[x],val[cnt]=val[x];
	return cnt;
}
void modify(int l,int r,int i,int j,int p1,int c1,int p2,int c2,int &p){
	if(j<l){ p=clone(p2); val[p]+=c2; return; }
	if(i<=l&&r<j){ p=clone(p1); val[p]+=c1+1; return; }
	if(l==r||r<i){ p=0; return; }

	p=++cnt;
	int mid=(l+r)>>1;
	modify(l,mid,i,j,lc[p1],c1+val[p1],lc[p2],c2+val[p2],lc[p]);
	modify(mid+1,r,i,j,rc[p1],c1+val[p1],rc[p2],c2+val[p2],rc[p]);
}
int query(int l,int r,int x,int p){
	if(!p)return 0;
	if(l==r)return val[p];
	int mid=(l+r)>>1;
	return val[p]+(x<=mid?query(l,mid,x,lc[p]):query(mid+1,r,x,rc[p]));
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read(),buc[i]=n+1;
	for(int i=n;i>=1;i--){
		modify(1,n,i,buc[a[i]],rt[i+1],0,rt[buc[a[i]]+1],0,rt[i]);
		buc[a[i]]=i;
	}
	int ans=0;
	while(q--){
		int l=read()^ans,r=read()^ans;
		printf("%d\n", ans=query(1,n,r,rt[l]));
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