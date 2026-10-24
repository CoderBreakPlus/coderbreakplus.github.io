// created time: 2026-10-23 18:08:37
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
const int B = 40;
ll s,b,dp[B+5][B+5];

void procedure(){
	s=read(),b=read();
	int x=lg2(2*b-1);
	if(s>x) {
		printf("%lld\n",s-x-1);
		return;
	}

	ll L=1,R=b,ans=b;
	while(L<=R){
		ll mid=(L+R)>>1;

		ll cnt=0;
		for(ll x=1;(b-1)/x;x<<=1)cnt+=(mid<=(b-1)/x);
		if(cnt<s){
			ans=mid;
			R=mid-1;
		}else L=mid+1;
	}
	printf("%lld\n",1-ans);
	// puts("0");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif

	memset(dp,0x3f,sizeof(dp));
	dp[1][1]=0;
	for(int i=1;i<=B;i++){
		for(int j=B;j>=1;j--){
			for(int k=2;k<=j;k++)
				if(j%k==0)chkmin(dp[i][j/k],dp[i][j]+k-1);
			chkmin(dp[i+1][j+1],dp[i][j]);
		}
		for(int j=1;j<=i;j++){
			ll cnt=0;
			for(ll x=1;(i-1)/x;x<<=1)cnt+=(j<=(i-1)/x);
			assert(dp[i][j]==cnt);
			// cout<<dp[i][j]<<","<<cnt<<" ";
		}
		// cout<<endl;
	}
	ll T=read();
	while(T--)
		procedure();
	return 0;
}