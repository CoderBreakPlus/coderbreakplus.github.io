// created time: 2026-04-02 16:21:55
// H. Random Tree Parking
// https://qoj.ac/contest/1459/problem/7864
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
const int B=40;

const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

int n,p[100005],dp[100005][B];
vector<int>E[100005];

int g[B],f[B],sz[100005];
void procedure(){
	n=read();
	for(int i=2;i<=n;i++)p[i]=read(),E[p[i]].pb(i);

	for(int u=n;u>=1;u--){
		sz[u]=1;
		for(auto v:E[u])sz[u]+=sz[v];

		memset(f,0,sizeof(f));f[0]=1;
		for(auto v:E[u]){
			memset(g,0,sizeof(g));
			for(int i=0;i<B;i++)
				for(int j=0;i+j<B;j++)
				g[i+j]=(g[i+j]+1ull*dp[v][i]*f[j])%mod;
			memcpy(f,g,sizeof(f));
		}

		for(int i=0;i<B;i++)
			for(int j=0;i+j<B;j++){
				if(i+j) dp[u][i+j-1]=(dp[u][i+j-1]+1ull*f[i]*inv[j])%mod;
			}

	}
	printf("%d\n",(int)(1ull*dp[1][0]*fac[n]%mod));
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}