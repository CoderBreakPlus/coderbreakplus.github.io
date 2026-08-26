// created time: 2026-08-26 07:53:02
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

int m,v;
int f[505][505][2],g[505][505][2];

inline void upd(int &a,ull b){ a=(a+b)%mod; }

inline int sum(int l,int r){
	if(l>r)return 0;
	return (l+r)*(r-l+1)/2;
}
void procedure(){
	m=read(),v=read();
	for(int i=1;i<=v;i++)
		f[0][i][0]=1;
	f[0][v][1]=1;

	int sz=0;
	for(int t=1;t<=m;t++){
		int x=read();
		memset(g,0,sizeof(g));
		if(x==1){
			int l=read(),r=read();
			for(int i=0;i<=sz;i++)
			for(int j=1;j<=v;j++){
				upd(g[i+1][j][0], (ull)min(r-l+1,max(0,j-l))*f[i][j][0]);
				upd(g[i+1][j][1], (ull)min(r-l+1,max(0,j+1-l))*f[i][j][1]);

				upd(g[i][j][0], (ull)sum(max(j,l),r)*f[i][j][0]);
				upd(g[i][j][1], (ull)sum(max(j+1,l),r)*f[i][j][1]);
								
				if(l<=j&&j<=r) upd(g[i][j][1],(ull)j*f[i][j][0]);
			}
			sz++;
		}else{
			for(int i=2;i<=sz;i++)
			for(int j=1;j<=v;j++)for(int o:{0,1})
				addmod(g[i-1][j][o]+=f[i][j][o]);

			for(int j=1;j<=v;j++){
				addmod(g[0][j][0]+=f[1][j][1]);
				addmod(g[0][j][1]+=f[1][j][1]);
				for(int k=1;k<j;k++)
					addmod(g[0][k][0]+=f[1][j][1]);
			}
			sz--;
		}
		memcpy(f,g,sizeof(f));
	}
	int ans=0;
	for(int k=1;k<=v;k++)
		addmod(ans+=f[0][k][1]);
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