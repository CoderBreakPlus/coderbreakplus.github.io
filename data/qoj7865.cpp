// created time: 2026-04-02 15:21:15
// I. Refresher into Midas
// https://qoj.ac/contest/1459/problem/7865
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
int a,b,m;
int dp[10000005],f[10000005];

void procedure(){
	a=read(),b=read(),m=read();
	if(m==0){
		puts("320");
		return;
	}
	int ans=0;
	
	for(int i=0;i<a;i++) f[i]=0;
	int val=0,id=0;
	
	for(int i=0;i<=m;i++){
		dp[i]=1;
		if(i>=b){
			int pos=(i-b)%a;
			f[pos]=max(f[pos],dp[i-b]-(i-b)/a);
			if(f[pos]>val){
				val=f[pos],id=pos;
			}else if(f[pos]==val) id=min(id,pos);
		}
		if(id<=i%a) dp[i]=max(dp[i],val+1);
		else dp[i]=max(dp[i],val);

		dp[i]+=i/a;
		ans=max(ans,dp[i]+1+(m-i)/a);
	}

	printf("%lld\n",160ll*ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}