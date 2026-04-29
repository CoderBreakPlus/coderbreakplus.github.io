// created time: 2026-04-29 18:42:21
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

char s[5000005];
int n,nxt[5000005][2],dp[5000005];

int tag[2][2],tag2[2][2];
void procedure(){
	scanf("%s",s+1); n=strlen(s+1);

	for(int i=1;i<=n;i++)dp[i]=0;
	for(int i=1;i<=n;i++)s[i]-='0';
	for(auto a:{0,1})for(auto b:{0,1})tag[a][b]=tag2[a][b]=n+1;

	for(int i=n;i>=1;i--){
		nxt[i][s[i]^1]=tag[(i&1)^1][s[i]^1];
		nxt[i][s[i]]=tag2[(i&1)^1][s[i]];

		tag[i&1][s[i]]=i;
		if(s[i-1]==s[i]) tag2[i&1][s[i]]=i;
	}

	dp[1]=1;
	for(int i=3;i<=n;i+=2)
		if(s[i]!=s[1]&&s[i-1]==s[i]){
			dp[i]=1;
			break;
		} 

	for(int i=1;i<=n;i++){
		if(nxt[i][0]<=n)addmod(dp[nxt[i][0]]+=dp[i]);
		if(nxt[i][1]<=n)addmod(dp[nxt[i][1]]+=dp[i]);
	}

	int ans=0;
	for(int i=n;i>=1;i-=2){
		if(s[i]==s[n]||nxt[i][s[i]]<=n)addmod(ans+=dp[i]);
	}
	printf("%d\n",ans);
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