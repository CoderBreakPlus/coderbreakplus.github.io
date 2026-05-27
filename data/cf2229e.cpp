// created time: 2026-05-27 09:48:18
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

int n,a[200005],mx[200005],dp[200005],df[200005],col[200005];
vector<int>E[200005];

int qz[200005],hz[200005];
void dfs(int x,int fa){
	mx[x]=0;
	for(int y:E[x]){
		if(y==fa)continue;
		if(x==n) col[y]=y;
		else col[y]=col[x];
		chkmax(qz[col[y]],y);
		chkmax(hz[col[y]],y);

		dfs(y,x);
		chkmax(mx[x],max(y,mx[y]));
	}
}

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)E[i].clear(),dp[i]=df[i]=0,qz[i]=hz[i]=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	if(E[n].size()==1){puts("1");return;}
	dfs(n,0);
	int st=0;
	for(int i=1;i<=n;i++){
		if(E[i].size()>1);
		else st=i;
	}
	dp[st]=df[st]=1;
	for(int i=st+1;i<n;i++){
		if(i-1>=mx[i])
			addmod(dp[i]=df[i-1]+mod-df[mx[i]]);
		addmod(df[i]=df[i-1]+dp[i]);
	}
	for(int i=2;i<=n;i++)chkmax(qz[i],qz[i-1]);
	for(int i=n-1;i>=1;i--)chkmax(hz[i],hz[i+1]);
	
	int ans=0;
	for(int i=1;i<n;i++){
		if(!dp[i])continue;
		if(max(qz[col[i]-1],hz[col[i]+1])<i)addmod(ans+=dp[i]);
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