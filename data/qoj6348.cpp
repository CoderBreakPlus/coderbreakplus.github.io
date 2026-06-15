// created time: 2026-06-15 07:22:53
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

int n; ll a[500005];
map<ll,pair<ll,ll>>mp;

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	if(n>200) n=min(n,200);

	for(int i=1;i<=n;i++){
		mp.clear();
		for(int j=1;j<=i;j++)
			for(int k=j+1;k<=i;k++)
				mp[a[k]/a[j]]={j,k};

		for(int j=i+1;j<=n;j++)
			for(int k=j+1;k<=n;k++)
				if(mp.count(a[k]/a[j])){
					puts("YES");
					printf("%d %d %d %d\n",mp[a[k]/a[j]].fi,mp[a[k]/a[j]].se,
						j,k);
					return;
				}
	}
	puts("NO");
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