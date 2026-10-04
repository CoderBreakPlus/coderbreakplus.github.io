// created time: 2026-10-04 20:18:01
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
const int B = 500;

int n,q,x[200005],mx[20][200005],mn[20][200005],bl[200005];
int lf[200005],rh[200005];

int getmx(int i,int j){ return x[i]>x[j]?i:j; }
int getmn(int i,int j){ return x[i]<x[j]?i:j; }

struct {
	
};
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++){
		x[i]=read(),mx[0][i]=mn[0][i]=i;
		bl[i]=(i-1)/B+1, rh[bl[i]]=i;
	}
	for(int i=n;i>=1;i--) lf[bl[i]]=i;

	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++){
			mx[i][j]=getmx(mx[i-1][j],mx[i-1][j+(1<<i-1)]);
			mn[i][j]=getmn(mn[i-1][j],mn[i-1][j+(1<<i-1)]);
		}

	for(int x=1;x<=bl[n];x++){

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