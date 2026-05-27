// created time: 2026-05-27 07:40:34
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

int n,m,f[1<<8][1<<8],g[1<<8][1<<8],e0[1<<8][1<<8],e1[1<<8][1<<8],e[8][8];

void procedure(){
	n=read(),m=read();
	for(int i=0;i<n;i++)for(int j=0;j<m;j++)
		e[i][j]=read()*INV(100)%mod;
	
	for(int i=0;i<(1<<n);i++)
		for(int j=0;j<(1<<m);j++){
			e0[i][j]=1,e1[i][j]=1;
			for(int k=0;k<n;k++)if((i>>k)&1){
				for(int l=0;l<m;l++)if((j>>l)&1)
					e0[i][j]=(ull)e0[i][j]*(mod+1-e[k][l])%mod;
			}
			for(int l=0;l<m;l++)if((j>>l)&1){
				int f=1;
				for(int k=0;k<n;k++)if((i>>k)&1)
					f=(ull)f*(mod+1-e[k][l])%mod;
				e1[i][j]=(ull)e1[i][j]*(mod+1-f)%mod;
			}
		}
	memset(f,0,sizeof(f));memset(g,0,sizeof(g));
	for(int i=0;i<(1<<n);i++)
		for(int j=0;j<(1<<m);j++){
			int tot=e1[i][j];
			for(int s=i;;s=(s-1)&i){
				for(int t=j;;t=(t-1)&j){
					tot=(tot+(ull)(mod-g[s][t])*f[i^s][j^t]%mod*e0[s][j^t])%mod;
					if(!t)break;
				}
				if(!s)break;
			}
			if(!tot)continue;
			if(__builtin_popcount(i)<=__builtin_popcount(j)){
				f[i][j]=tot;
			}else{
				g[i][j]=tot;
			}
		}
	g[0][0]=1;
	int tot=0,N=(1<<n)-1,M=(1<<m)-1;
	for(int i=0;i<=N;i++)
		for(int j=0;j<=M;j++){
			for(int t=(M^j);;t=(t-1)&(M^j)){
				int cur=(ull)g[i][j]*f[N^i][M^j^t]%mod*e0[N^i][t]%mod*e0[i][M^j]%mod*(n+__builtin_popcount(j)-__builtin_popcount(i))%mod;
				addmod(tot+=cur);
				if(!t)break;
			}
		}
	printf("%d\n",tot);
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