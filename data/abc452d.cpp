#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };

ll dp[200005][55];
char s[200005],t[200005];
int n,m;
void procedure(){
	scanf("%s%s",s+1,t+1);
	n=strlen(s+1),m=strlen(t+1);

	ll ans=0;
	for(int i=1;i<=n;i++){
		dp[i-1][0]++;
		for(int j=0;j<m;j++){
			if(s[i]!=t[j+1])
				dp[i][j]+=dp[i-1][j];
			else
				dp[i][j+1]+=dp[i-1][j];
		}
		for(int j=0;j<m;j++)
			ans+=dp[i][j];
	}
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}