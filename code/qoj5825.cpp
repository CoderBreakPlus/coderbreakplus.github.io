// created time: 2026-05-15 15:28:54
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

const int W = 10;
int n,A[3005][3005],B[3005][3005],C[3005][3005];
int M[3005][W],M1[3005][W],M2[3005][W],M3[3005][W];

mt19937 rnd(chrono::steady_clock::now().time_since_epoch().count());
void procedure(){
	n=read();
	memset(M1,0,sizeof(M1));memset(M2,0,sizeof(M2));memset(M3,0,sizeof(M3));
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)B[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)C[i][j]=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)A[i][j]=read();

	for(int i=1;i<=n;i++)
		for(int j=0;j<W;j++)M[i][j]=1;

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=0;k<W;k++)
				M3[i][k]=(M3[i][k]+(ull)C[i][j]*M[j][k])%mod;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=0;k<W;k++)
				M2[i][k]=(M2[i][k]+(ull)B[i][j]*M3[j][k])%mod;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			for(int k=0;k<W;k++)
				M1[i][k]=(M1[i][k]+(ull)A[i][j]*M[j][k])%mod;
	// for(int i=1;i<=n;i++)
	// 	{for(int j=0;j<W;j++) printf("%d ",M1[i][j]); puts("");}
	// for(int i=1;i<=n;i++)
	// 	{for(int j=0;j<W;j++) printf("%d ",M2[i][j]); puts("");}
	for(int i=1;i<=n;i++)
		for(int j=0;j<W;j++)
			if(M1[i][j]!=M2[i][j]){puts("No");return;}
	puts("Yes");
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