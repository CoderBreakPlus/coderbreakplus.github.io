// created time: 2026-10-26 15:49:12
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
const int B = 55;
int n,q,a[3005],l[3005],r[3005],buc[3005],ord[3005];
int f[3005],ans[3005];

void addmod(int &a,ull b){ a=(a+b)%mod; }
void ins(int x){
	for(int j=n;j>=1;j--)addmod(f[j],(ull)f[j-1]*x);
}
void del(int x){
	for(int j=1;j<=n;j++)addmod(f[j],(ull)(mod-f[j-1])*x);
}
void procedure(){
	n=read(),q=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int o=0;o<q;o++)
		l[o]=read(),r[o]=read()-1,ord[o]=o;
	sort(ord,ord+q,[](int x,int y){
		if(l[x]/B==l[y]/B) {
			if((l[x]/B)&1) return r[x]<r[y];
			else return r[x]>r[y];
		}else
			return l[x]<l[y];
	});
	int L=1,R=0;
	f[0]=1;
	for(int O=0;O<q;O++){
		int o=ord[O];
		while(L>l[o]) del(buc[a[--L]]),ins(++buc[a[L]]);
		while(R<r[o]) del(buc[a[++R]]),ins(++buc[a[R]]);
		while(L<l[o]) del(buc[a[L]]),ins(--buc[a[L++]]);
		while(R>r[o]) del(buc[a[R]]),ins(--buc[a[R--]]);
		for(int i=0;i<=n;i++){
			if(i&1)
				addmod(ans[o],(ull)(mod-f[i])*fac[n-i]);
			else
				addmod(ans[o],(ull)f[i]*fac[n-i]);
		}
	}
	for(int o=0;o<q;o++)
		printf("%d\n",ans[o]);
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