// created time: 2026-09-11 16:40:35
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
const int N = 10000000;
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

ll sa;
int tab[9000005];
void solver(int n, int k, int *a) {
    int m = k * (n - 1);
    long long C = 1LL * n * (k + 1) % mod;
    a[0] = 1;
    for (int i = 1; i <= m; ++i) {
        long long v = 1LL * (i + k - 1) % mod * a[i - 1];
        if (i >= n) v += (i - C) % mod * a[i - n];
        if (i > n)  v -= (i - C + k - 1) % mod * a[i - n - 1];
        a[i] = (v % mod + mod) % mod * iv[i] % mod;
    }
}

int n,a[3005],b[3005],ans;
int calc(int sb,int k,int w){
	if(!w){
		return sb==0 && k>0;
	}
	// <k
	int ret=0;
	for(int i=0;i*k<=sb;i++){
		if(i&1)
			ret=(ret+(ull)(mod-binom(w,i))*binom(sb-i*k+w-1,w-1))%mod;
		else
			ret=(ret+(ull)(    binom(w,i))*binom(sb-i*k+w-1,w-1))%mod;
	}
	return ret;
}
int f[3005],g[3005],h[3005];

void qz(){
	g[0]=f[0];
	for(int i=1;i<=n;i++)addmod(g[i]=f[i]+g[i-1]);
}
void ins(int x){
	qz();
	for(int j=0;j<=n;j++)
		addmod(f[j]=g[j]+mod-(j-x<=0?0:g[j-x-1]));
}
int all;
int dp(int mx,int d,bool sb=0){
	if(mx<0) return 0;
	for(int i=1;i<=n;i++){
		d-=max(0,a[i]-mx);
		if(sb && a[i]==mx) ins(a[i]),all--;
	}
	qz();
	int ret=0;
	for(int j=0;j<=d;j++){
		ret=(ret+(ull)g[d-j]*calc(j,mx+1,all))%mod;
	}
	return ret;
}

unordered_map<int,int>mp;
int golf(int x){
	if(mp.count(x))return mp[x];
	int ret=inv[n];
	for(int i=1;i<=n;i++)ret=(ull)ret*(x+i)%mod;
	return mp[x]=ret;
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)
		sa+=(a[i]=read());
	solver(n,n,tab);
	for(int sb=0;sb<=sa&&sb<=n*(n-1);sb++){
		int cf=golf((sa-sb)/n);
		int cc=tab[sb];
		if(sb-sa+n>0) addmod(cc+=mod-calc(sb,sb-sa+n,n));
		ans=(ans+(ull)cf*cc)%mod;
	}

	all=n,f[0]=1;
	for(int mx=0;mx<n;mx++){
		int d=n-mx-1;
		addmod(ans += mod-dp(mx-1, d));
		addmod(ans += dp(mx, d, 1));
	}
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