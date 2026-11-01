// created time: 2026-10-30 07:46:26
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
int n,m;
ll d0[200005],d1[200005];
vector<pair<int,int>>E[200005];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),c=read(),d=read();
		d0[u]+=c,d0[v]+=c;
		d1[u]+=d,d1[v]+=d;
		E[u].pb(v,d),E[v].pb(u,d);
	}
	set<pair<ll,int>>S;
	for(int i=1;i<=n;i++)S.emplace(d1[i],i);

	ll sum=0,ans=0;
	while(!S.empty()){
		auto [x,i]=*S.begin();
		S.erase(S.begin());
		chkmax(ans,x-sum),sum+=d0[i]-x;
		for(auto [j,d]:E[i]){
			if(!S.count({d1[j],j}))continue;
			S.erase({d1[j],j});
			d1[j]-=d;
			S.emplace(d1[j],j);
		}
	}
	printf("%lld\n",ans);
}
int main(){
	// #ifdef LOCAL
	// 	assert(freopen("test.in","r",stdin));
	// 	assert(freopen("test.out","w",stdout));
	// #endif
	assert(freopen("clear.in","r",stdin));
	assert(freopen("clear.out","w",stdout));
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}