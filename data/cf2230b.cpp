// created time: 2026-05-20 18:49:26
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

int n;char st[300005];
int dp[300005][1<<4];

void procedure(){
	scanf("%s",st+1);n=strlen(st+1);
	dp[0][0]=0;
	for(int i=1;i<=n;i++){
		for(int s=0;s<(1<<4);s++){
			dp[i][s]=dp[i-1][s];
		}
		// cout<<"ok "<<(st[i])<<endl;
		// cout<<"here "<<(1<<(st[i]-'1'))<<endl;
		if(st[i]!='4')
		for(int s=0;s<(1<<4);s++){
			bool f=1;
			for(int t=0;t<4;t++)if((s>>t)&1){
				if(((t+1)*10+st[i]-'0')%4==0)f=0;
			}
			if(f)chkmax(dp[i][s|(1<<(st[i]-'1'))],dp[i-1][s]+1);
		}
		// for(int s=0;s<(1<<4);s++)
		// 	if(dp[i][s]) cout<<i<<","<<s<<" dp="<<dp[i][s]<<endl;
	}	
	int ans=0;
	for(int i=0;i<(1<<4);i++)chkmax(ans,dp[n][i]);
	printf("%d\n",n-ans);
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