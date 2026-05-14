// created time: 2026-05-14 14:57:04
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

struct Edge{
	int to,nxt;
}e[1200005];
int hd[600005],tot;
void add(int u,int v){
	e[++tot].to=v;
	e[tot].nxt=hd[u];
	hd[u]=tot;
}
int n,m,dfn[600005],tim,dep[600005],f[20][600005],jp[20][600005];
int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
void dfs(int x,int fa){
	dfn[x]=++tim, f[0][dfn[x]]=fa, jp[0][x]=fa;
	for(int i=1;i<20;i++)jp[i][x]=jp[i-1][jp[i-1][x]];
	for(int i=hd[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(y==fa)continue;
		dep[y]=dep[x]+1,dfs(y,x);
	}
}
int kth_fa(int x,int k){
	while(k){
		int t=__builtin_ctz(k);
		x=jp[t][x], k^=(1<<t);
	}
	return x;
}
int dis(int x,int y,int z){ return dep[x]+dep[y]-2*dep[z]; }
int jump(int x,int y,int z,int d){
	if(dep[x]-dep[z]>=d) return kth_fa(x,d);
	else return kth_fa(y,dis(x,y,z)-d);
}
struct Node{
	int u,v,r; ll sum;
}F[20][300005];
inline Node operator+ (const Node &A,const Node &B){
	Node C=(Node){0,0,0,0};
	int z=LCA(A.v,B.u),d=dis(A.v,B.u,z);

	if(d>=A.r+B.r){
		C.sum=A.sum+B.sum+d-A.r-B.r;
		if(!A.sum) C.u=jump(A.v,B.u,z,A.r);
		else C.u=A.u;
		if(!B.sum) C.v=jump(B.u,A.v,z,B.r);
		else C.v=B.v;
	}else if(A.r+d<=B.r) C=A, C.sum+=B.sum;
	else if(B.r+d<=A.r) C=B, C.sum+=A.sum;
	else C.r=(A.r+B.r-d)/2, C.u=C.v=jump(A.u,B.u,z,A.r-C.r);

	return C;
}
void gems(int c,int n,int m,vector<int> u,vector<int> v,vector<int> a,vector<int> d){
	::n=n,::m=m;
	for(int i=0;i<n-1;i++){
		int t=n+i+1;
		add(u[i],t),add(t,u[i]);
		add(v[i],t),add(t,v[i]);
	}
	dfs(1,0);
	for(int i=1;(1<<i)<=2*n-1;i++)
		for(int j=1;j<=2*n-(1<<i);j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	for(int i=1;i<=m;i++)F[0][i]=(Node){a[i-1],a[i-1],2*d[i-1],0};
	for(int i=1;(1<<i)<=m;i++)
		for(int j=1;j<=m-(1<<i)+1;j++)
			F[i][j]=F[i-1][j]+F[i-1][j+(1<<i-1)];
}
ll query(int x,int l,int r){
	Node ret=(Node){x,x,0,0};
	for(int i=19;i>=0;i--)
		if(l+(1<<i)<=r+1) ret=ret+F[i][l],l+=(1<<i);
	return ret.sum/2;
}