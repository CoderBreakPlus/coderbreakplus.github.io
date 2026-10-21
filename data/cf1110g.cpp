// created time: 2026-10-21 11:25:04
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

int n,dep[2000005];
char s[2000005];
vector<int>E[2000005];

void dfs(int x,int fa){
	for(int y:E[x]){
		if(y==fa)continue;
		dep[y]=dep[x]+1;
		dfs(y,x);
	}
}
void add(int u,int v){ E[u].pb(v),E[v].pb(u); }
void procedure(){
	n=read();
	for(int i=1;i<=4*n;i++)E[i].clear();
	int fuck=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	scanf("%s",s+1);
	dfs(1,0);
	if(n<=2){ puts("Draw"); return; }

	int N=n;
	for(int i=1;i<=N;i++){
		if(s[i]=='W'){
			int a=++n; int b=++n; int c=++n;
			add(i,a),add(a,b),add(a,c);
		} 
	}
	dfs(1,0);
	
	for(int i=1;i<=n;i++){
		int deg=0;
		for(int j:E[i]){
			deg+=(E[j].size()>=2);
		}
		if(E[i].size()>=4||(deg>=2&&E[i].size()>=3)){
			puts("White");
			return;
		}
	}
	int S=0,T=0;
	for(int i=1;i<=n;i++){
		if(E[i].size()>=3){
			if(!S)S=i; else T=i;
		}
	}
	if(S&&T&&(dep[S]-dep[T])%2==0) puts("White");
	else 
	puts("Draw");
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