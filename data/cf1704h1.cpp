// created time: 2026-09-27 07:32:46
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int n,mod;
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
int fac[N+5],inv[N+5],iv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
	for(int i=1;i<=N;i++) iv[i]=(ull)inv[i]*fac[i-1]%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

int f[5005][3],g[5005],h[5005][2],dp[5005],ans[5005];
int dp1[5005][2][2],dp2[5005];

struct Mod{
	ull m,p;
	void init(int pp){ m=((__int128)1<<64)/pp; p=pp; }
	ull operator()(ull x){ return x-((__int128(x)*m)>>64)*p; }
}node;
void upd(int &a,ull b){ a=node(a+b); }
void procedure(){
	n=read(),mod=read();
	node.init(mod);
	math_init();

	g[0]=h[0][0]=1;

	for(int i=1;i<=n;i++){
		f[i][1]=node((ull)h[i-1][1]*i),f[i][0]=node((ull)g[i-1]*i);
		f[i][2]=node((ull)h[i-1][0]*i);
		for(int j=1;j<=i;j++){
			int c=binom(i-1,j-1);
			upd(g[i],node((ull)g[i-j]*f[j][1])*c);
			upd(h[i][0],node((ull)h[i-j][0]*(f[j][0]+f[j][1]))*c);
			upd(h[i][1],node((ull)(h[i-j][0]+h[i-j][1])*(f[j][0]+f[j][1]))*c);
		}
	}

	for(int i=1;i<=n;i++){
		f[i][0]=node((ull)f[i][0]*inv[i]);
		f[i][1]=node((ull)f[i][1]*inv[i]);
		f[i][2]=node((ull)f[i][2]*inv[i]);
	}
	for(int i=1;i<=n;i++){
		dp2[i]=node((ull)f[i][2]*i);
		dp1[i][0][0]=node((ull)f[i][0]*i);
		dp1[i][1][1]=node((ull)(f[i][1]+f[i][2])*i);
	}

	for(int i=1;i<=n;i++){
		for(int j=1;j<=i;j++){
			int val=node((ull)dp2[i-j]*f[j][2]);
			addmod(dp2[i] += val);
			addmod(dp[i] += mod-val);
			for(int p:{0,1})for(int q:{0,1})for(int r:{0,1}){
				int val=node((ull)dp1[i-j][p][q]*(f[j][r]+r*f[j][2]));
				if(!val)continue;
				if(r==0){
					if(q){
						addmod(dp1[i][p][0]+=val);
						if(p){
							addmod(dp[i]+=val);
						}
					}
				}else{
					addmod(dp1[i][p][1]+=val);
					addmod(dp[i]+=val);
				}
			}
		}
	}

	ans[0]=1;
	for(int i=1;i<=n;i++){
		int sum=0;
		for(int j=1;j<=i;j++)
			upd(sum, (ull)dp[j]*ans[i-j]);
		ans[i]=node((ull)sum*iv[i]); 
	}
	printf("%llu\n",node((ull)ans[n]*fac[n]));
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	while(T--) procedure();
	return 0;
}