// created time: 2026-05-22 11:06:08
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

const int N = 19;


int dp[N+5][N+5],ok[N+5];
void procedure(){
	dp[0][0]=1;
	for(int i=0;i<N;i++)
		for(int j=0;j<N;j++)
			for(int k=0;j+k<=N;k++)
				chkmax(dp[i+k-1][j+k],dp[i][j]*k);

	for(int i=0;i<=N;i++){
		for(int j=0;j<=N;j++)chkmax(ok[i],dp[i][j]);
		cout<<ok[i]<<" ";
	}
	cout<<endl;

	int ans=0;
	for(int i=0;i<(1<<N);i++){
		int x=__builtin_popcount(i);
		ans+=ok[x];
	}
	printf("%d\n",ans);
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