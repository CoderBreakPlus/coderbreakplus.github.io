// created time: 2026-05-14 14:13:09
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int n,d,o[4000005],stk[4000005],vis[4000005],M[4000005],tp;
vector<int>E[4000005];

void procedure(){
	n=read(),d=read();
	for(int i=1;i<=n;i++){
		for(int j=0;j<d;j++)E[i].pb(read()+n);
	}
	for(int i=1;i<=n;i++)o[i]=i;
	shuffle(o+1,o+n+1,rnd);
	
	for(int s=1;s<=n;s++){
		int u=o[s]; tp=0;
		// cout<<"at "<<s<<endl;
		while(u){
			stk[++tp]=u,u=E[u][rnd()%d];
			while(vis[u]) --tp,vis[stk[tp--]]=0;
			stk[++tp]=u,vis[u]=1; u=M[u];
		}
		for(int i=1;i<=tp;i+=2){
			int a=stk[i],b=stk[i+1];
			M[a]=b,M[b]=a;
			vis[a]=vis[b]=0;
		}
	}
	for(int i=1;i<=n;i++) printf("%d ",M[i]-n);
	puts("");
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