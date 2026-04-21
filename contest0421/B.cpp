// created time: 2026-04-21 09:08:29
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
int sb(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	return 1337;
}
int ok=sb();

int n=read();
int m=read();
int mod=read();
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

const int M = 60;
const int N = 130;

int h[N][N],g[N][N],f[N][N*N],vec[N*N],C[N][N],fac[N],inv[N],v[N][N];

void upd(int &x, ull b){ x=(x+b)%mod; }

void procedure(){
	C[0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=M;j++){
			g[i][j]=0;
			for(int k=0;k<=min(i,j);k++){
				if(k&1)
					g[i][j]=(g[i][j]+(ll)(mod-C[i][k])*C[j][k]%mod*fac[k]%mod*qpow(i,j-k)%mod*qpow(j,i-k))%mod;
				else
					g[i][j]=(g[i][j]+(ll)C[i][k]*C[j][k]%mod*fac[k]%mod*qpow(i,j-k)%mod*qpow(j,i-k))%mod;
			}
			h[i][j]=g[i][j];
			for(int k=1;k<i;k++)for(int l=1;l<j;l++){
				h[i][j]=(h[i][j]+(ll)(mod-h[k][l])*g[i-k][j-l]%mod*C[i-1][k-1]%mod*C[j][l])%mod;
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=M;j++){
			h[i][j]=(ll)((mod+1)/2)*h[i][j]%mod;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=M;j++)
			v[i][j]=(ull)h[i+1][j]*inv[i]%mod*inv[j]%mod;

	auto code = [&](int x,int y){
		return x*(n+1)+y;
	};

	int Q=code(M,n);
	f[0][code(0,0)]=1;

	for(int x=0;x<=n;x++)
		for(int l=1;l<=M;l++)
			addmod(vec[code(l,-x)]+=v[x][l]);

	for(int i=1;i<=n;i++)
		for(int j=0;j<=Q;j++){
			if(!f[i-1][j])continue;
			upd(f[i][j+1], (ull)f[i-1][j]*(j%(n+1)+1));
			for(int k=0;j+k<=Q;k++)
				upd(f[i][j+k], (ull)f[i-1][j]*vec[k]%mod*i);
		}

	int ans=0;
	for(int i=0;i<=M;i++){
		int val=(ull)f[n][code(i,0)]*fac[i]%mod*qpow(INV(n),i)%mod;
		for(int j=0;j<=M;j++)
			if(i!=j)
			val=(ull)val*(m-j+mod)%mod*INV(i-j+mod)%mod;
		addmod(ans+=val);
	}
	printf("%d\n",(ull)ans*qpow(n,m)%mod);
}
int main(){
	fac[0]=1;
	for(int i=1;i<=N-5;i++)fac[i]=(ll)fac[i-1]*i%mod;
	for(int i=0;i<=N-5;i++)inv[i]=INV(fac[i]);

	for(int i=0;i<=N-5;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)addmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
	}
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}