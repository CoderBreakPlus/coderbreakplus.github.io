// created time: 2026-11-09 08:10:27
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
int n,m,k,ans[2005][105],p[105],r;
int fa[105],sz[105];
int u[105],v[105],tp;

int find(int x){
	while(x!=fa[x]) x=fa[x];
	return x;
}
bool merge(int x,int y){
	x=find(x),y=find(y);
	if(x==y)return 1;
	if(sz[x]>sz[y])swap(x,y);
	u[++tp]=x,v[tp]=y;
	sz[y]+=sz[x],fa[x]=y;
	return 0;
}
void undo(){ fa[u[tp]]=u[tp]; sz[v[tp]]-=sz[u[tp]]; tp--; }
void undo(int tim){ while(tp>tim) undo(); }
void print(){
	printf("%d\n",r);
	for(int i=1;i<=r;i++){
		for(int j=1;j<=n;j++) printf("%d ",ans[i][j]);
		puts("");
	}
}
int fuck=0;
void dfs(int i,int L,int R,int c){
	if(c>=m || c+(k-i+1)<m) return;
	int bef=tp;
	if(L==R){
		p[L]=i;
		if(c+merge(L,i)==m){
			++r;
			for(int j=1;j<=k;j++)ans[r][j+n-k]=p[j]+n-k;
			for(int j=1;j<=n-k;j++)ans[r][j]=j;
			if(r==2000){
				print();
				exit(0);
			}
		}
	}else{
		auto dfsL=[&](){
			int tL=merge(L,i); p[L]=i;
			dfs(i+1,L+1,R,c+tL);
			undo(bef);
		};
		auto dfsR=[&](){
			int tR=merge(R,i); p[R]=i;
			dfs(i+1,L,R-1,c+tR);
			undo(bef);
		};
		if(rand()&1) dfsL(),dfsR();
		else dfsR(),dfsL();
	}
	undo(bef);
}
void procedure(){
	n=read(),m=read();
	k=min(20,n);
	for(int i=0;i<(1<<k-1);i++){
		for(int x=1;x<=k;x++)fa[x]=x;
		int L=0,R=k+1;
		for(int j=0;j<k-1;j++){
			if((~i>>j)&1)p[++L]=j+1;
			else p[--R]=j+1;
		}
		p[++L]=k;
		for(int j=1;j<=k;j++)fa[j]=j;
		for(int j=1;j<=k;j++)fa[find(p[j])]=find(j);
		int cnt=n-k;
		for(int j=1;j<=k;j++)cnt+=(find(j)==j);
		if(cnt==m){
			++r;
			for(int j=1;j<=k;j++)ans[r][j+n-k]=p[j]+n-k;
			for(int j=1;j<=n-k;j++)ans[r][j]=j;
			if(r==2000)break;
		}
	}
	if(r>=2000||n<=20||n-m<=10){
		print();
		return;
	}
	k=min(n,n-m+5);
	for(int i=1;i<=k;i++)fa[i]=i,sz[i]=1;
	dfs(1,1,k,n-k);
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