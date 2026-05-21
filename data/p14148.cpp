// created time: 2026-05-21 19:21:17
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

int n,k,p[1000005];

void procedure(){
	n=read(),k=read();
	if(n==1){
		puts("-1");
		return;
	}
	for(int i=1;i<=n;i++)p[i]=i;
	shuffle(p+1,p+n+1,rnd);
	
	int val=0;
	for(int i=1;i<=n;i++)val^=(p[i]+k*i);

	int T=3e7;
	while(val&&T--){
		int x=rnd()%(n-1)+1;
		val^=(p[x]+k*x)^(p[x+1]+k*(x+1));
		swap(p[x],p[x+1]);
		val^=(p[x]+k*x)^(p[x+1]+k*(x+1));
	}
	if(val){puts("-1");}
	else{
		for(int i=1;i<=n;i++)printf("%d ",p[i]);
		puts("");
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}