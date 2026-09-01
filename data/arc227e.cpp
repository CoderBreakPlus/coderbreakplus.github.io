// created time: 2026-09-01 20:17:37
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

int n,m,a[200005],dp[200005][4];

void procedure(){
	n=read()-1,m=read();
	for(int i=1;i<=m;i++)
		a[read()]++;

	for(int i=1;i<=n;i++){
		while(a[i]>=3){
			a[i]-=2;
			if(i*2<=n)a[2*i]++;
		}
	}

	int ret=1;
	for(int d=1;d<=n;d+=2){
		int ans=0;
		dp[d][a[d]]=1;
		for(int i=d;i<=n;i*=2){
			for(int j=0;j<=3;j++){
				// cout<<i<<","<<j<<" dp = "<<dp[i][j]<<endl;
				// very 0
				if(i*2<=n) addmod(dp[2*i][a[2*i]+j/2]+=dp[i][j]);
				else addmod(ans+=dp[i][j]);

				// very 1
				if(j>=1){
					if(i*2<=n) addmod(dp[2*i][a[2*i]+(j-1)/2]+=dp[i][j]);
					else addmod(ans+=dp[i][j]);
				}				
			}
		}
		// cout<<"d="<<d<<" ans="<<ans<<endl;
		ret=(ull)ret*ans%mod;
	}
	printf("%d\n",ret);
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