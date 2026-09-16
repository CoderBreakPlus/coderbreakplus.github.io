// created time: 2026-09-16 19:04:00
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

int n,m,f[2][1<<19];

int tr[1<<19][20];
int s[205][20];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)s[i][j]=read();

	f[0][0]=1;

	for(int j=0;j<(1<<m);j++){
		for(int k=1;k<=m;k++){
			int j2=0;
			for(int x=0;x<k-1;x++)if((j>>x)&1)j2^=(1<<k-x-2);
			tr[j][k]=(j2|(1<<k-1));
		}
	}
	for(int i=1,o=1;i<=n;i++,o^=1){
		memset(f[o],0,sizeof(f[o]));

		for(int k=m;k>=1;k--){
			if(s[i][k])
				for(int j=0;j<(1<<k-1);j++)addmod(f[o][tr[j][k]]+=f[o^1][j]);

			for(int j=0;j<(1<<k-1);j++)addmod(f[o^1][j]+=f[o^1][j^(1<<k-1)]);
		}
	}
	int ans=0;
	for(int j=0;j<(1<<m);j++)addmod(ans+=f[n&1][j]);
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