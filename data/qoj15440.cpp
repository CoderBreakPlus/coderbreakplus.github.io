// created time: 2026-09-10 08:22:15
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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

int n,m,p[505][505],ip[505][505],f[505][505],g[505][505];
int sl[505],sr[505];

bool chk[505][505];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		for(int j=1;j<=n;j++)p[i][j]=read(),ip[i][p[i][j]]=j;
	}
	for(int l=1;l<=n;l++){
		memset(sl,0x3f,sizeof(sl));
		memset(sr,0xc0,sizeof(sr));
		for(int r=l;r<=n;r++){
			chk[l][r]=1;
			for(int i=1;i<=m;i++){
				chkmin(sl[i],ip[i][p[1][r]]),chkmax(sr[i],ip[i][p[1][r]]);
				chk[l][r]&=(p[i][sl[i]]==p[1][l]);
				chk[l][r]&=(r-l==sr[i]-sl[i]);
			}
		}
	}
	for(int i=1;i<=n+1;i++)g[i][i-1]=1;
	for(int l=n;l>=1;l--)
		for(int r=l;r<=n;r++){
			if(chk[l][r]) f[l][r]=g[l+1][r];
			for(int k=l;k<=r;k++)
				g[l][r]=(g[l][r]+(ull)g[l][k-1]*f[k][r])%mod;
		}

	printf("%d\n",f[1][n]);
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