// created time: 2026-09-11 15:39:30
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

int n,m,f[505][255][130];
char s[505];

void procedure(){
	n=read(),m=n/4;
	scanf("%s",s+1);
	f[n+1][0][0]=1;
	for(int i=n;i>=1;i--)for(int j=0;j<=m;j++)for(int k=0;k<=2*m;k++){
		if(s[i]!='1') addmod(f[i][j][k+1]+=f[i+1][j][k]);
		if(s[i]!='0'&&i>1&&s[i-1]!='1'&&k>=2) addmod(f[i-1][j+1][max(k-2,1)]+=f[i+1][j][k]);
	}
	int ans=0;
	for(int i=0;i<=2*m;i++)
		addmod(ans+=f[1][m][i]);
	printf("%d\n",ans);
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