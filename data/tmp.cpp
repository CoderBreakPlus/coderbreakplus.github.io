// created time: 2026-04-25 11:16:47
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
#define int unsigned
const int mod = 998244353;

char buf[1<<21],*p1=buf,*p2=buf;
inline char gc(){
	return p1==p2&&(p2=(p1=buf)+fread(buf,1,1<<21,stdin),p1==p2)?EOF:*p1++;
}
inline int read(){
	int x=0,ch=gc();
	while(!isdigit(ch))ch=gc();
	while(isdigit(ch))x=x*10+ch-'0',ch=gc();
	return x;
}
inline ull qpow(ull a,ull b){
	ull ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
const int N = 10000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=(ull)fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=(ull)inv[i+1]*(i+1)%mod;
}

int n,q;
int f[10005];
int a[10005],m[10005],iv[10005];
ull ans[10005];
int pw[8200], pwb[8200];
void procedure(){	
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=a[n];i++)iv[i]=(ull)(mod-inv[i])*fac[i-1]%mod;
	for(int i=1;i<=q;i++) m[i]=read();
	f[1]=1;
	for(int i=2;i<=n;i++){
		ull tmp=0;
		for(int j=1;j<i;j++){
			int val=(ull)f[j]*iv[a[i]-a[j]]%mod;
			tmp+=val;
			f[j]=(ull)val*a[j]%mod;
		}
		f[i]=tmp%mod*(mod-a[i])%mod;
	}
	for(int i=1;i<=n;i++){
		ull A = a[i];
		ull T = qpow(A, (1<<13)); 

		pw[0] = f[i]; pwb[0] = 1;
		for (int k = 1; k < 4; k++) {
		    pw[k]  = pw[k-1] * A % mod;
		    pwb[k] = pwb[k-1] * T % mod;
		}

		ull stepA = qpow(A,4); 
		ull stepT = qpow(T,4); 

		for (int j = 4; j < (1<<13); j += 4) {
		    pw[j]   = pw[j-4] * stepA % mod;
		    pw[j+1] = pw[j-3] * stepA % mod;
		    pw[j+2] = pw[j-2] * stepA % mod;
		    pw[j+3] = pw[j-1] * stepA % mod;
		    pwb[j]   = pwb[j-4] * stepT % mod;
		    pwb[j+1] = pwb[j-3] * stepT % mod;
		    pwb[j+2] = pwb[j-2] * stepT % mod;
		    pwb[j+3] = pwb[j-1] * stepT % mod;
		}
		auto getpw = [&](int v){
			return (ull)pwb[v>>13]*pw[v&((1<<13)-1)];
		};
		#pragma GCC unroll 6
		for(int j=1;j<=q;j++){
			ans[j]+=getpw(m[j]);
		}
		if(!(i&15))
			#pragma GCC unroll 6
			for(int j=1;j<=q;j++)ans[j]%=mod;
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]%mod);
}
signed main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}