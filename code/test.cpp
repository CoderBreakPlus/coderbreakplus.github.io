// created time: 2026-10-30 08:01:53
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

int n = 6;
int a[55],p[55];
map<vector<int>,int>mp;
void procedure(){
	for(int i=1;i<=n;i++)p[i]=i;
	do{
		for(int i=1;i<=n;i++)a[i]=i;
		for(int i=1;i<=n;i++)
			swap(a[p[i]],a[p[i]%n+1]);
		mp[vector<int>(a+1,a+n+1)]++;
		// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	}while(next_permutation(p+1,p+n+1));
	for(auto [v,cnt]:mp){
		for(int x:v) cout<<x<<" ";
		cout<<"cnt="<<cnt<<endl;
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