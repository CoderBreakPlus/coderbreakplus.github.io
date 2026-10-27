// created time: 2026-10-27 07:58:29
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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

int n,m,k,fa[500005];
int u[500005],v[500005];
ll c[500005];

ll val[500005],cnt;
vector<pair<int,int>>vec[500005];

int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]); return fa[x];}

void procedure(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();
		val[++cnt]=c[u[i]]^c[v[i]];
	}
	sort(val+1,val+cnt+1);
	cnt=unique(val+1,val+cnt+1)-(val+1);

	ll ans=((1ll<<k)-cnt)%mod*qpow(2,n)%mod;
	for(int i=1;i<=m;i++){
		ll now=c[u[i]]^c[v[i]];
		int pos=lower_bound(val+1,val+cnt+1,now)-val;
		vec[pos].pb(u[i],v[i]);
	}
	for(int i=1;i<=cnt;i++){
		for(auto [u,v]:vec[i])fa[u]=u,fa[v]=v;

		int low=n;
		for(auto [u,v]:vec[i]){
			u=find(u),v=find(v);
			if(u!=v)low--,fa[u]=v;
		}
		addmod(ans+=qpow(2,low));
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