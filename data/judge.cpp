// created time: 2026-09-16 18:37:09
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

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int a[105];
void procedure(){
	int n = rng(1,8), sum = 0, now = 0, sig = 0;
	for(int i=1;i<=n;i++) sum+=(a[i]=rng(1,5));
	for(int i=1;i<=n;i++){
		now = max(0, a[i]-now);
		sig += now;
	}
	bool f1 = (2 * sig == sum);
	bool f2 = 1;

	now = 0;
	for(int i=1;i<=n;i++){
		if(i&1){
			now -= a[i];
			f2 &= (now <= 0);
		}else{
			now += a[i];
			f2 &= (now >= 0);
		}
	}
	f2 &= (now == 0);

	if(n&1){
		now = 0;
		for(int i=n-1;i>=2;i-=2){
			now += a[i]-a[i+1];
			f2 &= (now >= 0);
		}
	}
	if(f1 != f2){
		for(int i=1;i<=n;i++) cout<<a[i]<<" ";
		cout<<endl;
		exit(0);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1000000;
	// math_init();
	for(int i=1;i<=T;i++){
		procedure();
		if(i%1000==0) cout<<"checked "<<i<<endl;
	}
	return 0;
}