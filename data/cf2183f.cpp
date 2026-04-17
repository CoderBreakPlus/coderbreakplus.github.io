// created time: 2026-04-17 18:32:52
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

int n,dp[5005][5005][2],ans[5005][5005],fa[5005],seq[5005],dfn[5005],tim;
char s[5005];
vector<int>E[5005];

void dfs(int x,int ff){
	dfn[x]=++tim,seq[tim]=x;
	for(auto y:E[x]){
		if(y==ff)continue;
		dfs(y,x);
		fa[dfn[y]]=dfn[x];
	}
}
void procedure(){
	n=read();
	scanf("%s",s+1);
	tim=0;
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)dp[i][j][0]=dp[i][j][1]=ans[i][j]=0;
	

	for(int i=1;i<=n;i++)for(int j=1;j<=n;j++)
		if(s[seq[i]]==s[seq[j]]){
			dp[fa[i]][fa[j]][0]++;
			ans[i][j]++;
			// cout<<"upd1 "<<seq[i]<<" "<<seq[j]<<" with 1"<<endl;
		}

	for(int i=n;i>=1;i--)for(int j=n;j>=1;j--){
		addmod(dp[fa[i]][j][0]+=dp[i][j][0]);
		addmod(dp[i][fa[j]][1]+=dp[i][j][1]), addmod(dp[i][fa[j]][1]+=dp[i][j][0]);
		if(s[seq[i]]==s[seq[j]]){
			int v; addmod(v=dp[i][j][0]+dp[i][j][1]);
			addmod(dp[fa[i]][fa[j]][0]+=v);
			addmod(ans[i][j]+=v);
			// cout<<"upd2 "<<seq[i]<<" "<<seq[j]<<" with "<<v<<endl;
		}
	}
	for(int i=n;i>=1;i--)for(int j=n;j>=1;j--) addmod(ans[fa[i]][j]+=ans[i][j]);
	for(int i=n;i>=1;i--)for(int j=n;j>=1;j--) addmod(ans[i][fa[j]]+=ans[i][j]);

	for(int i=1;i<=n;i++)printf("%d ",ans[dfn[i]][dfn[i]]);puts("");
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