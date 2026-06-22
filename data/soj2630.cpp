// created time: 2026-06-22 10:12:02
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
const int N = 500000;
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

int n,m,k,ty;

int dp[205][205],C[405][405];
int iv[40005];

void procedure(){
	n=read(),m=read(),k=read(),ty=read();
	int ivk = INV(k);

	for(int i=1;i<=40000;i++)iv[i]=INV(i);
	for(int i=0;i<=400;i++)
		for(int j=0;j<=i;j++)C[i][j]=binom(i,j);
	if(ty==1){
		int x=read();
		int ans=0;
		for(int i=0;i<=n;i++){
			for(int j=0;j<=m;j++){
				if(i+j<x) continue;
				int tot = i*m+j*n-i*j, res = n*m-tot, pro;

				int exp = (tot + (ull)res * (mod+1-INV(tot+1))) % mod;
				if(!i || !j){
					pro = (ull)qpow(ivk, i*(m-1)+j*(n-1));
				}else{
					pro = (ull)qpow(ivk, tot-1);
				}
				pro = (ull)pro * binom(n,i) % mod * binom(m,j) % mod;

				if((i+j-x)&1){
					ans = (ans + (ull)(mod - binom(i+j-1,x-1)) * exp % mod * pro) % mod;	
				}else{
					ans = (ans + (ull)binom(i+j-1,x-1) * exp % mod * pro) % mod;
				}
			}
		}
		printf("%d\n", ans);
	}else{
		for(int i=0;i<=n;i++)
			for(int j=0;j<=m;j++){
				if(i && j)
					dp[i][j] = (ull)binom(n,i) * binom(m,j) % mod * qpow(ivk, i*m+j*n-i*j-1) % mod;
				else
					dp[i][j] = (ull)binom(n,i) * binom(m,j) % mod * qpow(ivk, i*(m-1)+j*(n-1)) % mod;
			}

		for(int i=n;i>=0;i--)
			for(int j=m;j>=0;j--){
				for(int k=i+1;k<=n;k++){
					dp[i][j]=(dp[i][j]+(ull)binom(k,i)*(mod-dp[k][j]))%mod;
				}
			}
		for(int i=n;i>=0;i--)
			for(int j=m;j>=0;j--){
				for(int l=j+1;l<=m;l++){
					dp[i][j]=(dp[i][j]+(ull)binom(l,j)%mod*(mod-dp[i][l]))%mod;
				}
			}

		int ans = 0;
		for(int p=0;p<=n;p++){
			for(int q=0;q<=m;q++){
				if(!p&&!q)continue;
				int x = (p+q+1)/2;

				int glo = 0;
				for(int i=0;i<=p;i++){
					for(int j=0;j<=q;j++){
						if(i+j<x) continue;
						int tot = i*m+j*n-i*j, res = n*m-tot;
						int exp = (tot + (ull)res * (mod+1-iv[tot+1])) % mod;
						exp = (ull)exp * C[p][i] % mod * C[q][j] % mod;

						if((i+j-x)&1){
							glo = (glo + (ull)(mod - C[i+j-1][x-1]) * exp) % mod;	
						}else{
							glo = (glo + (ull)C[i+j-1][x-1] * exp) % mod;
						}
					}
				}
				ans = (ans + (ull)glo * dp[p][q]) % mod;
			}
		}
		printf("%d\n", ans);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}