// created time: 2026-09-11 08:29:19
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

int n,m,a[1005],b[1005],u[2005],v[2005];

vector<pair<int,int>>E[1005];

bool act[1005],vis[1005],vis2[1005];
int prv[1005];

vector<int> add;
int res, cur;
bool dfs(int x,int i,ll hp){
	if(res==cur){
		int z=x;
		while(z) add.pb(z),z=prv[z];
		return 1;
	}
	for(auto [y,j]: E[x])if(j!=i){
		if(act[y]) {
			int z=x;
			while(z) add.pb(z),z=prv[z];
			return 1;
		}
		if(hp<=a[y])continue;
		if(vis[y]){
			int z=x;
			while(z) add.pb(z),z=prv[z];
			if(!vis2[y]){
				z=y;
				while(z) add.pb(z),z=prv[z];
			}
			return 1;
		}
		cur++,vis[y]=1,vis2[y]=1,prv[y]=x;
		if(dfs(y,j,hp+b[y])) return 1;
		cur--,vis2[y]=0,prv[y]=0;
	}
	return 0;
}

bool ok(){ for(int i=1;i<=n;i++)if(!act[i])return 0; return 1; }
bool check(ll hp){
	memset(act,0,sizeof(act));
	act[1]=1;
	while(!ok()){
		bool flg=0; add.clear();
		res=cur=0;
		for(int i=1;i<=n;i++)if(!act[i])res++;
		for(int i=1;i<=n;i++)
		memset(vis,0,sizeof(vis));
		memset(prv,0,sizeof(prv));

		int tim=0;
		for(int x=1;x<=n;x++)if(act[x]){
			for(auto [y,i]:E[x])if(!act[y] && !vis[y] && hp>a[y]){
				vis[y]=vis2[y]=1;
				cur++;
				if(dfs(y,i,hp+b[y])){
					flg=1; break;
				}
				cur--;
				vis2[y]=0;
			}
			if(flg) break;
		}
		if(!flg)return 0;
		for(int x: add){
			act[x]=1, hp+=b[x];
		}
	}
	return 1;
}
void procedure(){
	n=read(),m=read();
	for(int i=2;i<=n;i++)a[i]=read();
	for(int i=2;i<=n;i++)b[i]=read();
	for(int i=1;i<=n;i++) E[i].clear();

	for(int i=1;i<=m;i++){
		u[i]=read(),v[i]=read();
		E[u[i]].pb(v[i],i),E[v[i]].pb(u[i],i);
	}
	int L=1,R=1e9,ans=1e9+1;
	while(L<=R){
		int mid=(L+R)>>1;
		if(check(mid)) ans=mid,R=mid-1;
		else L=mid+1;
	}

	printf("%d\n",ans);
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