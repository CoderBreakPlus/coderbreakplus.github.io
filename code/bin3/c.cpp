// created time: 2026-11-02 07:36:06
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

int n,m;
const int M=5050;
int dp[105][105][M+5],f[105],g[105];
map<int,int>mp;

void procedure(){
	n=read(),m=read();
	mp.clear();
	mp[1]=0;
	bool flg=0;
	while(m--){
		int x=read(),y=read();
		if(mp.count(x)&&mp[x]!=y)
			flg=1;
		mp[x]=y;
	}
	if(flg){ puts("0"); return; }
	memset(f,0,sizeof(f));
	f[0]=1;
	int A=1,B=0;
	for(auto [a,b]: mp){
		// cout<<"here "<<a<<" "<<b<<endl;
		if(a>1){
			memset(g,0,sizeof(g));
			for(int i=0;i<=n;i++)
				for(int j=0;j<=a-A;j++){
					int res=(b-B)-(a-A)*i;
					if(res>M||res<0)continue;
					g[i+j]=(g[i+j]+(ull)f[i]*dp[a-A][j][res])%mod;
				}
			memcpy(f,g,sizeof(f));
		}
		A=a,B=b;
	}
	int ans=0;
	for(int i=0;i<=n;i++)addmod(ans+=f[i]);
	ans=ans*qpow(2,n-A)%mod;
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	math_init();
	dp[0][0][0]=1;
	for(int i=0;i<100;i++){
		for(int j=0;j<=i;j++)for(int k=0;k<=i*(i+1)/2;k++){
			addmod(dp[i+1][j+1][k+j+1]+=dp[i][j][k]);
			addmod(dp[i+1][j][k+j]+=dp[i][j][k]);
		}
	}
	while(T--) procedure();
	return 0;
}