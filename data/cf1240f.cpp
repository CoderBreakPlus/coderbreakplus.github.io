// created time: 2026-06-12 09:19:51
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

int n,m,k,eid[2005][2005],to[2005][2005],col[2005];
int deg[2005],id[2005],cnt;

void match(int v,int y,int x){
	swap(eid[v][x],eid[v][y]);
	swap(to[v][x],to[v][y]);
	if(to[v][y]) match(to[v][y],x,y),col[eid[v][y]]=y;
}
void procedure(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)read();
	for(int i=1;i<=m;i++){
		int u=read(),v=read()+n;
		if(deg[u]%k==0) deg[u]=0, id[u]=++cnt;
		if(deg[v]%k==0) deg[v]=0, id[v]=++cnt;
		deg[u]++,deg[v]++;
		u=id[u],v=id[v];

		int x=0;
		for(int c=1;c<=k;c++)
			if(!eid[u][c]&&!eid[v][c])x=c;
		if(!x){
			int y=0;
			for(int c=1;c<=k;c++)if(!eid[u][c])x=c;
			for(int c=1;c<=k;c++)if(!eid[v][c])y=c;
			match(v,y,x);
		}
		to[u][x]=v,to[v][x]=u;
		eid[u][x]=eid[v][x]=i;
		col[i]=x;
	}
	for(int i=1;i<=m;i++)printf("%d\n",col[i]);
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