// created time: 2026-09-05
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

ll n,m,u[200005],v[200005],l[200005];
struct dsu{
	ll fa[200005],sz[200005];
	ll find(ll x){if(x!=fa[x])fa[x]=find(fa[x]);return fa[x];}
	void merge(ll x,ll y){
		x=find(x),y=find(y);
		if(x==y)return;
		fa[x]=y,sz[y]+=sz[x];
	}
	void init(){
		for(ll i=1;i<=n;i++)fa[i]=i,sz[i]=1;
	}
}d1,d2,d3;

map<pair<ll,ll>,ll>mp;
void procedure(){
	n=read(),m=read();
	d1.init(),d2.init(),d3.init();
	for(ll i=1;i<=m;i++){
		u[i]=read(),v[i]=read(),l[i]=read();
		if(l[i]==1)d1.merge(u[i],v[i]);
		if(l[i]==2)d2.merge(u[i],v[i]);
		if(l[i]==3)d3.merge(u[i],v[i]);
	}
	mp.clear();

	for(ll i=1;i<=n;i++){
		if(mp.count({d2.find(i),d3.find(i)})){
			d1.merge(i,mp[{d2.find(i),d3.find(i)}]);
		}else mp[{d2.find(i),d3.find(i)}]=i;
	}
	printf("%lld\n",d1.sz[d1.find(1)]);
	for(ll i=1;i<=n;i++)
		if(d1.find(i)==d1.find(1))printf("%lld ",i);
	puts("");
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