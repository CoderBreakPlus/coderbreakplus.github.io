// created time: 2026-04-07 14:19:55
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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

int n,m,a[21];
ull f[22][1<<21],g[1<<21];

int lowbit(int x){ return x&-x; }

void procedure(){
	n=read(),m=read();
	memset(a,0,sizeof(a));
	for(int i=0;i<m;i++)a[read()-1]=1;

	f[0][0]=1;
	for(int v=0;v<n;v++){
		if(!a[v]){
			memset(f[v+1],0,sizeof(ull)<<v+1);
			for(int x=v;x>=0;x--){
				memset(g,0,sizeof(ull)<<v+1);
				for(int i=0;i<(1<<v);i++){
					if(!f[x][i])continue;
					for(int k=0;k<=v;k++){
						int to=(i>>k<<k+1)^(i&((1<<k)-1));
						to^=lowbit(i>>k<<k+1)^(1<<k);
						if(x>k) f[x+1][to]+=f[x][i];
						else g[to]+=f[x][i];
					}
				}
				memcpy(f[x],g,sizeof(ull)<<v+1);
			}
		}else{
			for(int i=0;i<=v;i++) memset(f[i]+(1<<v),0,sizeof(ull)<<v);
			memset(f[v+1],0,sizeof(ull)<<v+1);
			for(int x=v;x>=0;x--)for(int i=0;i<(1<<v);i++){
				if(!f[x][i])continue;
				for(int k=x;k<=v;k++){
					int to=(i>>k<<k+1)^(i&((1<<k)-1));
					to^=lowbit(i>>k<<k+1)^(1<<k);
					f[k+1][to]+=f[x][i];
				}
				f[x][i]=0;
			}
		}
	}
	ull ans=0;
	for(int x=0;x<=n;x++)
		for(int i=0;i<(1<<n);i++)
			if(__builtin_popcount(i)==m) ans+=f[x][i];
	printf("%llu\n",ans);
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