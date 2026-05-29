// created time: 2026-05-29 09:23:56
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
const int B=300;

int a,b,m,f[200005],g[200005],pw[200005],iv[200005];
int qz[B+5][200005];


void procedure(){	
	a=read(),b=read(),m=read();
	memset(f,0,sizeof(int)*(a+1));
	for(int i=0;i<=B;i++)
		memset(qz[i],0,sizeof(int)*(a+1));

	f[b]=1;
	for(int j=b;j<=a;j++){
		for(int l=1,r;l<=min(j,m);l=r+1){
			int d=j/l;
			r=min(m,j/d);
			// j-d*l 到 j-d*r

			if(d>B){
				for(int x=l;x<=r;x++){
					f[j]=(f[j]+(ull)f[j-d*x]*pw[x-1])%mod;
				}
			}else{
				// for(int x=l;j-d*x>=0;x++){
				// 	f[j]=(f[j]+(ull)f[j-d*x]*pw[x-1])%mod;
				// }
				f[j]=(f[j]+(ull)qz[d][j-d*l]*pw[l-1])%mod;
				// for(int x=r+1;j-d*x>=0;x++){
				// 	f[j]=(f[j]+(ull)(mod-f[j-d*x])*pw[x-1])%mod;
				// }
				if(j>=d*(r+1))
				f[j]=(f[j]+(ull)(mod-qz[d][j-d*(r+1)])*pw[r])%mod;
			}
		}
		f[j]=(ull)f[j]*iv[j]%mod;
		for(int k=1;k<=B;k++){
			qz[k][j]=((j>=k?2ull*qz[k][j-k]:0ull)+f[j])%mod;
		}
	}
	printf("%llu\n",(ull)f[a]*pw[a]%mod);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	pw[0]=1;
	for(int i=1;i<=200000;i++)addmod(pw[i]=pw[i-1]*2);
	iv[200000]=INV(pw[200000]);
	for(int i=199999;i>=0;i--)addmod(iv[i]=iv[i+1]*2);
	// cout<<iv[0]<<endl;
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}