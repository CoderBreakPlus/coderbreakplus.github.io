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
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,m,c,sum,b[55],qz[55];

inline void upd(int &a,ull b){ a=(a+b)%mod; }
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

namespace brute{
	int f[2][1<<20][55];

	int main(){
		f[0][0][0]=1;
		for(int i=1,op=1;i<=n;i++,op^=1){
			memset(f[op],0,sizeof(f[op]));
			int up=(1<<min(m,n-i+1)),down=(1<<max(0,m-i+1));

			if(down>1){
				for(int j=0;j<up;j+=down){
					for(int k=0;k<=n;k++){
						int val=f[op^1][j][k];
						if(!val) continue;
						upd(f[op][j>>1][k], 1ull*val*k);
						upd(f[op][j>>1][k+1], 1ull*val*qz[i]%mod*(c-k));
					}
				}
			}else{
				for(int j=0;j<up;j+=2){
					for(int k=0;k<=n;k++){
						int val=f[op^1][j][k];
						if(!val) continue;
						upd(f[op][j>>1][k], 1ull*val*k);
						upd(f[op][j>>1][k+1], 1ull*val*qz[i]%mod*(c-k));
					}
				}
				for(int j=1;j<up;j+=2){
					for(int k=0;k<=n;k++){
						int val=f[op^1][j][k];
						addmod(f[op][j>>1][k]+=val);
					}
				}
			}
			if(i+m<=n){
				if(up>1) up>>=1;
				if(down>1) down>>=1;
				for(int j=0;j<up;j+=down){
					for(int k=0;k<=n;k++){
						int val=f[op][j][k]; if(!val) continue;
						upd(f[op][j|(1<<m-1)][k],1ull*(mod-val)*k);
						upd(f[op][j|(1<<m-1)][k+1],1ull*(mod-val)*qz[i]%mod*(c-k));
					}
				}
			}
		}
		int ivs=INV(sum);
		int ans=0;
		for(int k=0;k<=n&&k<=c;k++) ans=(ans+1ull*f[n&1][0][k]*qpow(ivs,k))%mod;
		return ans;
	}
}
namespace sol{
	int f[55][55][55],c0[55][55],c1[55][55],ans[55];
	int main(){
		for(int i=1;i<=m;i++)
		for(int j=0;j<=n;j++){
			if(i<=n-m+1)
				c0[i][j]=(ull)inv[j]*qpow(b[i],j)%mod;
			else
				c0[i][j]=(j==0);
		}
		for(int i=1;i<=m;i++)
			for(int j=0;j<=n;j++){
				if(i+m<=n-m+1)
					c1[i][j]=(ull)inv[j]*qpow(b[i+m],j)%mod;
				else
					c1[i][j]=(j==0);
			}
		for(int C=0;C<=n;C++){
			for(int p=0,q=C;p<=C;p++,q--){
				if(2*m>n && q) continue;
				memset(f,0,sizeof(f));

				for(int i=0;i<=p;i++)
					for(int j=0;j<=min(q,C-i);j++)if(C-i-j==0||m+1<=n)
						f[1][i][j]=(ull)i*(m+1<=n?C-i-j:1)*(2*m+1<=n?j:1)*c0[1][i]%mod*c1[1][q-j]%mod;

				for(int x=2;x<m;x++){
					if(2*m+x<=n){
						for(int i=p;i>=0;i--)
						for(int j=0;j<=q;j++)
						for(int k=i+1;k<=p;k++)
							upd(f[x-1][k][j],(ull)f[x-1][i][j]*c0[x][k-i]);

						for(int i=p;i>=0;i--)
						for(int j=0;j<=q;j++)
						for(int l=min(q,j);l>=0;l--)
							upd(f[x][i][l],(ull)f[x-1][i][j]*c1[x][j-l]);

						for(int k=0;k<=p;k++)
							for(int l=0;l<=q;l++)
								f[x][k][l]=(ull)f[x][k][l]*k*l*(C-k-l)%mod;
						continue;
					}else{
						for(int i=0;i<=p;i++)
						for(int j=0;j<=min(q,C-i);j++)

						for(int k=i,l=0;k<=C;k++)
							if(C-k-l==0||m+x<=n)
							upd(f[x][k][l],(ull)f[x-1][i][j]
							*k*(m+x<=n?C-k-l:1)%mod*(2*m+x<=n?l:1)%mod*c0[x][k-i]%mod*c1[x][j-l]);
					}
				}

				for(int i=0;i<=p;i++)
					for(int j=0;j<=q;j++){
						upd(ans[C],(ull)f[m-1][i][j]*p*(2*m<=n?q:1)%mod*c0[m][p-i]%mod*c1[m][j]);
					}
			}
			ans[C]=(ull)ans[C]*fac[C]%mod;
			ans[C]=(ull)ans[C]*qpow(INV(sum),C)%mod;
		}

		int out=0;
		for(int i=0;i<=n;i++){
			int cf=ans[i];
			for(int j=0;j<=n;j++)if(j!=i) cf=(ull)cf*(c-j+mod)%mod;
			for(int j=0;j<=n;j++)if(j!=i) cf=(ull)cf*INV(i-j+mod)%mod;
			addmod(out+=cf);
		}
		return out;
	}
}
void procedure(){
	n=read(),m=read(),c=read();

	for(int i=1;i<=n-m+1;i++) b[i]=read();
	for(int i=1;i<=n;i++) addmod(qz[i]=qz[i-1]+b[i]);
	sum=qz[n];
	if(3*m-1>=n) printf("%d\n",sol::main());
	else printf("%d\n",brute::main());
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}