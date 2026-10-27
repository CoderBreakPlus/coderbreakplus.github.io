// created time: 2026-10-27 09:59:07
// #pragma GCC optimize(3,"inline")
// #pragma GCC optimize("Ofast,unroll-loops")
// #pragma GCC target("avx,avx2")
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
const int N=8005;
int L,c[N],n,x[N];

namespace DP{
	const int M=8005;
	int f[2][M][M],g[M][M],h[M][M];
	vector<int>v2[M];

	void main(){
		for(int i=1;i<=L;i++)v2[i].pb(0),c[i]=min(c[i],n+1);
		for(int i=1;i<=n;i++)v2[x[i]+1].pb(i);
		for(int i=1;i<=L;i++)v2[i].pb(n+1);

		for(int i=1;i<=L;i++){
			int cnt=(int)v2[i].size()-2;
			if(i<L)cnt+=(int)v2[i+1].size()-2;
			c[i]=min(c[i],cnt+1);
		}

		for(int i=0;i<=c[1];i++)
			memset(f[1][i],0xc0,sizeof(int)*2);
		f[1][0][0]=0;
		f[1][c[1]][1]=0;

		for(int i=2,o=0;i<=L;i++,o^=1){
			int sz=(int)v2[i].size()-1;
			for(int j=0;j<=c[i];j++){
				memset(f[o][j],0xc0,sizeof(int)*(sz+2));
				memset(g[j],0xc0,sizeof(int)*(sz+2));
				memset(h[j],0xc0,sizeof(int)*(sz+2));
			}
			for(int j=0;j<=c[i-1];j++){
				int low=v2[i-1].size();
				int ptl=1,ptr=0;
				for(int k=0;k<low;k++){
					if(f[o^1][j][k]<-1e9)continue;
					int l=k?v2[i-1][k-1]:0,r=k?v2[i-1][k]-1:0;

					while(ptr<=sz&&v2[i][ptr+1]<=r)ptr++;
					while(ptl<=sz&&v2[i][ptl]<=l)ptl++;

					int cnt=sz-ptl;
					if(cnt<j)continue;

					chkmax(f[o][0][0],f[o^1][j][k]);
					int mx=min(ptr,sz-j);
					chkmax(g[max(0,c[i]-sz+mx+j)][mx],f[o^1][j][k]+mx-1);

					for(int x=ptl;x<=min(sz-j,ptr+1);x++){
						int t=v2[i][x];
						chkmax(h[max(c[i]-sz+x+j,0)][x],f[o^1][j][k]+x-1);
					}
				}
			}
			for(int j=c[i];j>=0;j--)
				for(int k=sz;k>=1;k--){
					chkmax(f[o][j][k],g[j][k]);
					if(k>1)chkmax(g[max(j-1,0)][k-1],g[j][k]-1);
				}
			for(int j=0;j<c[i];j++)
				for(int k=0;k<=sz;k++)chkmax(h[j+1][k],h[j][k]);
			for(int j=0;j<=c[i];j++)
				for(int k=0;k<=sz-c[i]+j;k++){
					chkmax(f[o][j][k],h[j][k]);
					if(k<sz)chkmax(h[j][k+1],h[j][k]);
				}
		}
		int ans=0;
		for(int k=0;k<(int)v2[L].size();k++)
			chkmax(ans,f[L&1][0][k]);
		printf("%d\n",ans);
	}
}
void procedure(){
	L=read();
	for(int i=1;i<=L;i++) c[i]=read();
	n=read();
	for(int i=1;i<=n;i++) x[i]=read();
	reverse(x+1,x+n+1);
	DP::main();
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