// created time: 2026-10-04 07:33:52
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

int n,a;
ll t[5000005],dp[5000005];

ll stk[5000005],val[5000005],qz[500005],tp;

void procedure(){
	n=read(),a=read();
	for(int i=1;i<=n;i++)t[i]=read()-i;
	memset(dp,0x3f,sizeof(dp));
	dp[0]=-1;

	// for(int i=0;i<=n;i++){
	// 	ll now=dp[i];
	// 	for(int j=i+1;j<=n;j++){
	// 		now=max(now,t[j]);
	// 		chkmin(dp[j],now+2*a+j-i-2);
	// 	}
	// }
	qz[0]=1e18;
	for(int i=1;i<=n;i++){
		while(tp && t[stk[tp]]<=t[i]) tp--;
		stk[++tp]=i,qz[tp]=qz[tp-1];

		int L=stk[tp-1],R=i-1,Ans=L-1;
		while(L<=R){
			int Mid=(L+R)>>1;
			if(dp[Mid]<t[i]) Ans=Mid,L=Mid+1;
			else R=Mid-1; 
		}
		if(Ans>=stk[tp-1]) chkmin(qz[tp],t[i]+2*a-Ans-2);
		if(Ans+1<i) chkmin(qz[tp],dp[Ans+1]+2*a-(Ans+1)-2);

		chkmin(dp[i],qz[tp]+i);
	}
	printf("%lld\n",dp[n]+n+1);
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