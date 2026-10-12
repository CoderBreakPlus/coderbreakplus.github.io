// created time: 2026-10-12 15:12:32
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

int n,q,a[200005],stk[200005],f[20][200005],tp;
int get(int x,int y){ return a[x]<a[y]?x:y; }
int qry(int l,int r){
	int p=lg2(r-l+1);
	return get(f[p][l],f[p][r-(1<<p)+1]);
}
ll lf[200005],rh[200005];
ll slf[200005],srh[200005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read(),f[0][i]=i;
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	a[0]=a[n+1]=-2e9;
	stk[0]=n+1,tp=0;
	for(int i=n;i>=1;i--){
		lf[i]=lf[i+1]+a[i];
		while(a[i]<a[stk[tp]]){
			lf[i]+=(ll)(a[i]-a[stk[tp]])*(stk[tp-1]-stk[tp]);
			tp--;
		}
		stk[++tp]=i;
	}
	stk[0]=0,tp=0;
	for(int i=1;i<=n;i++){
		rh[i]=rh[i-1]+a[i];
		while(a[i]<a[stk[tp]]){
			rh[i]+=(ll)(a[i]-a[stk[tp]])*(stk[tp]-stk[tp-1]);
			tp--;
		}
		stk[++tp]=i;
	}
	for(int i=1;i<=n;i++) slf[i]=slf[i-1]+lf[i],srh[i]=srh[i-1]+rh[i];
	while(q--){
		int l=read(),r=read();
		int pos=qry(l,r);

		ll ret=(ll)(pos-l+1)*(r-pos+1)*a[pos];
		ret+=slf[pos-1]-slf[l-1]-lf[pos]*(pos-l);
		ret+=srh[r]-srh[pos]-rh[pos]*(r-pos);
		printf("%lld\n",ret);
	}
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