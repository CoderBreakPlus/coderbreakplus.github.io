// created time: 2026-05-12 16:12:39
// https://qoj.ac/contest/1906/problem/10074
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

int n,u[200005],v[200005],p[200005];
vector<int>E[200005];

int val[800005],cnt[800005],tag[800005];
void upd(int p,int v){
	val[p]+=v,tag[p]+=v;
}
void pushup(int p){
	val[p]=min(val[p<<1],val[p<<1|1]),cnt[p]=0;
	if(val[p<<1]==val[p])cnt[p]+=cnt[p<<1];
	if(val[p<<1|1]==val[p])cnt[p]+=cnt[p<<1|1];
}
void pushdown(int p){
	if(tag[p]){
		upd(p<<1, tag[p]);
		upd(p<<1|1, tag[p]);
		tag[p]=0;
	}
}
void update(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l) return;
	if(ql<=l && r<=qr) {upd(p,v); return;}
	int mid=(l+r)>>1;pushdown(p);
	update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
void build(int l,int r,int p){
	if(l==r){
		cnt[p]=1;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
}
void procedure(){
	n=read();
	for(int i=1;i<n;i++){
		u[i]=read(),v[i]=read();
	}
	for(int i=1;i<=n;i++)p[read()]=i;
	for(int i=1;i<n;i++){
		u[i]=p[u[i]],v[i]=p[v[i]];
		if(u[i]>v[i])swap(u[i],v[i]);
		// cout<<"link "<<u[i]<<" "<<v[i]<<endl;
		E[v[i]].pb(u[i]);
	}
	ll ans=0;
	build(1,n,1);
	update(1,n,1,n,2*n,1);
	for(int i=1;i<=n;i++){
		update(1,n,i,i,-2*n,1);
		update(1,n,1,i,1,1);
		for(auto j:E[i]) update(1,n,1,j,-1,1);

		// cout<<val[1]<<" "<<cnt[1]<<endl;
		if(val[1]==1)ans+=cnt[1];
	}
	printf("%lld\n",ans);
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