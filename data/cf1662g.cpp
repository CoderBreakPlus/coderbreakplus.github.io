// created time: 2026-05-03 08:24:10
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }
vector<int>E[1000005];
int n,p[1000005],sz[1000005],rt,mxs[1000005];
void dfs(int x,int fa){
	sz[x]=1;
	for(auto y:E[x]){
		if(y==fa)continue;
		dfs(y,x),sz[x]+=sz[y];
		mxs[x]=max(mxs[x],sz[y]);
	}
	mxs[x]=max(mxs[x],n-sz[x]);
	if(!rt||mxs[x]<mxs[rt])rt=x;
}
int ton[1000005];
bitset<1000005>b;
ll ans;

void dfs(int x,int fa,int d){
	ans+=d;
	for(auto y:E[x])if(y!=fa){
		dfs(y,x,d+1);
	}
}
void procedure(){
	n=read();
	for(int i=2;i<=n;i++){
		p[i]=read();
		E[p[i]].pb(i),E[i].pb(p[i]);
	}	
	dfs(1,0);
	// cout<<"rt="<<rt<<endl;
	for(auto i:E[rt]){
		int b;
		if(sz[i]>sz[rt]) b=n-sz[rt];
		else b=sz[i];
		ton[b]++;
		// cout<<"b="<<b<<endl;
	}
	for(int i=1;i<n;i++){
		if(ton[i]>=3) {
			int d=(ton[i]-1)/2;
			ton[i]-=2*d,ton[2*i]+=d;
		}
	}
	dfs(rt,0,1);
	b[0]=1;
	for(int i=1;i<n;i++){
		// if(ton[i]) cout<<i<<" cnt="<<ton[i]<<endl;
		while(ton[i]--)b|=(b<<i);
	}
	int ok=0;


	for(int i=0;i<n;i++){
		if(b[i]&&max(2*i-(n-1),(n-1)-2*i)<max(2*ok-(n-1),(n-1)-2*ok))
			ok=i;
	}
	// cout<<"ok="<<ok<<endl;
	printf("%lld\n",(ll)ok*(n-1-ok)+ans);
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