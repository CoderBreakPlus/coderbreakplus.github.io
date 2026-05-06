// created time: 2026-05-06 10:39:24
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

int n;
ll a[500005],b[500005],c[1000005];

void procedure(){
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();
	for(int i=1;i<=2*n+1;i++)c[i]=read();

	ll bef=c[1],ans=1e18;
	for(int i=1;i<=n;i++){
		bef=min(bef, b[i]);bef+=c[2*i];
		ans=min(ans, bef+a[i]);
		if(i==n)ans=min(ans, bef+c[2*n+1]);
		bef+=c[2*i+1];
	}
	bef=a[1];
	for(int i=2;i<=n;i++){
		bef+=c[2*i-1];
		ans=min(ans, bef+b[i]);

		bef+=c[2*i];
		bef=min(bef,a[i]);
	}
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	while(scanf("%d",&n)!=EOF) procedure();
	return 0;
}