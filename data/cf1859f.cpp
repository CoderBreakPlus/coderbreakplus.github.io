// created time: 2026-09-21 14:12:13
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

int n,t,q,a[100005],b[100005],lca[100005],vis[100005],f[20][100005],jp[20][100005],tim;
ll ans[100005],dis[100005];
char s[100005];
vector<pair<int,int>>E[100005];

int dfn[100005],seq[100005],ff[100005],fv[100005];
ll dep[100005],ext[100005],val0[20][100005],val1[20][100005];

int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
void dfs(int x,int fa,int w){
	jp[0][x]=fa;
	f[0][dfn[x]=++tim]=fa,seq[tim]=x,ff[x]=fa,fv[x]=w;
	dep[x]=dep[fa]+w;
	for(auto [y,w]:E[x]){
		if(y==fa)continue;
		dfs(y,x,w);
	}
}
void procedure(){
	n=read(),t=read(); tim=0;
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		E[u].pb(v,w),E[v].pb(u,w);
	}
	scanf("%s",s+1);
	q=read();
	dfs(1,0,0);
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	for(int i=1;i<=19;i++)
		for(int j=1;j<=n;j++)jp[i][j]=jp[i-1][jp[i-1][j]];

	for(int i=1;i<=q;i++){
		a[i]=read(),b[i]=read();
		lca[i]=LCA(a[i],b[i]);
		ans[i]=0;
	}

	for(int o=0;o<=19;o++){
	// for(int o=3;o<=3;o++){
		for(int i=1;i<=n;i++)dis[i]=1e18,vis[i]=0;
		priority_queue<pair<ll,int>,vector<pair<ll,int>>,greater<pair<ll,int>>>Q;

		for(int i=1;i<=n;i++)if(s[i]=='1')dis[i]=0,Q.push({0,i});
		while(!Q.empty()){
			int x=Q.top().se;Q.pop();
			if(vis[x])continue;vis[x]=1;
			for(auto [y,w]:E[x])if(dis[y]>dis[x]+w+(w>>o)){
				dis[y]=dis[x]+w+((w+(1<<o)-1)>>o);
				Q.push({dis[y],y});
			}
		}

		// for(int i=1;i<=n;i++) cout<<dis[i]<<" "; cout<<endl;

		for(int i=2;i<=n;i++){
			int x=seq[i];
			ext[x]=ext[ff[x]]+fv[x]-((fv[x]+(1<<o)-1)>>o);
		}
		val0[0][0]=val1[0][0]=1e18;
		for(int i=1;i<=n;i++) val0[0][i]=dis[i]-ext[i],val1[0][i]=dis[i]+ext[i];
		for(int i=1;i<=19;i++)
			for(int j=0;j<=n;j++)
				val0[i][j]=min(val0[i-1][j],val0[i-1][jp[i-1][j]]),
				val1[i][j]=min(val1[i-1][j],val1[i-1][jp[i-1][j]]);

		for(int i=1;i<=q;i++){
			ll cur=0;

			int xx=a[i];
			for(int j=19;j>=0;j--)if(dfn[jp[j][xx]]>=dfn[ff[lca[i]]])
				chkmin(cur,val0[j][xx]-ext[b[i]]+2*ext[lca[i]]+t*o),xx=jp[j][xx];

			// cout<<"cur="<<cur<<endl;

			xx=b[i];
			for(int j=19;j>=0;j--)if(dfn[jp[j][xx]]>=dfn[lca[i]]){
				// cout<<"at "<<xx<<" jump 2^"<<j<<" val="<<val1[j][xx]<<"-"<<ext[b[i]]<<"+"<<t*o<<endl;
				chkmin(cur,val1[j][xx]-ext[b[i]]+t*o),xx=jp[j][xx];
			}

			// cout<<"at "<<o<<" contri "<<cur<<endl;
			chkmin(ans[i],cur);
		}
	}
	for(int i=1;i<=q;i++){
		printf("%lld\n",ans[i]+dep[a[i]]+dep[b[i]]-2*dep[lca[i]]);
	}
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