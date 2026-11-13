// created time: 2026-11-13 08:26:44
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

int n,m,e[20];
ll f[1<<20],g[1<<20],ans[20][20];

void procedure(){
	n=read(),m=read();
	for(int i=0;i<n;i++){
		e[i]=0;
		for(int j=0;j<n;j++)ans[i][j]=0;
	}
	for(int i=0;i<(1<<n);i++)f[i]=g[i]=0;

	for(int i=1;i<=m;i++){
		int u=read()-1,v=read()-1;
		e[v]|=(1<<u);
	}

	g[0]=1;
	for(int i=1;i<(1<<n);i++)
		for(int j=0;j<n;j++)if((i>>j)&1)
			if(!(e[j]&i))g[i]+=g[i^(1<<j)];

	f[(1<<n)-1]=1;
	for(int i=(1<<n)-1;i>=1;i--)
		for(int j=0;j<n;j++)if((i>>j)&1)
			if(!(e[j]&i))f[i^(1<<j)]+=f[i];

	for(int i=(1<<n)-1;i>=1;i--){
		for(int k=0;k<n;k++)if((i>>k)&1)
			if(!(e[k]&i)){
				ll val=f[i]*g[i^(1<<k)];
				if(!val)continue;
				for(int l=0;l<n;l++)if((~i>>l)&1)
					ans[k][l]+=val;
			}
	}
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++)printf("%lld ",ans[i][j]);
		puts("");
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