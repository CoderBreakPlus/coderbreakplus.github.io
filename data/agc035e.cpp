// created time: 2026-11-11 14:22:04
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int mod;
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

int n,k;
const int M=80;
int dp[M][M];
void solve0(){
	int dist=k/2;
	dp[0][0]=1;
	for(int i=0;i<(n+1)/2;i++){
		for(int j=0;j<=i;j++){
			if(i+1-j<=dist)addmod(dp[i+1][j]+=dp[i][j]);
			addmod(dp[i+1][i+1]+=dp[i][j]);
		}
	}
	auto count=[&](int x){
		int ret=0;
		for(int j=0;j<=x;j++)addmod(ret+=dp[x][j]);
		return ret;
	};
	printf("%d\n",(ull)count(n/2)*count((n+1)/2)%mod);
}
int f[2][M][M][M][M];

void solve1(){
	int dem=(k+1)/2;
	f[0][0][0][0][0]=1;
	int ans=0;
	for(int i=0,o=0;i<=n;i++,o^=1){
		memset(f[o^1],0,sizeof(f[o^1]));
		for(int s0=0;s0<=(i+1)/2;s0++)for(int t0=0;t0<=(n-i+2)/2;t0++)
		for(int s1=0;s1<=i/2;s1++)for(int t1=0;t1<=(n-i+3)/2;t1++){
			int &F=f[o][s0][t0][s1][t1];
			if(s0&&t1>=2&&min(s0,t0)+min(s1,t1-1)>dem)F=0;
			if(!F)continue;

			if(i==n){
				if(t0<=1&&t1<=1)addmod(ans+=F);
				continue;
			}

			int S1=s0,T1=t0;
			if(s1){
				int S0=s1+1,T0=t1-1;
				if(!T0)S0=0;
				addmod(f[o^1][S0][T0][S1][T1]+=F);
			}else{
				addmod(f[o^1][0][0][S1][T1]+=F);
				for(int x=1;x<=(n-i+1)/2;x++)
					addmod(f[o^1][1][x][S1][T1]+=F);
			}
		}
	}
	printf("%d\n",ans);
}
void procedure(){
	n=read(),k=read(),mod=read();
	if(k&1){
		solve1();
	}else{
		solve0();
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