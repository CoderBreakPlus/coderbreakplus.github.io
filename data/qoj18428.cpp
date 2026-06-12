// created time: 2026-06-12 14:43:39
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

int n,p[505],q[505],dp[505][505],t1[505][505],t2[505][505];
void procedure(){
	n=read();
	bool f=1;
	for(int i=1;i<=n;i++)p[i]=read(),f&=(p[i]==i);

	if(f){
		puts("0");
		return;
	}
	int ans=0,ivn=INV(n),stp=(ull)n*INV(n-1)%mod,invn_1=INV(n-1);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++)q[j]=p[j];
		sort(q+1,q+i+1);
		sort(q+i+1,q+n+1);

		bool f=1;
		for(int j=1;j<=n;j++)f&=(q[j]==j);
		if(f) continue;

		for(int j=0;j<=n+1;j++){
			memset(dp[j],0,sizeof(dp[j]));
			memset(t1[j],0,sizeof(t1[j]));
			memset(t2[j],0,sizeof(t2[j]));
		}
		
		dp[i][i+1]=1;
		for(int j=i;j>=1;j--)
			for(int k=i+1;k<=n;k++){
				addmod(t1[j][k]+=t1[j+1][k]);
				addmod(t2[j][k]+=t2[j][k-1]);
				addmod(dp[j][k]+=t1[j][k]);
				addmod(dp[j][k]+=t2[j][k]);
				if(q[j]<=q[k]||!dp[j][k])continue;
				
				ans=(ans+(ull)dp[j][k]*stp)%mod;
				int cf=(ull)dp[j][k]*invn_1%mod;
				addmod(t1[j][k]+=cf);
				addmod(t2[j][k]+=cf);
			}
	}
	printf("%llu\n",((ull)ans*ivn+1)%mod);
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