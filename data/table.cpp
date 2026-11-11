// created time: 2026-11-11 10:16:24
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

int n,k;
set<int>S;

void dfs(int x){
	if(S.count(x))return;
	S.emplace(x);
	for(int i=0;i<n;i++)if((x>>i)&1){
		int y=x^(1<<i);
		if(i>=2)y|=(1<<i-2);
		if(i+k<n)y|=(1<<i+k);
		dfs(y);
	}
}
void brute(int n,int k){
	::n=n,::k=k;
	S.clear();
	dfs((1<<n)-1);

	for(int x:S){
		for(int i=0;i<n;i++)putchar('0'+((x>>i)&1));
		puts("");
	}
}
void procedure(){
	int n=read(),k=read();
	brute(n,k);
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