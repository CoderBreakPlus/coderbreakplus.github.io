// created time: 2026-05-29 08:55:27
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

int n;
const int N = (1<<22)+5;
struct Edge{
	int to,nxt;
}e[N];
int hd[N],tot,sz[N],ans;
void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=hd[u];
	hd[u]=tot;
}
void dfs(int x,int fa=-1){
	sz[x]=!!x;
	ll sb=(ll)(n-1)*(n-2)/2;
	for(int i=hd[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa)continue;
		dfs(y,x),sz[x]+=sz[y];
		sb-=(ll)sz[y]*(sz[y]-1)/2;
	}
	sb-=(ll)(n-1-sz[x])*(n-1-sz[x]-1)/2;
	if(sb&1) ans^=x;
}
void procedure(){
	n=(1<<read());
	memset(hd,0,sizeof(int)*n); tot=ans=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		add(u,v),add(v,u);
	}
	dfs(0);
	printf("%d\n",ans^(n==2));
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