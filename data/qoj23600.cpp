// created time: 2026-11-02 08:41:55
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

int n,m,id,a[1000005],fa[1000005];
vector<int>E[1000005];

int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
void dfs(int x,int fa){
	a[x]=id;
	for(int y:E[x])if(y!=fa){
		++id;
		dfs(y,x);
		++id;
	}
}
void cat(){
	n=read(),m=read();id=0;
	for(int i=0;i<=n;i++)fa[i]=i,E[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
		fa[find(u)]=find(v);
	}
	for(int i=1;i<=n;i++)
		if(find(i)==i) E[0].pb(i);
	dfs(0,-1);
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	puts("");
}
int jp[1000005],ord[1000005];
void dog(){
	n=read();
	for(int i=1;i<=n;i++)ord[i]=i,a[i]=read(),jp[i]=0;
	sort(ord+1,ord+n+1,[](int x,int y){ return a[x]<a[y]; });

	int now=0;
	vector<pair<int,int>>edge;
	for(int i=1;i<=n;i++){
		int x=ord[i],step=a[x]-a[now]-1;
		while(step--) now=jp[now];
		if(now&&x)edge.pb(now,x);
		jp[x]=now,now=x;
	}

	printf("%d\n",(int)edge.size());
	for(auto [u,v]: edge) printf("%d %d\n",u,v);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	char s[55];
	scanf("%s",s);
	int T=read();
	if(s[0]=='c')
		while(T--)cat();
	else
		while(T--)dog();
	// math_init();
	return 0;
}