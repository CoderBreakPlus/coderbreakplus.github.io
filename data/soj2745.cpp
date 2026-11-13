// created time: 2026-11-13 19:23:50
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
int n,a[25],b[25];

ll sa[1<<25],sb[1<<25];
bitset<1<<25>vis;
void procedure(){
	n=read();
	for(int i=0;i<n;i++){
		a[i]=read(),b[i]=read();
		sa[1<<i]=a[i];
		sb[1<<i]=b[i];
	}
	for(int i=1;i<(1<<n);i++){
		sa[i]=sa[i&-i]+sa[(i&-i)^i];
		sb[i]=sb[i&-i]+sb[(i&-i)^i];
	}
	if(sb[(1<<n)-1]<=0){
		puts("0");
		return;
	}
	sa[0]=1;
	for(int i=0;i<(1<<n);i++){
		vis[i]=(sa[i]<=0&&(i==(1<<n)-1||sb[(1<<n)-1]-sb[i]>0));
	}

	for(int i=1;i<(1<<n);i++)if(vis[i]){
		int now=i;
		ull sum=0;
		while(now){
			int j=__builtin_ctz(now);now^=(1<<j);
			sum+=sa[i^(1<<j)];
		}
		sa[i]=sum%mod;
	}
	printf("%d\n",sa[(1<<n)-1]);
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