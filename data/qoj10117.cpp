// created time: 2026-04-09 07:35:02
// https://qoj.ac/contest/1924/problem/10117
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

ll cnt[10],buc[10];
void procedure(){
	ll n=read();
	memset(cnt,0,sizeof(cnt));
	ll N=n;while(N)cnt[N%10]++,N/=10;
	ll val=0;

	for(int i=2;i<=9;i++){
		if(n%i==0){
			ll x=n/i;memset(buc,0,sizeof(buc));
			while(x)buc[x%10]++,x/=10;
			bool f=1;
			for(int j=0;j<10;j++)f&=(buc[j]==cnt[j]);
			val+=f;
		}
	}
	printf("%lld\n",val);
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