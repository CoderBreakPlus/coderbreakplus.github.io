// created time: 2026-06-30 09:33:00
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
const int N=(1<<13)+5;
int n,a[N];

int stk[N][3],tp[N],dp[N][N],v[N][N];

void ins(int i,int j){
	if(dp[i][j]>n)return;
	while(tp[j]&&dp[stk[j][tp[j]]][j]>=dp[i][j]) tp[j]--;
	stk[j][++tp[j]]=i;
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++){
		v[i][i]=a[i];
		for(int j=i+1;j<=n;j++)
			v[i][j]=v[i][j-1]|a[j];
	}
	for(int i=0;i<=n;i++)memset(dp[i],0x3f,sizeof(dp[i]));
	for(int i=0;i<(1<<13);i++) tp[i]=0;
	dp[0][(1<<13)-1]=0;
	ins(0,(1<<13)-1);
	
	for(int i=1;i<=n;i++){
		for(int j=0;j<(1<<13);j++){
			for(int k=1;k<=tp[j];k++){
				int p=stk[j][k];
				chkmin(dp[i][j&v[p+1][i]],dp[p][j]+1);
			}
		}
		for(int j=0;j<(1<<13);j++)ins(i,j);
	}
	if(dp[n][0]<=n)
		printf("%d\n",n-dp[n][0]);
	else puts("-1");
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