// created time: 2026-09-02 12:14:11
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
const int M = 500;
int n,f[200005][M+5];

void upd(int &x,ull y){
	x=(x+y)%mod;
}
void procedure(){
	n=read();
	f[0][0]=1;

	for(int i=0;i<=n;i++){
		for(int j=0;i+2*j<=n && j<=M;j++)if(f[i][j]){
			// as a single point
			upd(f[i+2*j+1][j], (ull)f[i][j]*2*j);
			// as a leaf
			addmod(f[i+2*j+1][j+1]+=f[i][j]);
			if(j)addmod(f[i+2*j][j]+=f[i][j]);
			// as a double point
			upd(f[i+2*j+1][j-1], (ull)f[i][j]*j%mod*(j-1));
		}
	}

	int ans=0;
	for(int i=n;i>=0;i-=2){
		addmod(ans+=f[i][1]);
		if(i==0)ans++;
	}
	printf("%d\n",ans);
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