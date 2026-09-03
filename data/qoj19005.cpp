// created time: 2026-09-03 09:57:22
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

int n,q,a[100005],val[100005],seq[100005],tl,out[100005];

int ok[10005],idx;
ll sum;
bool vis[5000005];
int fk[5000005];
vector<pair<int,int>>E[100005];

void dfs(int x,int fa){
	if(fa) val[x]=seq[++tl],fk[seq[tl]]=x;
	sum+=(ull)val[x]*a[x];
	for(auto [y,i]:E[x]){
		if(y==fa)continue;
		dfs(y,x);
		out[i]=val[y]-val[x];
	}
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v,i),E[v].pb(u,i);
	}	
	dfs(1,0);
	for(int i=1;i<n;i++)printf("%d\n",out[i]); fflush(stdout);

	while(q--){
		printf("? 1\n"); fflush(stdout);
		ll x=read()-sum;

		ll w=1;
		if(x<0)x=-x,w=-w;

		// cout<<"x="<<x<<endl;
		for(int i=1;i<=idx;i++){
			while(x%ok[i]==0){
				x/=ok[i],w*=ok[i];
			}
		}
		int node=fk[x];
		printf("! %d %d\n", node, a[node]+w); fflush(stdout);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif

	for(int i=2;i<=5e6;i++){
		if(!vis[i]){
			for(int j=2*i;j<=5e6;j+=i) vis[j]=1;
		}
	}
	for(int i=2;i<=1e4;i++){
		if(!vis[i]) ok[++idx]=i;
	}
	for(int i=1e4+1;i<=5e6;i++){
		if(!vis[i]){
			seq[++tl]=i;
			if(tl==1e5)break;
		}
	}
	tl=0;
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}