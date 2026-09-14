// created time: 2026-09-13 15:28:15
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

int n,m,sb;
bool tag[1000005],ok[1000005],vis[1000005],vism[1000005];
vector<int>s[1000005],e[1000005];
vector<pair<int,int>>E[1000005];


void add(int u,int v){
	E[u].pb(v,++sb),E[v].pb(u,sb);
}

int dfn[1000005],tim,low[1000005],stk[1000005],tp;

int ans,flg,cnts,cntv,cntm;
void dfs(int x,int i){
	dfn[x]=low[x]=++tim, stk[++tp]=x, vis[x]=1;
	ans+=2;
	cntv++;
	for(auto [y,j]: E[x])if(i!=j){
		cntm+=!vism[j]; vism[j]=1;
		if(!dfn[y]){
			dfs(y,j);
			low[x]=min(low[x],low[y]);
		}else if(vis[y]){
			low[x]=min(low[x],dfn[y]);
		}
	}
	if(low[x]==dfn[x]){
		cnts++;
		int siz=0;
		do{
			flg|=tag[stk[tp]],vis[stk[tp]]=0;
			siz++;
		}while(stk[tp--]!=x);
		flg|=(siz%2==0);
	}
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int k=read();
		if(k<=1) ans+=k;
		else ok[i]=1;
		while(k--){ int x=read(); s[i].pb(x),e[x].pb(i); }
	}

	for(int i=1;i<=n;i++)if(e[i].size()){
		if(e[i].size()==1) tag[e[i][0]]=1;
		else{
			if(ok[e[i][0]]&&ok[e[i][1]])
				add(e[i][0],e[i][1]);
			else
				tag[e[i][0]]=tag[e[i][1]]=1;
		}
	}
	for(int i=1;i<=m;i++)if(ok[i]&&!dfn[i]){
		flg=cnts=cntv=cntm=0;
		dfs(i,0);
		if(!flg && cnts-1+cntv==cntm)ans--;
	}
	printf("%d\n",ans);
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