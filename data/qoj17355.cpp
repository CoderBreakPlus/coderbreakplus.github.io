// created time: 2026-05-29 15:50:37
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

int n,k,mn[500005],dep[500005],dis[500005]; char s[500005];
vector<int>E[500005];

void dfs(int x,int fa){
	mn[x]=(s[x]=='0'?1e9:dep[x]);
	for(auto y:E[x])if(y!=fa){
		dep[y]=dep[x]+1;
		dfs(y,x);
		chkmin(mn[x],mn[y]);
	}
}
void dfs2(int x,int fa,int d){
	if(d+mn[x]-dep[x]<=k)chkmin(d,mn[x]-dep[x]);
	for(auto y:E[x])if(y!=fa){
		if(s[y]=='0'){
			if(d+1<=k) dis[y]=dis[x],dfs2(y,x,d+1);
			else dis[y]=dis[x]+1,dfs2(y,x,1);
		}else
			dis[y]=dis[x]-(d+1<=k),dfs2(y,x,k+1);
	}
}
void procedure(){
	n=read(),k=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)E[i].clear(),dis[i]=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	dfs2(1,0,k+1);

	for(int i=2;i<=n;i++)printf("%d ",dis[i]);
	puts("");
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