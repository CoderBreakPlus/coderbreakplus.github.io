// created time: 2026-04-15 14:10:03
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

ll n,a[200005],b[200005],c[200005];
ll __lcm(ll x,ll y){
	return x/__gcd(x,y)*y;
}

ll vis[1000005],pr[1000005],t;
vector<ll>vec[1000005];

const ll B = 50;

void procedure(){
	n=read();
	for(ll i=1;i<=n;i++)a[i]=read();
	for(ll i=1;i<=n;i++)b[i]=read(),vec[i].clear();

	ll ans=0;
	for(ll i=1;i<=n;i++){
		ll sb=1;
		if(i>1) sb=__gcd(a[i-1],a[i]);
		if(i<n) sb=__lcm(sb, __gcd(a[i],a[i+1]));
		c[i]=sb;
	}
	for(ll i=1;i<=n;i++){
		if(b[i]<c[i])continue;

		if(a[i]>c[i]){
			ans++;
			a[i]=c[i];
			c[i]=0;
		}
	}
	for(ll i=1;i<=n;i++){
		if(b[i]<c[i]||!c[i]) continue;

		if(a[i]==c[i]) {
			// a[i]*k <= b[i] ==> k <= b[i]/c[i]
			// gcd(a[i-1],a[i]*k) == gcd(a[i-1],a[i])

			ll k=b[i]/c[i];

			ll val=1;
			if(i>1) val=__lcm(val,a[i-1]/__gcd(a[i-1],a[i]));
			if(i<n) val=__lcm(val,a[i+1]/__gcd(a[i+1],a[i]));

			ll sz=0;

			ll ban=0;
			if(vec[i-1].size()==1)
				ban=vec[i-1].back();

			for(ll w=1;w<=t && pr[w]<=k;w++)
				if(__gcd(pr[w],val)==1 && w!=ban){
					vec[i].pb(w);
					sz++;
					if(sz>=B)break;
				}

			if(vec[i].size()) ans++;
			else vec[i].clear();
		}
	}
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	for(ll i=2;i<=1e6;i++){
		if(!vis[i]) pr[++t]=i;
		for(ll j=2*i;j<=1e6;j+=i) vis[j]=1;
	}
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}