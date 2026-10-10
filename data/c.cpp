// created time: 2026-10-05 08:23:36
#include"cards.h"
#include<bits/stdc++.h>
// #ifdef LOCAL
// #include"_cards.cpp"
// #endif
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
const int N = 10000000;
int fac[N+5],inv[N+5];
int lst[2*N+5];
int *pw2=lst+N;

void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=(ull)fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=(ull)inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return (ull)fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return (ull)fac[x]*inv[x-y]%mod;
}
void init(int c,int t){
	pw2[0]=1;
	for(int i=-1;i>=-N;i--)
		pw2[i]=(pw2[i+1]+(pw2[i+1]&1)*mod)>>1;
	for(int i=1;i<=N;i++)
		addmod(pw2[i]=pw2[i-1]*2);
}

int cards(int n,int m,int a,int b){
	if(!n)return 0;
	int d=(ull)(a+(ull)2*mod-b)%mod*pw2[-1]%mod;

	fac[0]=1;
	if(n>=1)inv[1]=1;
	for(int i=2;i<=n;i++)
		inv[i]=mod-(ull)(mod/i)*inv[mod%i]%mod;
	for(int i=1;i<=n;i++)
		fac[i]=(ull)fac[i-1]*(2*n-i+1)%mod*inv[i]%mod;

	inv[0]=1;
	for(int i=1;i<n;i++)
		inv[i]=(ull)inv[i-1]*(pw2[i]+mod-1)%mod;

	int cur=INV(inv[n-1]);
	for(int i=n-1;i>=1;i--){
		int pre=inv[i-1];
		inv[i]=(ull)cur*pre%mod;
		cur=(ull)cur*(pw2[i]+mod-1)%mod;
	}

	int bm=qpow(2,m);
	int rm=qpow(INV(bm),n-1);

	int q[2]={0,0};
	int ans=0;

	for(int j=0;j<=2*n-2;j++){
		int C=fac[min(j,2*n-j)];

		int p=(ull)C*(mod+1LL-pw2[j-n])%mod;

		int &las=q[j&1];
		int now=(p+2ull*las)%mod;
		las=now;

		int e=j+1-n;
		int g;

		if(e==0){
			g=m%mod;
		}else if(e>0){
			g=(ull)(rm+mod-1)%mod*inv[e]%mod;
		}else{
			int k=-e;
			g=(ull)(mod+1LL-rm)%mod*pw2[k]%mod*inv[k]%mod;
		}

		ans=(ans+2ull*now*g)%mod;
		rm=(ull)rm*bm%mod;
	}

	return (ull)ans*d%mod*pw2[-2*n+1]%mod;
}