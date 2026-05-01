// created time: 2026-05-01
// https://www.luogu.com.cn/problem/P16394
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };

ll n,k,K,a[100005],vis[100005],rd[100005];
void procedure(){
	n=read(),k=K=read();
	if(k>(ll)(n-1)*(n-1)||k<(ll)n*(n-1)/2){
		puts("-1");
		return;
	}
	ll now=n;
	for(ll i=1;i<=n;i++) vis[i]=0;
	a[1]=1; vis[1]=1;
	for(ll i=n;i>=2;i--){
		while(k-(now-1)<(i-1)*(i-2)/2) now--;
		k-=(now-1);
		a[i]=now,vis[now]=1;
	}
	// for(ll i=1;i<=n;i++) printf("%lld ",a[i]);puts("");

	ll pt=1;
	for(ll i=1;i<=n;i++) rd[i]=(a[i]==a[i-1]);
	for(ll i=1;i<=n;i++){
		if(rd[i]){
			while(vis[pt])pt++;
			a[i]=pt++;
		}
	}
	ll ok=0,sb=0;
	for(ll i=1;i<=n;i++){
		printf("%lld ",a[i]); 
		sb=max(sb,a[i]);
		ok+=sb-1;
	}
	assert(ok==K);
	puts("");

	ok=0, sb=n;
	for(ll i=1;i<=n;i++){
		printf("%lld ",n-a[i]+1);
		sb=min(sb,n-a[i]+1);
		ok+=n-sb;
	}
	assert(ok==K);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}