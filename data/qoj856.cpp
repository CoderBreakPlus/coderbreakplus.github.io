// created time: 2026-05-20 14:30:02
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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

int n,m,k,dep[300005],seq[300005],vis[300005],t,res;
vector<int>E[300005];

void dfs(int x){
	vis[x]=1;
	for(auto y:E[x]){
		if(vis[y]){
			if(dep[x]-dep[y]>=2){
				// cout<<"here "<<x<<"->"<<y<<endl;
				res-=(seq[++t]=dep[x]-dep[y]+1);
			}
		}else{
			dep[y]=dep[x]+1;
			dfs(y);
		}
	}
}
void procedure(){
	n=read(),res=m=read(),k=read();
	for(int i=1;i<=n;i++)E[i].clear(),vis[i]=dep[i]=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	t=0;
	dfs(1);

	int ans=k,ivk=INV(k);
	for(int i=1;i<=t;i++)
		ans=(ull)ans*(qpow(k-1,seq[i])+((seq[i]&1)?(1-k+mod):(k-1)))%mod*ivk%mod;
	// cout<<"res"<<res<<endl;
	while(res--)ans=(ull)ans*(k-1)%mod;
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