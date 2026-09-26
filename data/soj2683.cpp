// created time: 2026-09-26 08:31:04
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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
const int N = 1000000;
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

int h,w,n,m,a[25];
int f[2][25][1<<18],pre[1<<18];

void upd(int &a,ull b){ a=(a+b)%mod; }

int C1[1000005],C2[1000005][18];
void procedure(){
	h=read(),w=read(),m=read(); n=h*w;
	for(int i=1;i<=m;i++) a[i]=read();
	sort(a+1,a+m+1);

	a[m+1]=n+1;
	int r=0,c=0,rc;
	while(~h&1)h>>=1,r++;
	while(~w&1)w>>=1,c++;

	int nd=1<<(rc=r+c), sz=h*w;
	if(sz>m+1){ puts("0"); return; }

	for(int i=0;i<=n;i++){
		C1[i]=binom(i,nd-1);
		for(int l=0;l<rc;l++)C2[i][l]=binom(i,(1<<l)-1);
	}

	f[(m&1)^1][0][0]=1;

	for(int i=m,o=m&1;i>=1;i--,o^=1){
		memset(f[o],0,sizeof(f[o]));
		for(int j=0;j<=m-i;j++){
			// put a link
			for(int k=0,F;k<(1<<rc);k++)if(F=f[o^1][j][k]){
				int res=n-a[i]-j*nd-k;
				// cout<<"res="<<res<<endl;
				// leave it
				addmod(f[o][j][k] += F);
				// add
				upd(f[o][j+1][k], (ull)F*C1[res]);

				// fuck

				int x=(~k)&((1<<rc)-1);
				while(x){
					int l=__builtin_ctz(x);
					upd(f[o][j][k^(1<<l)], (ull)(mod-F)*C2[res][l]);
					x^=(1<<l);
				}
			}
		}
	}
	pre[0]=1;
	for(int i=1;i<(1<<rc);i++){
		int x=(i&-i);
		pre[i]=(ull)pre[i^x]*binom(i,x)%mod;
	}

	int ans=0;
	for(int i=0;i<(1<<rc);i++){
		upd(ans, (ull)f[1][sz-1][i]*pre[(1<<rc)-1-i]);
	}
	ans=(ull)ans*qpow(fac[nd],sz-1)%mod*fac[sz]%mod*binom(r+c,r)%mod*qpow(2,rc)%mod;
	for(int i=0;i<rc;i++)ans=(ull)ans*fac[1<<i]%mod;

	printf("%d\n",ans);
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