// created time: 2026-10-12 15:02:22
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

int n,q;
vector<tuple<int,int,int>>vec[200005];

int tag[1600005],sum[1600005],val[1600005];

void pushup(int p){
	if(tag[p]){
		val[p]=sum[p];
	}else{
		addmod(val[p]=val[p<<1]+val[p<<1|1]);
	}
}
void update(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr){
		tag[p]+=v;
		pushup(p);
		return;
	}
	update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
void build(int l,int r,int p){
	if(l==r){ sum[p]=l; return; }
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	addmod(sum[p]=sum[p<<1]+sum[p<<1|1]);
}

void procedure(){
	n=read(),q=read();
	build(1,n,1);
	for(int i=1;i<=q;i++){
		int a=read(),b=read(),c=read(),d=read();
		vec[a].pb(b,d,1);
		vec[c+1].pb(b,d,-1);
	}
	int ans=0;
	for(int i=1;i<=n;i++){
		for(auto [l,r,v]: vec[i]) update(1,n,l,r,v,1);
		ans=(ans+(ull)i*(sum[1]+mod-val[1]))%mod;
	}
	printf("%d\n",ans);
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