// created time: 2026-11-06 15:23:45
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

int n,a[200005],hz[200005];
int b[200005],c[200005],ans;

void dfs(int i){
	if(i==n+1){
		int tmp=0;

		int pt=n;while(pt>=1&&!b[pt])pt--;
		for(int i=1;i<=pt;i++)tmp+=(b[i]>b[i+1]);

		pt=1;while(pt<=n&&!c[pt])pt++;
		for(int i=pt;i<=n;i++)tmp+=(c[i]>c[i-1]);

		chkmin(ans,tmp);
		// if(tmp==2){
		// 	for(int i=1;i<=n;i++) cout<<b[i]<<" "; cout<<endl;
		// 	for(int i=1;i<=n;i++) cout<<c[i]<<" "; cout<<endl;
		// }

		return;
	}
	for(b[i]=0,c[i]=a[i];b[i]<=a[i];b[i]++,c[i]--)
		dfs(i+1);
}
void procedure(){
	n=ans=read();
	for(int i=1;i<=n;i++)a[i]=read();
	dfs(1);
	printf("%d\n",ans);
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