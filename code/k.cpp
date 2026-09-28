// created time: 2026-09-28 10:26:13
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
const int M = 52, S = 2 * M;
ll n,m,a[55],s[55];

struct Mat{
	ll a[S+1][S+1];
	ll* operator[](int x){ return a[x]; }
	const ll* operator[](int x)const{ return a[x]; }
	Mat(){ memset(a,0x3f,sizeof(a)); }
}M0,M1,M2;
Mat operator* (const Mat& A,const Mat &B){
	Mat C;
	for(int i=0;i<=S;i++)
		for(int j=0;j<=S;j++)
			for(int k=0;k<=S;k++)
				chkmin(C[i][j],A[i][k]+B[k][j]);
	return C;
}
void procedure(){
	n=read(),m=read();
	a[0]=1;
	for(int i=1;i<=n;i++) a[i]=read()+1,s[i]=i;
	sort(a,a+n+1);

	M0[0][M]=0;
	for(int i=0;i<=S;i++){
		for(int p=0;p<=n;p++)
			for(int q=0;q<=n;q++){
				int w=i+p+q-n;
				if(0<=w&&w<=S) chkmin(M1[i][w],a[p]+a[q]);
			}
		for(int p=0;p<=n;p++){
			int w=i+p-n/2;
			if(0<=w&&w<=S) chkmin(M2[i][w],a[p]);
		}
	}

	int res=m/2;
	while(res){
		if(res&1)M0=M0*M1;
		M1=M1*M1; res>>=1;
	}
	if(m&1)M0=M0*M2;
	printf("%lld\n",M0.a[0][M+1]);
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