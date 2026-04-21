// created time: 2026-04-21 14:55:13
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

ll n,m,fa[200005],dep[200005],sz[200005],sb[200005];
vector<ll>E[200005];
map<ll,ll>s[200005];
void procedure(){
	n=read(),m=read();
	for(ll i=1;i<n;i++) fa[i]=i+1; fa[n]=0;
	for(ll i=1;i<=n;i++) E[i].clear();
	for(ll i=1;i<=m;i++){
		ll u=read(),v=read();
		fa[u]=max(fa[u],v);
	}
	dep[n]=0;
	map<ll,ll>mp;
	for(ll i=n-1;i>=1;i--){
		dep[i]=dep[fa[i]]+1;
		// cout<<i<<" dep="<<dep[i]<<endl;
		E[fa[i]].pb(i);
	}
	for(ll i=1;i<=n;i++) sb[i]=dep[i],mp[dep[i]]++;
	sort(sb+1,sb+n+1);

	
	ll ans=0;
	for(ll i=1;i<=n;i++){
		ans+=sb[i]*(n-i+1);
	}
	for(auto [x,y]:mp) ans+=x*(y*(y-1)/2);

	for(ll i=1;i<=n;i++){
		sz[i]=1;
		ll cnt=0;
		for(auto y:E[i]){
			sz[i]+=sz[y];
			cnt-=sz[y]*(sz[y]+1)/2;
		}
		cnt+=sz[i]*(sz[i]+1)/2;
		ans-=dep[i]*cnt;
		s[i].clear(); s[i][dep[i]]=1;
	}

	for(ll i=1;i<=n;i++){
		ll cnt=0;
		for(auto j:E[i]){
			if(s[i].size()<s[j].size())swap(s[i],s[j]);
			for(auto [x,y]: s[j]){
				cnt+=s[i][x]*y;
				s[i][x]+=y;
			}
			s[j].clear();
		}
		ans-=dep[i]*cnt;
	}
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