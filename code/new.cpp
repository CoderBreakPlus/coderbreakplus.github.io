// created time: 2026-04-23 14:13:20
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
const int P=12252240;
int n,a[10000005],x,y,k,M,C[20][20],pw[20];

int f[P][2],g[P][2];
void upd(int &a,ull b){ a=(a+b)%mod; }
void procedure(){
	n=read(),a[0]=read(),x=read(),y=read(),k=read(),M=read();
	for(int i=1;i<n;i++)a[i]=((ull)a[i-1]*x+y)%M;
	pw[0]=1;
	for(int i=1;i<=k;i++)pw[i]=(ull)pw[i-1]*(n-1)%mod;

	int out=0; ull iv=INV(n-1);
	for(int i=0;i<n;i++){
		int v=a[i]/P*P;
		for(int s=0;s<=k;s++)
			out=(out+(ull)pw[k-s]*v%mod*s%mod*C[k][s])%mod;
		a[i]%=P;
		f[a[i]][0]++;
	}
	for(int i=1;i<=k;i++){
		memcpy(g,f,sizeof(g));
		for(int j=0;j<P;j++){
			int k=j-j%i;
			ull v0=f[j][0]*iv%mod, v1=f[j][1]*iv;

			addmod(g[k][0]+=v0);
			upd(g[k][1], v1+v0*j);
		}
		memcpy(f,g,sizeof(f));
	}
	int tmp=0;
	for(int i=0;i<P;i++)addmod(tmp+=g[i][1]);
	printf("%d\n",(out+(ull)tmp*pw[k])%mod);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	for(int i=0;i<=17;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)addmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
	}
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}