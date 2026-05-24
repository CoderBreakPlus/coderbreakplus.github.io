// created time: 2026-05-24 18:02:55
// O(n^2) 的，懒得优化了。
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

const int N = 5e4, B = 50;
int n,m,fa[100005],ff[100005],bl[100005],lf[100005],rh[100005],val[100005],bp[100005],lc[100005],rc[100005],dfn[100005],tim,id;
int f[20][100005];
int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]); return fa[x]; }

ll sum[N/B+5][2*N+5],ans[N/B+5][N/B+5];

void dfs(int x,int fa){
	dfn[x]=++tim,f[0][dfn[x]]=fa;
	if(lc[x]) dfs(lc[x],x);
	if(rc[x]) dfs(rc[x],x);
	val[x]-=val[fa];
}
int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
void procedure(){
	n=id=read(),m=read();
	vector<tuple<int,int,int>>vec;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		vec.pb(w,u,v);
	}
	sort(vec.begin(),vec.end());
	for(int i=1;i<=n;i++) fa[i]=i,bl[i]=(i-1)/B+1,rh[bl[i]]=i;
	for(int i=n;i>=1;i--) lf[bl[i]]=i;

	for(auto [w,u,v]: vec){
		u=find(u),v=find(v);
		if(u==v)continue;
		++id; fa[u]=fa[v]=fa[id]=id,val[id]=bp[id]=w;
		// cout<<"link "<<id<<" "<<u<<" "<<v<<endl;
		// cout<<"bp "<<id<<" = "<<bp[id]<<endl;
		lc[id]=u,rc[id]=v; ff[u]=ff[v]=id;
	}
	dfs(id,0);
	for(int i=1;(1<<i)<=id;i++)
		for(int j=1;j<=id-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	for(int i=1;i<=bl[n];i++){
		for(int j=1;j<=rh[i];j++)sum[i][j]=1;
		for(int j=1;j<id;j++)sum[i][ff[j]]+=sum[i][j];
		for(int j=1;j<=id;j++)sum[i][j]*=val[j];
		for(int j=id-1;j>=1;j--)sum[i][j]+=sum[i][ff[j]];
	}
	
	for(int i=1;i<=bl[n];i++){
		for(int j=i;j<=bl[n];j++){
			ans[i][j]=ans[i][j-1];
			for(int k=lf[j];k<=rh[j];k++){
				for(int l=lf[j];l<k;l++)ans[i][j]+=bp[LCA(k,l)];
				ans[i][j]+=sum[j-1][k]-sum[i-1][k];
			}
		}
	}
	ll lst=0;
	m=read();
	while(m--){
		ll l=read(),r=read();
		#ifndef LOCAL
			l^=lst,r^=lst;
		#endif
		lst=0;
		if(bl[l]==bl[r]){
			for(int i=l;i<=r;i++)for(int j=i+1;j<=r;j++){
				lst+=bp[LCA(i,j)];
			}
		}else{
			lst=ans[bl[l]+1][bl[r]-1];
			for(int i=lf[bl[r]];i<=r;i++)lst+=sum[bl[r]-1][i]-sum[bl[l]][i];
			for(int i=l;i<=rh[bl[l]];i++)lst+=sum[bl[r]-1][i]-sum[bl[l]][i];
			
			vector<int>vec;
			for(int i=lf[bl[r]];i<=r;i++)vec.pb(i);
				for(int j=l;j<=rh[bl[l]];j++)vec.pb(j);

			for(int i=0;i<vec.size();i++)
				for(int j=i+1;j<vec.size();j++)
					lst+=bp[LCA(vec[i],vec[j])];
		}
		printf("%lld\n",lst);
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