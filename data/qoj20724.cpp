// created time: 2026-09-28 09:50:03
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

int n,m,k,a[1000005],pt[1000005];
ll sum[1000005];

bool check(ll m){
	for(int i=1;i<=2*n;i++) {
		pt[i]=pt[i-1];
		while(pt[i]<=2*n&&sum[pt[i]]-sum[i-1]<=m)pt[i]++;
	}

	auto nayo = [&](int x){
		int orig_x=x;
		for(int t=1;t<=k;t++){
			x=pt[x];
			if(x>=orig_x+n) return 1;
		}
		return 0;
	};
	if(nayo(1)) return 1;

	int len=pt[1], id=1;
	for(int i=2;i<=n;i++)
		if(pt[i]-i+1<len) len=pt[i]-i+1,id=i; 

	for(int i=id;i<=pt[id];i++)
		if(nayo((i-1)%n+1)) return 1;
	return 0;
}
void procedure(){
	n=read(),m=read(),k=read();

	for(int i=1;i<=n;i++)a[i]=a[i+n]=read();
	for(int i=1;i<=2*n;i++)sum[i]=sum[i-1]+a[i];

	ll L=0,R=sum[n],Ans=sum[n];
	while(L<=R){
		ll M=(L+R)>>1;
		if(check(M)) Ans=M,R=M-1;
		else L=M+1;
	}
	printf("%lld\n",sum[n]+(m-1)*Ans);
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