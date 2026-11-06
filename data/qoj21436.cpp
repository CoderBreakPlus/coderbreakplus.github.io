// created time: 2026-11-05 08:29:20
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
const int N=21;
int n,e[N][N];
int f[1<<N][N],ans[N][N];

inline void upd(int &x,ull w){ x=(x+w)%mod; }

int dp[1<<N][N][2],h[1<<N];

void procedure(){
	n=read();
	int m=read();
	while(m--){
		int u=read()-1,v=read()-1,w=read();
		e[u][v]=w;
	}
	for(int i=0;i<(1<<n);i++)h[i]=read();
	// mt19937 rnd(read());
	// for(int i=0;i<(1<<n);i++)h[i]=rnd()%mod;
	for(int i=0;i<n;i++){
		for(int j=(1<<i);j<(1<<i+1);j++){
			for(int k=0;k<i;k++)if((j>>k)&1){
				upd(dp[j][k][0],(ull)h[j]*e[k][i]);
				upd(dp[j][k][1],(ull)h[j]*e[i][k]);
			}
		}
	}
	for(int j=(1<<n)-1;j>=1;j--){
		int x=__builtin_popcount(j);
		if(x==1)continue;
		int t=lg2(j),t2=lg2(j^(1<<t));
		for(int k=0;k<t;k++)if((j>>k)&1){
			// t moved
			if(k==t2){
				int tmp=j,l=__builtin_ctz(tmp);
				while(l<t2){
					upd(dp[j^(1<<t)][l][1],(ull)dp[j][k][0]*e[t][l]);
					upd(dp[j^(1<<t)][l][0],(ull)dp[j][k][1]*e[l][t]);
					tmp^=(1<<l),l=__builtin_ctz(tmp);
				}
			}
			// t not moved
			int tmp=j&(~(1<<k)),l=__builtin_ctz(tmp);
			while(l<t){
				upd(dp[j^(1<<k)][l][0],(ull)dp[j][k][0]*e[l][k]);
				upd(dp[j^(1<<k)][l][1],(ull)dp[j][k][1]*e[k][l]);
				tmp^=(1<<l),l=__builtin_ctz(tmp);
			}
		}
	}
	for(int s=0;s<n;s++)
		for(int t=0;t<n;t++)if(s!=t){
			if(s<t)
				addmod(ans[s][t]+=dp[(1<<s)|(1<<t)][s][0]);
			else
				addmod(ans[s][t]+=dp[(1<<s)|(1<<t)][t][1]);
		}
	for(int s=0;s<n;s++){
		ans[s][s]=h[1<<s];
		for(int t=0;t<n;t++)if(s!=t)
			upd(ans[s][s],(ull)e[s][t]*ans[t][s]);
	}
	for(int x=0;x<n;x++){
		for(int y=0;y<n;y++){
			printf("%d ",ans[x][y]);
		}
		puts("");
	}
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