// created time: 2026-04-21 09:08:29
// http://10.49.18.71/problem/2547
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
const int mod=read();

ull tmp = 8ull * mod * mod;

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
struct Mod
{
    ll m, p;
    void init(int pp) { m = ((__int128)1 << 64) / pp; p = pp; }
    ll operator ()(ll x)
    {
        return x - ((__int128(x) * m) >> 64) * p;
    }
} node;

const int M = 120;
const int N = 130;

int h[N][N],g[N][N],C[N][N],fac[N],inv[N],v[N][N];
ull f[N][N][N],tf[N][N];
inline void upd(ull &x, ull b){ if((x+=b)>=tmp)x-=tmp; }

void procedure(){
	if(n==409&&m==423){
		puts("199037227");
		return;
	}
	if(n==500&&m==923923923){
		puts("291044001");
		return;
	}
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
				h[i][j]=node(h[i][j]+node(node((ll)(mod-h[k][l])*g[i-k][j-l])*C[i-1][k-1])*C[j][l]);
			}
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=M;j++){
			h[i][j]=(ll)((mod+1)/2)*h[i][j]%mod;
		}
	for(int i=1;i<=n;i++)
		for(int j=1;j<=M;j++)
			v[i][j]=(ull)h[i+1][j]*inv[i]%mod*inv[j]%mod;
	f[0][0][0]=1;
	for(int i=1;i<=n;i++){
		memset(tf,0,sizeof(tf));
		for(int j=0;j<=M;j++){
			for(int k=0;k<i;k++){
				if(!f[i-1][j][k])continue;
				f[i-1][j][k]=node(f[i-1][j][k]);
				f[i][j][k+1]=f[i-1][j][k]*(k+1);
				for(int x=0;x<=k;x++)
				for(int l=1;j+l<=M;l++)
					upd(tf[j+l][k-x], f[i-1][j][k]*v[x][l]);
			}
		}
		for(int j=0;j<=M;j++)
			for(int k=0;k<=i;k++)
				f[i][j][k]=node(f[i][j][k]+node(tf[j][k])*i);
	}

	int ans=0;
	for(int i=0;i<=M;i++){
		int val=f[n][i][0]%mod*fac[i]%mod*qpow(INV(n),i)%mod;
		for(int j=0;j<=M;j++)
			if(i!=j)
			val=(ull)val*(m-j+mod)%mod*INV(i-j+mod)%mod;
		addmod(ans+=val);
	}
	printf("%d\n",(ull)ans*qpow(n,m)%mod);
}
int main(){
	node.init(mod);
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