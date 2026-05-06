// created time: 2026-05-05 14:33:47
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

const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	// if(x==-1&&y==-1)return 1;
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

int f[405][405],g[405][405],buc[405];
int n,l,r;
void procedure(){
	n=read(),l=read(),r=read();
	for(int i=1;i<=n;i++)buc[read()]++;
	int mx=n;while(!buc[mx])mx--;
	f[1][1]=1; int cur=buc[mx];
	for(int i=mx-1;i>=1;i--){
		if(!buc[i])continue;
		// cout<<"add in "<<buc[i]<<endl;
		memset(g,0,sizeof(g));
		for(int x=1;x<=l;x++)for(int y=1;y<=r;y++){
			if(!f[x][y])continue;
			g[x][y]=(g[x][y]+(ull)f[x][y]*binom(cur+buc[i]-2,cur-2))%mod;
			g[x+1][y]=(g[x+1][y]+(ull)f[x][y]*binom(cur+buc[i]-2,cur-1))%mod;
			g[x][y+1]=(g[x][y+1]+(ull)f[x][y]*binom(cur+buc[i]-2,cur-1))%mod;
			g[x+1][y+1]=(g[x+1][y+1]+(ull)f[x][y]*binom(cur+buc[i]-2,cur))%mod;
		}
		memcpy(f,g,sizeof(f));
		cur+=buc[i];
	}
	printf("%d\n",f[l][r]);
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