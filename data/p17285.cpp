// created time: 2026-11-22 14:51:08
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
const int N=3e7;
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

int n,m,k,f[N+5],h[N+5];

int pr[N/5+5],cnt;
bitset<N+5>vis;
void procedure(){
	n=read(),m=read(),k=read();
	if(k>n||k>m){
		puts("0");
		return;
	}
	else if(k==n){
		for(int i=0;i<=n;i++)
			if(i&1)f[i]=mod-binom(n,i);
			else f[i]=binom(n,i);
	}else if(k==0){
		for(int i=0;i<=n;i++)
			f[i]=binom(n,i);
	}else{
		f[0]=1;
		for(int i=0;i<n;i++){
			int now=(n-2ll*k+mod)*f[i]%mod;
			if(i>0)now=(now+(i-1ll-n+mod)*f[i-1])%mod;
			f[i+1]=(ull)now*inv[i+1]%mod*fac[i]%mod;
		}
	}
	h[1]=1;

	for(int i=2;i<=n;i++){
		if(!vis[i]){
			h[i]=qpow(i,m);
			pr[++cnt]=i;
		}
		for(int j=1;j<=cnt&&i*pr[j]<=n;j++){
			h[i*pr[j]]=(ull)h[i]*h[pr[j]]%mod;
			vis[i*pr[j]]=1;
			if(i%pr[j]==0)break;
		}
	}
	ull ans=0;
	for(int i=0;i<=n;i++){
		int v;
		if(n-2*i==0)v=(m==0);
		else if(n-2*i>0)v=h[n-2*i];
		else{
			if(m&1)v=mod-h[2*i-n];
			else v=h[2*i-n];
		}
		ans=(ans+(ull)f[i]*v)%mod;
	}
	ans=ans%mod*binom(n,k)%mod*qpow((mod+1)/2,n)%mod;
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