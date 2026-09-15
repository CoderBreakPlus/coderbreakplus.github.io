// created time: 2026-09-15 18:21:11
#include<bits/extc++.h>
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
mt19937_64 rnd(1);
const int Lim=63,Siz=160;
int tmp[Siz+5][Lim+5];

ull r[Siz+5][Lim+5][Siz+5],a[Siz+5],s;
void procedure(ll s=0){
	if(!s)s=read();

	int n=-1,m=-1,k=-1;
	for(int N=1;N<=Siz;N++){
		for(int M=lg2(N)+1;M<=Lim;M++)
			for(int K=0;M+K<=64&&N+K<=199;K++)
				if(tmp[N][M]+K*(K-1)/2+N*K==s || tmp[N][M]+K*(K-1)/2+N*K+1==s){
					n=N,m=M,k=K;
					break;
				}
		}
	bool add=(tmp[n][m]+k*(k-1)/2+n*k+1==s);
	printf("%d\n",n+k+add);
	for(int i=1;i<=n;i++) printf("%llu ",r[n][m][i]);
	for(int i=0;i<k;i++) printf("%llu ",1ull<<i+m);

	if(add) printf("%llu\n",r[n][m][1]);
	else puts("");
}
ull seq[100005]; int sz;
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	for(int m=1;m<=Lim;m++){
		for(int n=1;n<=Siz&&n<(1ull<<m);n++){
			ull fk=(1ull<<m)-n;
			for(int j=1;j<=n;j++)a[j]=rnd()%fk;
			sort(a+1,a+n+1);
			for(int j=1;j<=n;j++)a[j]+=j,r[n][m][j]=a[j];

			// __gnu_pbds::gp_hash_table<ull,int>S;
			sz=0;
			for(int j=1;j<=n;j++)
				for(int k=j+1;k<=n;k++)seq[++sz]=a[j]^a[k];
			sort(seq+1,seq+sz+1);
			tmp[n][m]=unique(seq+1,seq+sz+1)-(seq+1);
		}
	}
	ll T=read();
	while(T--) procedure();

	// for(ll i=50;i<=10000;i++)procedure(i);
	return 0;
}