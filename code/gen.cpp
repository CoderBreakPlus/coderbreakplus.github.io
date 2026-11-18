// created time: 2026-11-18 08:47:34
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

int n=5,p[55];

void procedure(){
	cout<<n<<endl;
	for(int i=1;i<=2*n;i++)p[i]=i;
	shuffle(p+1,p+2*n+1,rnd);
	
	for(int i=1;i<=n;i++){
		if(p[i]<p[i+n])swap(p[i],p[i+n]);
		cout<<p[i]<<" ";
	}
	cout<<endl;
	for(int i=1;i<=n;i++)
		cout<<p[i+n]<<" ";
	cout<<endl;
	cout<<n*(n-1)/2<<endl;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			cout<<i<<" "<<j<<endl;
}
int main(){
	assert(freopen("test.in","w",stdout));
	// math_init();
	int T=1;
	while(T--) procedure();
	return 0;
}