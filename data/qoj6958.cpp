// created time: 2026-08-03
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

int n,p[1000005],tag[1000005],val[1000005],f[20][1000005],dfn[1000005],tim;
vector<int>E[1000005];


int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }

void dfs(int x,int fa){
	dfn[x]=++tim; 
	f[0][dfn[x]]=fa;

	for(int y:E[x]){
		dfs(y,x);
	}
}
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
void solve(int x){
	for(int y:E[x]){
		solve(y);
		tag[x]+=tag[y];
	}
}
void procedure(){
	n=read();
	tim=0;
	for(int i=1;i<=n;i++)E[i].clear(),tag[i]=0;
	for(int i=2;i<=n;i++)p[i]=read(),E[p[i]].pb(i);
	for(int i=2;i<=n;i++)val[i]=read();
	dfs(1,0);
	
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	for(int y=2;y<=n;y++){
		int x=read(),z=LCA(x,y);
		tag[x]++,tag[y]++,tag[z]-=2;
	}
	solve(1);

	int ans=0;
	for(int i=2;i<=n;i++){
		if(tag[i]>1&&val[i]) ans++;
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