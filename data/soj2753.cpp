// created time: 2026-11-17 07:38:18
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

int n,fa[1000005];
vector<int>E[1000005],G[1000005];
int dp[1000005];

void dfs(int x,int fa){
	for(int y:E[x])if(y!=fa){
		dfs(y,x);
		G[x].pb(y);
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)E[i].clear(),G[i].clear(),dp[i]=fa[i]=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	priority_queue<int,vector<int>,greater<int>>S;
	S.push(1);
	dp[1]=1;

	int sig=0;
	for(int i=1;i<=n;i++){
		bool have=0;
		while(!S.empty() && S.top()<=i){
			int x=S.top();S.pop();
			addmod(dp[x]+=sig);
			have|=(x==i);
			for(int y:G[x])S.push(y),dp[y]=mod-sig;
		}
		if(have){
			addmod(sig+=dp[i]);
		}
	}
	printf("%d\n",dp[n]);
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