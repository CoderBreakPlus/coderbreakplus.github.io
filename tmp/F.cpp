// created time: 2026-04-09 13:04:15
// 
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

int n,m;
const int T=11;
struct Mat{
	int a[T][T];
	Mat(){ memset(a,0,sizeof(a)); }
}M,E,Q;
Mat operator* (const Mat &A, const Mat &B){
	Mat C;
	for(int i=0;i<T;i++)
		for(int j=0;j<T;j++)
			for(int k=0;k<T;k++)
				C.a[i][k]=(C.a[i][k]+A.a[i][j]*B.a[j][k])%9;
	return C;
}
void procedure(){
	E=Mat();
	n=read(),m=read()+1;
	while(n) {
		E.a[0][n%10]++,n/=10;
	}
	Q=M;
	while(m){
		if(m&1)E=E*Q;
		Q=Q*Q;
		m>>=1;
	}
	printf("%d\n",E.a[0][10]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	M.a[0][0]=1;
	for(int i=1;i<10;i++){
		int x=i*i;
		while(x) M.a[i][x%10]++,x/=10;
		M.a[i][10] = i%9;
	}
	M.a[10][10]=1;

	// for(int i=0;i<T;i++){
	// 	for(int j=0;j<T;j++)putchar('0'+M.a[i][j]);puts("");
	// }
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}