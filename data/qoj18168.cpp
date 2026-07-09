// created time: 2026-07-09 07:34:21
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

int n,q,a[1000005];

int stk[1000005],w;

namespace brute{
	void main(){
		while(q--){
			int l=read(),r=read(); w=0;
			for(int i=l;i<=r;i++){
				if(w && stk[w]==a[i]) w--;
				else stk[++w]=a[i];
			}
			printf("%d\n",w);
		}
	}
}
map<int,int>mp[1000005];
vector<int>E[1000005];

int p=1,c=1,fa[1000005],bro[1000005],dfn[1000005],dep[1000005],f[21][1000005];
int id[1000005],tim;
int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
void dfs(int x,int fa){
	dfn[x]=++tim, f[0][dfn[x]]=fa;
	for(int y:E[x]) dep[y]=dep[x]+1,dfs(y,x);
}
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
void procedure(){
	n=read(),q=read();	
	for(int i=1;i<=n;i++) a[i]=read();
	// if(n<=2000&&q<=2000) {brute::main();return;}
	
	id[0]=p;

	auto addedge = [&](int x,int y,int z){
		fa[y]=x, E[x].pb(y), bro[y]=z;
	};
	for(int i=1;i<=n;i++){
		if(bro[p]==a[i]) p=fa[p];
		else{
			if(mp[p].count(a[i])) p=mp[p][a[i]];
			else{
				mp[p][a[i]]=++c;
				addedge(p,c,a[i]);
				p=c;
			}
		}
		id[i]=p;
	}
	dfs(1,0);

	for(int i=1;(1<<i)<=c;i++)
		for(int j=1;j<=c-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
	
	while(q--){
		int l=id[read()-1],r=id[read()];
		printf("%d\n", dep[l]+dep[r]-2*dep[LCA(l,r)]);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}