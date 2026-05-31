// created time: 2026-05-30 09:22:12
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

ll n,A,B;
char s[100005],t[100005];

void procedure(){
	n=read(),A=read(),B=read();
	scanf("%s",s+1);
	scanf("%s",t+1);
	ll cA=0,cB=0,cC=0;
	for(ll i=1;i<=n;i++){
		if(s[i]=='0')cA++;
		if(t[i]=='0')cB++;
		if(s[i]=='0'&&t[i]=='0')cC++;
	}
	if(!cA||!cB){
		printf("%lld\n",n);
		return;
	}
	assert(A<=cA);
	assert(B<=cB);
	long double prob=(long double)cC*(cA-A)*(cB-B)/cA/cB;
	printf("%.10Lf\n",n-prob);
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