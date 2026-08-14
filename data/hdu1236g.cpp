// created time: 2026-08-13 14:54:36
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
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
inline int read(){
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

const int dx[4] = {1,-1,0,0};
const int dy[4] = {0,0,1,-1};

int n,m,N,a[50005],k,q,fa[50005];
int buc[50005],ok[50005];

int A[105],B[105],C[105],D[105];

string s[50005];
char str[50005];

int code(int x,int y){ return (x-1)*m+y; }
inline int find(int x){
	// cout<<"finding "<<x<<endl;
	if(x!=fa[x]) fa[x]=find(fa[x]);
	return fa[x];
}

bool chk(int x,int y){ return (x>=1&&y>=1&&x<=n&&y<=m&&s[x][y]=='.'); }

vector<int>E[205];
bool vis[205][205];

int que[205],hd,tl;
void procedure(){	
	n=read(),m=read(),k=read(),q=read();
	N=n*m;
	for(int i=1;i<=N;i++) fa[i]=i;
	for(int i=1;i<=n;i++) {
		string().swap(s[i]);
		s[i].resize(m+1);
		scanf("%s",str+1);
		for(int j=1;j<=m;j++)s[i][j]=str[j];
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<=m;j++){
			if(s[i][j]=='#')continue;
			for(int d:{0,1,2,3}){
				int x=i+dx[d],y=j+dy[d];
				if(chk(x,y)) fa[find(code(i,j))]=find(code(x,y));
			}
		}
	}

	int idx=0;
	for(int i=1;i<=k;i++){
		A[i]=read(),B[i]=read(),C[i]=read(),D[i]=read();
		int x=find(code(A[i],B[i])),y=find(code(C[i],D[i]));
		if(!buc[x]) buc[x]=++idx;
		if(!buc[y]) buc[y]=++idx;
		E[buc[x]].pb(buc[y]);
	}

	for(int i=1;i<=idx;i++){
		que[hd=tl=1]=i;
		vis[i][i]=1;
		while(hd<=tl){
			int x=que[hd++];
			for(int y:E[x]){
				if(vis[i][y]) continue;
				que[++tl]=y,vis[i][y]=1;
			}
		}
	}
	while(q--){
		int x1=read(),y1=read(),x2=read(),y2=read();
		int x=find(code(x1,y1)),y=find(code(x2,y2));
		if(!buc[x]||!buc[y])
			puts(x==y?"1":"0");
		else
			puts(vis[buc[x]][buc[y]]?"1":"0");
	}

	for(int i=1;i<=idx;i++) E[i].clear();
	for(int i=1;i<=idx;i++) 
		for(int j=1;j<=idx;j++) vis[i][j]=0;

	for(int i=1;i<=N;i++) ok[i]=buc[i]=0;
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