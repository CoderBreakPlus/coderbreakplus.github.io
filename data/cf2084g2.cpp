// created time: 2026-04-23 09:46:24
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
mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
int n,a[500005];

int lc[500005],rc[500005],k[500005],sz[500005],rt;
ll t1[500005],t2[500005],val[500005],v0,v1;

int cnt;

int newnode(){
	int x=++cnt;
	lc[x]=rc[x]=t1[x]=t2[x]=val[x]=0,k[x]=rnd(),sz[x]=1;
	return x;
}
void upd(int x,ll s1,ll s2){
	if(x){
		t1[x]+=s1, t2[x]+=s2;
		val[x]+=s1+sz[lc[x]]*s2;
	}
}
void pushdown(int x){
	upd(lc[x],t1[x],t2[x]);
	upd(rc[x],t1[x]+t2[x]*(sz[lc[x]]+1),t2[x]);
	t1[x]=t2[x]=0;
}
void pushup(int x){
	sz[x]=sz[lc[x]]+sz[rc[x]]+1;
}
int merge(int x,int y){
	if(!x || !y) return x^y;
	pushdown(x),pushdown(y);
	if(k[x]<k[y]){
		rc[x]=merge(rc[x],y);
		return pushup(x),x;
	}else{
		lc[y]=merge(x,lc[y]);
		return pushup(y),y;
	}
}
void split(int x,int &a,int &b){
	if(!x){ a=b=0; return; }
	pushdown(x);
	if(val[x]>=0) {
		a=x;
		split(rc[x],rc[x],b);
	}else{
		b=x;
		split(lc[x],a,lc[x]);
	}
	pushup(x);
}
vector<ll>vec;
void divide(int x){
	if(!x)return;
	pushdown(x);
	divide(rc[x]);
	vec.pb(val[x]);
	divide(lc[x]);
}
void procedure(){	
	n=read(); cnt=0;
	for(int i=1;i<=n;i++)a[i]=0;
	for(int i=1;i<=n;i++){
		a[read()]=i;
	}	
	v0=v1=rt=0;

	ll s=(n+1)/2,t=n/2;
	for(ll i=1;i<=n;i++){
		if(!a[i]){
			int l,r;
			split(rt,l,r);
			rt=merge(merge(l,newnode()),r);
		}else if(a[i]&1) v0++;

		ll cf0=i*t-i*i;
		ll cf1=s+2*i-t;
		ll cf2=-2;

		v1+=cf2*v0*v0+cf1*v0+cf0;
		upd(rt, cf2*(2*v0+1)+cf1, 2*cf2);
	}
	ll ans=v1;
	for(ll i=1;i<=n;i++) ans+=i*(n-i+1);
	divide(rt);
	
	s-=v0;
	while(s--) ans+=vec.back(),vec.pop_back();
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}