// created time: 2026-10-21 10:52:23
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

int n,x,y;
vector<int>E[3005];

int stk[3005],tp;
int seq[3005],sz,w[3005],qz[3005],hz[3005],vis[3005];

void dfs(int x,int fa){
	stk[++tp]=x;
	if(x==y){
		sz=tp;
		memcpy(seq,stk,sizeof(seq));
	}
	for(int y:E[x])if(y!=fa)
		dfs(y,x);
	--tp;
}
int tot;
void dfs2(int x,int fa){
	++tot,vis[x]=1;
	for(int y:E[x])if(y!=fa&&!vis[y])
		dfs2(y,x);
}

int dp[3005][3005][2];

void procedure(){
	n=read(),x=read(),y=read();
	for(int i=1;i<=n;i++) E[i].clear(),vis[i]=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	tp=0;
	dfs(x,0);

	seq[sz+1]=0;
	for(int i=1;i<=sz;i++){
		tot=0; dfs2(seq[i],seq[i+1]);
		w[i]=tot;
	}

	if(sz==2){
		printf("%d\n",n&1);
		return;
	}
	for(int i=1;i<=sz;i++) qz[i]=qz[i-1]+w[i];
	hz[sz+1]=0;
	for(int i=sz;i>=1;i--) hz[i]=hz[i+1]+w[i];

	for(int i=1;i+2<=sz;i++){
		int j=i+2;
		int tot=qz[i]+hz[j];
		dp[i][j][0]=dp[i][j][1]=(tot&1);
	}

	for(int len=4;len<=sz;len++)
		for(int i=1,j=len;j<=sz;i++,j++){
			int tot=qz[i]+hz[j];
			if(tot&1){
				// solve dp[i][j][1]
				dp[i][j][1]=min(dp[i+1][j][0],dp[i][j-1][0]);
				// solve dp[i][j][0]
				dp[i][j][0]=max(dp[i+1][j][1],dp[i][j-1][1]);
				chkmax(dp[i][j][0],dp[i][j][1]);
			}else{
				// solve dp[i][j][0]
				dp[i][j][0]=max(dp[i+1][j][1],dp[i][j-1][1]);
				// solve dp[i][j][1]
				dp[i][j][1]=min(dp[i+1][j][0],dp[i][j-1][0]);
				chkmin(dp[i][j][1],dp[i][j][0]);
			}
			// cout<<i<<"->"<<j<<" dp="<<dp[i][j][0]<<","<<dp[i][j][1]<<endl;
		}
	printf("%d\n",dp[1][sz][0]);
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