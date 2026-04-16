// created time: 2026-04-16 08:41:37
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

ll n=500000,q=100000,m=5;
ll a[500005],b[100005];

void procedure(){
	cout<<n<<" "<<q<<endl;
	for(ll i=1;i<=n;i++)a[i]=i;
	shuffle(a+1,a+n+1,rnd);
	for(ll i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	for(ll i=1;i<=q;i++){
		for(ll j=1;j<=2*m;j++) b[j]=rnd()%(n-2*m+1);

		sort(b+1,b+2*m+1);
		for(ll j=1;j<=2*m;j++) b[j]+=j;

		cout<<m<<endl;
		for(ll j=1;j<=m;j++) cout<<b[2*j-1]<<" "<<b[2*j]<<endl;
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}