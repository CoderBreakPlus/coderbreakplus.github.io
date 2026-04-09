// created time: 2026-04-09 13:27:41
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

int n,a[100005],u[100005],v[100005];
vector<pair<int,int>>e[100005];

int fa[100005],sz[100005];
ll tot;

int find(int x){ if(x!=fa[x]) fa[x]=find(fa[x]); return fa[x]; }

void merge(int x,int y,int f){
	x=find(x),y=find(y);
	assert(x!=y);
	if(f){
		tot-=(ll)sz[x]*(sz[x]-1)/2;
		tot-=(ll)sz[y]*(sz[y]-1)/2;
	}
	fa[x]=y; sz[y]+=sz[x];
	if(f) tot+=(ll)sz[y]*(sz[y]-1)/2;
}
void procedure(){
	n=read();
	for(int i=1;i<n;i++){
		u[i]=read(),v[i]=read();
	}
	for(int i=1;i<=n;i++){
		a[i]=read();
	}
	for(int i=1;i<n;i++){
		int d=__gcd(a[u[i]],a[v[i]]);
		e[d].pb(u[i],v[i]);
	}
	iota(fa+1, fa+n+1, 1);
	fill(sz+1, sz+n+1, 1);

	int ans=0;
	for(int t=1;t<=n;t++){
		for(int x=t;x<=n;x+=t)
			for(auto [p,q]: e[x])
				if(a[p]!=t && a[q]!=t) merge(p,q,0);
		tot=0;
		for(int x=t;x<=n;x+=t)
			for(auto [p,q]: e[x])
				if(a[p]==t || a[q]==t) merge(p,q,1);
		ans=(ans+tot%mod*t)%mod;

		for(int x=t;x<=n;x+=t)
			for(auto [p,q]: e[x]) fa[p]=p,sz[p]=1,fa[q]=q,sz[q]=1;
	}
	printf("%d\n",1ull*ans*INV(1ll*n*(n-1)/2%mod)%mod);

	for(int i=1;i<=n;i++){
		e[i].clear();
		fa[i]=i,sz[i]=1;
	}
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