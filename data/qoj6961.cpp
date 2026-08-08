// created time: 2026-08-03
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

ll n,a[1<<18];

ll b[50];
map<ll,ll>mp;
void procedure(){
	n=read();
	memset(b,0,sizeof(b));
	mp.clear();
	mp[0]++;
	for(ll i=1;i<(1<<n);i++)a[i]=read(),mp[a[i]]++;
	sort(a+1,a+(1<<n));

	vector<ll>ans;
	for(ll i=1;i<(1<<n);i++){
		ll w=a[i],v=0;
		for(ll x=0;x<30;x++){
			if((~w)>>x&1)continue;
			if(b[x]) w^=b[x];
			else {
				b[x]=w;
				v=1; break;
			}
		}
		if(v) ans.pb(a[i]);
	}
	if(ans.size()>n){ puts("-1"); return; }

	ll d=n-ans.size();
	for(auto [x,y]: mp){
		if(y!=(1ll<<d)){ puts("-1"); return; } 
	}
	while(d--) printf("0 ");
	for(auto x:ans)printf("%lld ",x);puts("");
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