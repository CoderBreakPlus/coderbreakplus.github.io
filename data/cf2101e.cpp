// created time: 2026-10-20 16:14:44
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

int n,dep[70005],tim,f[20][70005],dfn[70005],jp[70005]; char s[70005];
vector<int>E[70005];

int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
int dist(int x,int y){ if(!x||!y) return -1; return dep[x]+dep[y]-2*dep[LCA(x,y)]; }
void dfs(int x,int fa){
	f[0][dfn[x]=++tim]=fa;
	for(int y:E[x])if(y!=fa)
		dep[y]=dep[x]+1,dfs(y,x);
}
int sz[70005],mxs[70005],vis[70005],rt,wh;
void findcent(int x,int fa){
	sz[x]=1,mxs[x]=0;
	for(int y:E[x])if(!vis[y]&&y!=fa){
		findcent(y,x);
		sz[x]+=sz[y];
		chkmax(mxs[x],sz[y]);
	}
	chkmax(mxs[x],wh-sz[x]);
	if(mxs[x]<mxs[rt])rt=x;
}
void build(int x){
	vis[x]=1;
	int cur=wh;
	for(int y:E[x])if(!vis[y]){
		if(sz[y]>sz[x]) wh=cur-sz[x];
		else wh=sz[y];
		rt=0,findcent(y,x);
		jp[rt]=x,build(rt);
	}
}
struct Node{
	int x,y,d;
	Node(){ x=y=0,d=-1; }
	Node(int X,int Y){ x=X,y=Y,d=dist(X,Y); }
};
bool operator< (const Node &A, const Node &B){ return A.d<B.d; }
inline Node operator+ (const Node &A, const Node &B){ return max({A,B,Node(A.x,B.x),Node(A.x,B.y),Node(A.y,B.x),Node(A.y,B.y)}); }
inline void operator+= (Node &A, const Node &B){ A=A+B; }

int mxd[70005];
vector<Node>buc[70005];
vector<int>dtmp[70005];

int ans[70005],cur[70005];
void procedure(){
	n=read(); scanf("%s",s+1);
	tim=0;
	for(int i=1;i<=n;i++)vector<int>().swap(E[i]),jp[i]=vis[i]=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	mxs[rt=0]=wh=n,findcent(1,0);
	build(rt);

	for(int i=1;i<=n;i++) mxd[i]=0;
	for(int i=1;i<=n;i++){
		vector<int>().swap(dtmp[i]);
		int x=i;
		while(x){
			int d=dist(x,i);
			dtmp[i].pb(d);
			chkmax(mxd[x],d),x=jp[x];
		}
	}
	for(int u=1;u<=n;u++)
		buc[u].resize(mxd[u]+1);
	auto clear=[&](){
		for(int u=1;u<=n;u++)
			fill(buc[u].begin(),buc[u].end(),Node());
	};
	auto press=[&](int R){
		for(int u=1;u<=n;u++)
			for(int i=min(R-1,(int)buc[u].size()-2);i>=0;i--) buc[u][i]+=buc[u][i+1];
	};

	Node dia;
	for(int u=1;u<=n;u++)
		if(s[u]=='1') dia+=Node(u,u);
	int S=dia.x,T=dia.y;
	
	for(int u=1;u<=n;u++){
		if(s[u]=='1'){
			cur[u]=max(dist(u,S),dist(u,T));
			if(!cur[u]) s[u]='0',ans[u]=1;
		}else ans[u]=-1;
	}
	for(int t=2;;t++){
		clear();
		int R=0;
		for(int u=1;u<=n;u++)if(s[u]=='1'){
			int m=cur[u]/2;
			chkmax(R,m);
			for(int i=0,x=u;i<dtmp[u].size();i++,x=jp[x]){
				int d=dtmp[u][i];
				if(m>=d){
					buc[x][min((int)buc[x].size()-1,m-d)]+=Node(u,u);
				}
			}
		}
		press(R);
		bool flg=0;
		for(int u=1;u<=n;u++)if(s[u]=='1'){
			cur[u]=0;
			for(int i=0,x=u;i<dtmp[u].size();i++,x=jp[x]){
				int d=dtmp[u][i];
				int X=buc[x][d].x,Y=buc[x][d].y;
				chkmax(cur[u],max(dist(X,u),dist(Y,u)));
			}
			if(cur[u]) flg=1;
			else s[u]='0',ans[u]=t;
		}
		if(!flg)break;
	}
	for(int u=1;u<=n;u++) printf("%d ",ans[u]);
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