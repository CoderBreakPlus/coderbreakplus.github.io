// created time: 2026-10-14 07:03:57
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

int n,a[1<<20],b[1<<20],pop[1<<20],cf[21];

int wa[21][1<<20],wb[21][1<<20],ans[21][1<<20];

void fwt_bit(int *f,int m){
	m=(1<<m);
	for(int i=0;i<(1<<n);i+=(m<<1))
		for(int j=0;j<m;j++) addmod(f[i+m+j]+=f[i+j]);
}

void procedure(){
	n=read();
	for(int i=0;i<(1<<n);i++)a[i]=read(),pop[i]=__builtin_popcount(i);
	for(int i=0;i<(1<<n);i++)b[i]=read();
	
	for(int i=1;i<=n;i++){
		memset(wa,0,sizeof(wa)),memset(wb,0,sizeof(wb));
		for(int j=0;j<(1<<n);j++){
			wa[pop[j]][j]=((j>>i)&1)*a[j];
			wb[pop[j]][j]=(ull)pop[j&((1<<i)-1)]*b[j]%mod;
		}
		for(int v=0;v<=n;v++){
			for(int j=0;j<n;j++) fwt_bit(wa[v],j),fwt_bit(wb[v],j);
			for(int j=0;j<(1<<n);j++)
				ans[v][j]=(ans[v][j]+(ull)wa[v][j]*wb[v][j])%mod;
		}
	}
	for(int v=0;v<=n;v++){
		for(int m=1;m<(1<<n);m<<=1)
			for(int i=0;i<(1<<n);i+=(m<<1))
				for(int j=0;j<m;j++){
					addmod(ans[v][i+m+j]+=mod-ans[v][i+j]);
				}
	}
	for(int i=0;i<(1<<n);i++)
		printf("%d ",ans[pop[i]][i]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}