// created time: 2026-06-23 08:05:36
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int n,k,mod;
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
namespace FastMod {
typedef unsigned long long ull;
typedef __uint128_t uLL;
ull b,m;
inline void init(ull B) { b=B,m=ull((uLL(1)<<64)/B); }
inline ull mod(ull a) {
	ull q=((uLL(m)*a)>>64),r=a-q*b;
	return r>=b?r-b:r;
}
};
ull o(ull x){return FastMod::mod(x);}

const int N = 500;
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
ull D;

inline int P(int x,int y){
	if(y>x)return 0;
	int ret=1;
	for(int i=x;i>x-y;i--)ret=(ull)ret*i%mod;
	return ret;
}
int z[105],t,dp[105][105],S[105][105],ans;
int pre[105],pre2[105];


void calc(int cf){
	cf=(ull)cf*pre[t]%mod*fac[k]%mod;
	int cnt=0;
	for(int i=1;i<=t;i++){
		if(z[i]==z[i-1])cnt++; else cnt=1;
		cf=o((ull)cf*iv[cnt]);
	}
	int q=0;
	for(int i=0;i<=min(n,k);i++){
		q=o(q+o((ull)pre[i]*dp[t][i])*pre2[i]);
	}

	ans=o(ans+o(o((ull)cf*q)*q)*q);
}
// int cnt;
void dfs(int x,int w,int cf){
	if(t>n)return;
	if(!x){
		// cnt++;
		// if(cnt%10000==0)cerr<<cnt<<endl;
		calc(cf);
		return;
	}

	for(int i=min(x,w);i>=1;i--){
		z[++t]=i;
		for(int j=0;j<=k;j++){
			ull sum=0;
			for(int w=0;w<=min(j,z[t]);w++){
				sum+=(ull)dp[t-1][j-w]*S[z[t]][w];
				if(sum>=D)sum-=D;
			}
			dp[t][j]=o(sum);
		}
		dfs(x-i,i,o((ull)cf*inv[i]));
		--t;
	}
}
void procedure(){
	n=read(),k=read(),mod=read();
	FastMod::init(mod);
	D=(ull)15*mod*mod;
	math_init();

	for(int i=0;i<=min(n,k);i++)pre[i]=P(n,i),pre2[i]=qpow(n,n-i);

	S[0][0]=1;
	for(int i=1;i<=k;i++)
		for(int j=1;j<=i;j++)
			S[i][j]=(S[i-1][j-1]+(ull)j*S[i-1][j])%mod;

	dp[0][0]=1;
	dfs(k,k,1);
	printf("%d\n",(ull)ans*qpow(INV(n),3*n)%mod);
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