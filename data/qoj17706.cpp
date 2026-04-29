// created time: 2026-04-29 07:38:11
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

int n,m,k,s[100005],t[100005],c[100005];

void chkmin(pair<ll,int> &a,pair<ll,int> b){ a=min(a,b); }

pair<ll,int> dp[100005];
vector<pair<int,int>>e[100005];

pair<ll,int> tr[400005];
ll tag[400005];

inline void build(int l,int r,int p){
	tr[p]={1e18,0},tag[p]=0;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
}
inline void pushup(int p){
	tr[p]=min(tr[p<<1],tr[p<<1|1]);
}
inline void upd(int p,ll v){
	tr[p].fi+=v, tag[p]+=v;
}
inline void pushdown(int p){
	if(tag[p]){
		upd(p<<1, tag[p]);
		upd(p<<1|1, tag[p]);
		tag[p]=0;
	}
}
inline void update(int l,int r,int x,const pair<ll,int> &v,int p){
	if(l==r){
		chkmin(tr[p], v);
		return;
	}
	int mid=(l+r)>>1; pushdown(p);
	if(x<=mid) update(l,mid,x,v,p<<1);
	else update(mid+1,r,x,v,p<<1|1);
	pushup(p);
}
inline void modify(int l,int r,int ql,int qr,ll v,int p){
	if(r<ql || qr<l) return;
	if(ql<=l && r<=qr){
		upd(p, v);
		return;
	}
	int mid=(l+r)>>1; pushdown(p);
	modify(l,mid,ql,qr,v,p<<1),modify(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
inline pair<ll,int> check(ll x){
	build(0,n,1);update(0,n,0,{0,0},1);
	for(int i=1;i<=n;i++){
		dp[i]=tr[1]; dp[i].fi+=x, dp[i].se++;
		update(0,n,i,dp[i],1);
		for(auto [l,v]: e[i])
			modify(0,n,0,l-1,v,1);
	}
	return dp[n];
}
void procedure(){
	n=read(),m=read(),k=read()+1;
	for(int i=1;i<=m;i++){
		s[i]=read(),t[i]=read()-1,c[i]=read();
		e[t[i]].pb(s[i],c[i]);
	}	
	if(k>=n){
		puts("0");
		return;
	}
	ll l=0,r=1e14;
	int ok=0;
	while(l<=r){
		ok++;
		ll mid=(l+r)>>1;
		auto [val,cnt]=check(mid);
		if(check(mid).se<=k){
			r=mid-1;
		}else l=mid+1;
	}
	// cerr<<"ok="<<ok<<endl;
	auto [val,cnt]=check(l);
	printf("%lld\n",val-(ll)l*k);
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