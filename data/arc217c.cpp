#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };
const int N = 100;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

int n,c,a[105];
int f[105][105],g[105][105];

int qz[105][105],ans[105];

void procedure(){
	n=read(),c=read();
	for(int i=1;i<=n;i++)a[i]=read(); a[n+1]=c+1;
	sort(a+1,a+n+1);
	memset(f,0,sizeof(f));
	memset(g,0,sizeof(g));
	memset(qz,0,sizeof(qz));
	memset(ans,0,sizeof(ans));
	for(int i=1;i<=n+1;i++) f[i][i-1]=1;

	for(int l=n;l>=1;l--){
		for(int r=l;r<=n;r++){
			for(int k=l;k<=r;k++){
				f[l][r]=(f[l][r]+1ull*f[l][k-1]*f[k+1][r]%mod*binom(r-l,k-l)%mod*(a[r+1]-a[k]))%mod;
			}
		}
	}
	for(int i=0;i<=n;i++) qz[0][i]=qpow(a[1]-1,i);
	for(int i=1;i<=n;i++){
		for(int j=1;j<=n;j++){
			for(int k=1;k<=i;k++)
				if(j>i-k)
				qz[i][j]=(qz[i][j]+1ull*qz[k-1][j-1-(i-k)]*f[k+1][i]%mod*(a[i+1]-a[k])%mod*binom(j-1,i-k))%mod;
			qz[i][j]=(qz[i][j]+1ull*qz[i][j-1]*(a[i+1]-1))%mod;
		}
	}
	int iv=qpow(INV(c),n);
	g[n][0]=1;
	for(int i=n;i>=1;i--){
		for(int k=i;k>=2;k--){
			int t=k-2,l=i-k+1;
			for(int x=0;x+l<=n;x++)
				g[t][x+l]=(g[t][x+l]+1ull*g[i][x]*f[k][i]%mod*binom(x+l,x))%mod;
		}
		for(int j=0;j<=n;j++)addmod(g[i-1][j]+=g[i][j]);
	}
	for(int i=0;i<=n;i++)
		for(int k=0;k<=n;k++){
			ans[i+k]=(ans[i+k]+1ull*qz[i][n-k]*g[i][k]%mod*binom(n,k))%mod;
		}

	for(int i=0;i<=n;i++)
		// printf("%d ",ans[i]);
		printf("%d ",(int)(1ull*ans[i]*iv%mod));
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	int T=read();
	math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}