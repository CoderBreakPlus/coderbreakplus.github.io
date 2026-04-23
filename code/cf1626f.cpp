// created time: 2026-04-23 14:13:20
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,a[10000005],x,y,k,M;

void procedure(){
	n=read(),a[0]=read(),x=read(),y=read(),k=read(),M=read();
	for(int i=1;i<n;i++)a[i]=((ull)a[i-1]*x+y)%M;

	int out=0;
	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<k);s++){
			int v=a[i],ans=0;
			for(int t=0;t<k;t++)if((s>>t)&1){
				addmod(ans+=v);
				v-=(v%(t+1));
			}
			out=(out+(ull)ans*qpow(n-1,k-__builtin_popcount(s)))%mod;
		}
	}
	printf("%d\n",out);
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