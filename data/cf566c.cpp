// created time: 2026-06-12 16:46:46
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

int n,c[200005],sz[200005],mxs[200005],son[200005],vis[200005],wh,rt;
double val[200005];

vector<pair<int,int>>E[200005];
void dfs(int x,int fa,int d){
	val[x]=sqrtl(d)*c[x];
	for(auto [y,w]:E[x]){
		if(y==fa)continue;
		dfs(y,x,d+w); val[x]+=val[y];
	}
}
double calc(int x,int fa,int d){
	double ret=sqrtl(d)*d*c[x];
	for(auto [y,w]:E[x]){
		if(y==fa)continue;
		ret+=calc(y,x,d+w);
	}
	return ret;
}
void findcent(int x,int fa){
	sz[x]=1,mxs[x]=0;
	for(auto [y,w]:E[x]){
		if(vis[y]||y==fa)continue;
		findcent(y,x);
		sz[x]+=sz[y],chkmax(mxs[x],sz[y]);
	}
	chkmax(mxs[x],wh-sz[x]);
	if(mxs[rt]>mxs[x]) rt=x;
}

void solve(int x){
	vis[x]=1;
	dfs(x,0,0);
	son[x]=0;
	double fuck=0;
	for(auto [y,w]:E[x]){
		if(val[y]>val[son[x]])son[x]=y;
		fuck+=val[y];
	}
	if(2*val[son[x]]>fuck){
		if(vis[son[x]]){
			double ans_x = calc(x,0,0);
			double ans_son_x = calc(son[x],0,0);	
			if(ans_x < ans_son_x){
				printf("%d %.10lf\n",x,ans_x);
			}else{
				printf("%d %.10lf\n",son[x],ans_son_x);
			}
		}else{
			rt=0,wh=(sz[son[x]]>sz[x])?(wh-sz[x]):(sz[son[x]]);
			findcent(son[x],x);
			solve(rt);
		}
	}else{
		printf("%d %.10lf\n",x,calc(x,0,0));
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		E[u].pb(v,w),E[v].pb(u,w);
	}
	mxs[0]=wh=n; findcent(1,0);
	solve(rt);
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