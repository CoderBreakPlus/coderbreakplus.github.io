// created time: 2026-04-18 10:46:10
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

int n=8;

void procedure(){
	cout<<n<<endl;
	int cnt=0;
	for(int i=1;i<=n;i++){
		int x=max(0ll,rng(-5,2));
		if(i==n&&!cnt) x=rng(1,2);
		cout<<x;
		cnt+=x;
	}
	cout<<endl;
	cnt=0;
	for(int i=1;i<=n;i++){
		int x=max(0ll,rng(-5,2));
		if(i==n&&!cnt) x=rng(1,2);
		cout<<x;
		cnt+=x;
	}
	cout<<endl;
	cout<<rng(1,n)<<endl;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","w",stdout));
	#endif
	ll T=1; cout<<T<<endl;
	// math_init();
	while(T--) procedure();
	return 0;
}