// created time: 2026-11-07 07:40:45
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
char ibuf[1<<22],*ip=ibuf,*ie=ibuf;
int gc(){
    if(ip==ie){ie=ibuf+fread(ibuf,1,1<<22,stdin);ip=ibuf;if(ip==ie)return -1;}
    return *ip++;
}
int read(){
    int x=0;char c=gc();
    while(c<'0'||c>'9')c=gc();
    while(c>='0'&&c<='9')x=x*10+(c-'0'),c=gc();
    return x;
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

int n,h[5000005],c[5000005];
ll dp[5000005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)h[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<=n;i++){
		dp[i]=dp[i-1];
		int mx=h[i];
		for(int j=i-1;j>=1;j--){
			chkmax(mx,h[j]);
			if(max(h[i],h[j])==mx)
				chkmin(dp[i],dp[j-1]+c[j]);
		}
		dp[i]+=c[i];
		// cout<<"at "<<i<<" dp="<<dp[i]<<endl;
	}
	printf("%lld\n",dp[n]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}