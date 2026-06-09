// created time: 2026-06-09 08:20:40
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

int n,m,k,p,c;
int dis(int x){
	if(x==0)return 0;
	if(c==1)return 2*n-2*x;
	else if(c==2)return 2*x;
	else return min(2*x,2*n-2*x);
}
int a[1000005],b[1000005],buc[1000005];
ll dp[1000005];

int que[1000005],hd,tl;
ll val(int x){ return dp[x]+dis(x); }
void procedure(){
	n=read(),m=read(),k=read(),p=read();
	c=read();

	for(int i=1;i<=n;i++){
		int x=read();
		a[i]=a[i-1],b[i]=b[i-1];
		if(buc[x]++ == 0) a[i]++;
		if(buc[x]==p) b[i]++,buc[x]=0;
	}
	que[hd=tl=1]=0;
	dp[0]=n+1;
	for(int i=1;i<=n;i++){
		while(hd<=tl&&a[i]-b[que[hd]]>m)hd++;
		dp[i]=val(que[hd]);
		while(hd<=tl&&val(que[tl])>val(i))tl--;
		que[++tl]=i;
	}
	printf("%lld\n",dp[n]);
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