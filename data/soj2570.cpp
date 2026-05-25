// created time: 2026-05-25 08:09:21
// wqs 二分+整体二分
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

int n,m,fa[100005];
vector<tuple<int,int,int>>g[2];

int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }

const int M=1e6;
ll V1[2000005],V2[2000005];
ll *v1=V1+M;
ll *v2=V2+M;

int findx(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
int mergex(int x,int y){
	if((x=findx(x))==(y=findx(y))) return 0;
	return fa[findx(x)]=findx(y),1;
}
void init(){
	for(int i=1;i<=n;i++)fa[i]=i;
}

tuple<int,int,int> seq[2][200005]; int pt[2];
int ok[2][200005];

namespace dsu{
	int fa[200005], sz[200005];
	int u[200005], v[200005], tp;
	int find(int x){ while(x!=fa[x]) x=fa[x]; return x; }
	bool merge(int x,int y){
		x=find(x),y=find(y);
		if(x==y)return 0;
		if(sz[x]>sz[y])swap(x,y);
		u[++tp]=x, v[tp]=y; sz[y]+=sz[x],fa[x]=y;
		return 1;
	}
	void undo(int x){
		while(tp > x){
			fa[u[tp]] = u[tp];
			sz[v[tp]] -= sz[u[tp]];
			tp --;
		}
	}
	void init(){
		for(int i=1;i<=n;i++) sz[i]=1,fa[i]=i;
	}
}
vector<int>tr[800005];
void solve(int l,int r,int p,int o){
	if(l>r)return;
	int mid=(l+r)>>1, cur=dsu::tp, v=get<0>(seq[o^1][mid]);
	for(int i=l;i<=mid;i++) dsu::merge(get<1>(seq[o^1][i]),get<2>(seq[o^1][i]));

	int cur2=dsu::tp;
	// cout<<"here "<<l<<"->"<<r<<" p="<<p<<" o="<<o<<endl;
	for(auto x: tr[p]){
		if(dsu::merge(get<1>(seq[o][x]), get<2>(seq[o][x]))) tr[p<<1|1].pb(x);
		else{
			tr[p<<1].pb(x), ok[o][x]=v;
			// cout<<"at "<<x<<" v="<<v<<endl;
		}
	}
	dsu::undo(cur2);
	solve(mid+1,r,p<<1|1,o);
	dsu::undo(cur);
	for(auto x: tr[p<<1|1]) dsu::merge(get<1>(seq[o][x]), get<2>(seq[o][x]));
	solve(l,mid-1,p<<1,o);
	dsu::undo(cur);
}
void procedure(){
	n=read(),m=read();
	g[0].clear(),g[1].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read(),o;
		char s[5];scanf("%s",s);
		if(s[0]=='R')o=0;else o=1;
		g[o].pb(w,u,v);
	}
	pt[0]=pt[1]=0;
	for(int o:{0,1}){
		init();
		sort(g[o].begin(), g[o].end());
		for(auto [w,u,v]: g[o]){
			if(findx(u)==findx(v))continue;
			seq[o][++pt[o]]={w,u,v};
			fa[findx(u)]=findx(v);
		}
	}
	for(int o:{0,1})for(int i=1;i<=pt[o];i++)ok[o][i]=2*M;
	for(int i=-M;i<=M;i++) v1[i]=v2[i]=0;


	for(int o:{0,1}){
		dsu::init();
		// for(int i=1;i<=pt[o^1];i++) {
		// 	auto [w,u,v]=seq[o^1][i];
		// 	cout<<w<<","<<u<<","<<v<<" | ";
		// }
		// cout<<endl;
		// for(int i=1;i<=pt[o];i++) {
		// 	auto [w,u,v]=seq[o][i];
		// 	cout<<w<<","<<u<<","<<v<<" | ";
		// }
		// cout<<endl;

		for(int i=1;i<=(n<<2);i++)tr[i].clear();
		for(int i=1;i<=pt[o];i++)tr[1].pb(i);
		solve(1,pt[o^1],1,o);

		// for(int i=1;i<=pt[o];i++) cout<<ok[o][i]<<" ";cout<<endl;

		// for(int i=1;i<=pt[o^1];i++){
		// 	init();
		// 	for(int j=1;j<=i;j++) mergex(get<1>(seq[o^1][j]),get<2>(seq[o^1][j]));
		// 	for(int j=1;j<=pt[o];j++)
		// 		if(!mergex(get<1>(seq[o][j]),get<2>(seq[o][j])))
		// 			chkmin(ok[o][j], get<0>(seq[o^1][i]));
		// }
	}

	for(int i=1;i<=pt[0];i++){
		auto [w,u,v] = seq[0][i];
		ok[0][i]-=w;
		if(ok[0][i]>=-M)
			v1[-M]+=w,v1[min(M+1,ok[0][i])]-=w,
			v2[-M]++,v2[min(M+1,ok[0][i])]--;
	}

	for(int i=1;i<=pt[1];i++){
		auto [w,u,v] = seq[1][i];
		ok[1][i]=max(-M,w-ok[1][i]);
		if(ok[1][i]<=M)v1[ok[1][i]]+=w;
	}
	for(int i=-M+1;i<=M;i++){
		v1[i]+=v1[i-1];
		v2[i]+=v2[i-1];
	}
	for(int i=-M;i<=M;i++){
		v1[i]+=(ll)v2[i]*i;
	}

	int L=v2[M], R=v2[-M];
	for(int k=0;k<n;k++){
		if(k>R||k<L){
			printf("-1 ");
			continue;
		}
		int l=-M,r=M;
		while(l+1<r){
			int mid=(l+r)>>1;
			if(v2[mid]>k) l=mid;
			else r=mid;  
		}
		ll a1=v1[l],a2=v1[r];
		printf("%lld ", max(a1-(ll)l*k, a2-(ll)r*k));
	}
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