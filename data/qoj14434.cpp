// created time: 2026-06-07 10:06:00
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
const int M = 15;
int b[1<<4][1<<4][1<<4];
int MEX(int x,int y,int z){
	for(int i=0;i<4;i++){
		if((x==i)||(y==i)||(z==i))continue;
		return i;
	}
}
int n,a[500005],f[500005][M+1],dp[500005][4],qz[500005][4];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),f[i][1]=(1<<min(3,a[i]));
	for(int i=0;i<(1<<4);i++)
	for(int j=0;j<(1<<4);j++)
	for(int k=0;k<(1<<4);k++)
		for(int x=0;x<4;x++)for(int y=0;y<4;y++)for(int z=0;z<4;z++)
		if((i>>x)&(j>>y)&(k>>z)&1)
			b[i][j][k]|=(1<<MEX(x,y,z));

	for(int k=1;k<=M;k+=2)
		for(int i=1;i<=n-k+1;i++)
			for(int p=1;p+2<=k;p+=2)for(int q=1;p+q+1<=k;q+=2)
				f[i][k]|=b[f[i][p]][f[i+p][q]][f[i+p+q][k-p-q]];

	memset(dp,0xc0,sizeof(dp)),memset(qz,0xc0,sizeof(qz));
	dp[0][0]=qz[0][0]=0;
	for(int i=1;i<=n;i++)for(int o=0;o<4;o++){
		for(int k=1;k<=M&&k<=i;k+=2){
			if(k==1&&a[i]>3)continue;
			if((f[i-k+1][k]>>o)&1)
				for(int p=0;p<=o;p++)chkmax(dp[i][o],dp[i-k][p]+1);
		}

		if(i>=M+2)
			for(int p=0;p<=o;p++)chkmax(dp[i][o],qz[i-M-2][p]+1);

		qz[i][o]=dp[i][o];
		if(i>=2)chkmax(qz[i][o],qz[i-2][o]);
	}
	
	int ans=2*n;
	a[n+1]=2e9;
	for(int i=n;i>=0;i--){
		for(int o=0;o<4&&o<=a[i+1];o++)
			if(dp[i][o]>=0){
				chkmin(ans,(i-dp[i][o])/2);
			}
		if(!i||a[i]<a[i-1])break;
	}
	printf("%d\n",ans>n?-1:ans);
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