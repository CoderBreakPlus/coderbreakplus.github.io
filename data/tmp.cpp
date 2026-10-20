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

int n,dep[70005],tim,f[20][70005],dfn[70005]; char s[70005];
vector<int>E[70005];

int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
int dist(int x,int y){
	if(!x||!y) return -1;
	return dep[x]+dep[y]-2*dep[LCA(x,y)];
}
void dfs(int x,int fa){
	f[0][dfn[x]=++tim]=fa;
	for(int y:E[x])if(y!=fa)
		dep[y]=dep[x]+1,dfs(y,x);
}
int ans[70005],cur[70005];

struct Node{
	int x,y,d;
	Node(){ x=y=0,d=-1; }
	Node(int X,int Y){ x=X,y=Y,d=dist(X,Y); }
};
bool operator< (const Node &A, const Node &B){ return A.d<B.d; }
inline Node operator+ (const Node &A, const Node &B){ return max({A,B,Node(A.x,B.x),Node(A.x,B.y),Node(A.y,B.x),Node(A.y,B.y)}); }
inline void operator+= (Node &A, const Node &B){ A=A+B; }
Node buc[70005];
void procedure(){
	n=read(); scanf("%s",s+1);
	tim=0;
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	Node dia;
	for(int u=1;u<=n;u++)
		if(s[u]=='1') dia+=Node(u,u);
	int S=dia.x,T=dia.y;
	
	// cout<<"S="<<S<<" T="<<T<<endl;
	// cout<<"FUCK"<<endl;
	for(int u=1;u<=n;u++){
		if(s[u]=='1'){
			cur[u]=max(dist(u,S),dist(u,T));
			if(!cur[u]) s[u]='0',ans[u]=1;
		}else
			ans[u]=-1;
	}

	for(int i=1;i<=n;i++) cout<<cur[i]<<" "; cout<<endl;
	for(int t=2;;t++){
		for(int i=0;i<=n;i++)buc[i]=Node();
		for(int u=1;u<=n;u++)if(s[u]=='1')
			buc[cur[u]/2]+=Node(u,u);
		for(int i=n-1;i>=0;i--)buc[i]+=buc[i+1];

		for(int u=1;u<=n;u++)if(s[u]=='1'){
			int L=1,R=n-1,P=0;
			while(L<=R){
				int M=(L+R)>>1;
				int S=buc[M].x,T=buc[M].y;
				if(max(dist(u,S),dist(u,T))>=M)
					P=M,L=M+1;
				else
					R=M-1;
			}
			cur[u]=P;
		}
		bool flg=0;
		for(int u=1;u<=n;u++)if(s[u]=='1'){
			if(cur[u]) flg=1;
			else s[u]='0',ans[u]=t;
		}
		if(!flg)break;
		for(int u=1;u<=n;u++) printf("%d ",cur[u]);
		puts("");
	}
	for(int i=1;i<=n;i++) printf("%d ",ans[i]);
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