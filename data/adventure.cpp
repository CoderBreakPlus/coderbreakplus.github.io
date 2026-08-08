// created time: 2026-08-03 18:40:09
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

vector<int>E[200005];
int n,m,q,h[200005],ex[200005];
int fa[20][200005],mn[20][200005];
ll sum[20][200005];

int find(int i,int x){
	// cout<<i<<" "<<x<<endl;
	// assert(i<20);
	if(x==fa[i][x])return x;
	return fa[i][x]=find(i,fa[i][x]);
}
void merge(int i,int x,int y){
	// assert(i<20);
	x=find(i,x),y=find(i,y);
	if(x==y)return;
	fa[i][x]=y,sum[i][y]+=sum[i][x];
}

ll solve(int x,int y){
	if(!ex[x]){
		if(y<h[x]) return y;
	}else{
		if(y<ex[x]) return y;
		if(y+ex[x]<h[x]) return y+ex[x];
	}
	ll now=h[x];
	for(int j=0;j<19;j++){
		int l=(1<<j),r=(1<<j+1)-1,fx=find(j+1,x);
		if(y+now>=r){
			now=sum[j+1][fx];
			continue;
		}
		if(y+now<mn[j][find(j,x)]) return y+now;
		now=sum[j+1][fx];
	}
	return y+now;
}
bool vis[200005];
void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++){
		h[i]=read();
		for(int j=0;j<20;j++)fa[j][i]=i,sum[j][i]=h[i],mn[j][i]=1e9;
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		E[x].pb(y),E[y].pb(x);
	}
	// 第 j 层，所有 <2^j 的点之间连边，考虑向 2^j~2^j+1 扩展
	for(int j=0;j<20;j++){
		int l=(1<<j),r=(1<<j+1)-1;
		for(int u=1;u<=n;u++){
			if(h[u]<l)
				for(int v:E[u]) if(h[v]<l) merge(j,u,v);
		}
		for(int u=1;u<=n;u++){
			if(l<=h[u]&&h[u]<=r)
				for(int v:E[u]) chkmin(mn[j][find(j,v)],h[u]);
		}
	}
	while(q--){
		int o=read(),x=read(),y=read();
		if(o==1){
			ex[x]=y;
			for(int j=0;j<20;j++){
				int l=(1<<j),r=(1<<j+1)-1;
				if(l<=ex[x]&&ex[x]<=r) {
					chkmin(mn[j][find(j,x)],ex[x]);
					for(int y:E[x])
						chkmin(mn[j][find(j,y)],ex[x]);
				}else{
					auto sb1 = [&](int u){
						u=find(j,u);
						if(vis[u])return; vis[u]=1;
						sum[j][u]+=ex[x];
					};
					auto sb2 = [&](int u){
						u=find(j,u);
						vis[u]=0;
					};
					sb1(x);
					for(int y:E[x]) sb1(y);
					sb2(x);
					for(int y:E[x]) sb2(y);
				}
			}
		}else{
			printf("%lld\n",solve(x,y));
		}
	}
}
int main(){
	assert(freopen("test.in","r",stdin));
	assert(freopen("test.out","w",stdout));
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}