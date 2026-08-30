// created time: 2026-08-30 10:52:15
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
int n,qz[300005];
char s[300005];

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
void procedure(){
	scanf("%s",s+1); n=strlen(s+1);
	for(int i=1;i<=n;i++)qz[i]=qz[i-1]+(s[i]!=s[i-1]);
	qz[n+1]=qz[n]+1;

	int j=1,ans=0;
	for(int i=1;i<=n;i++){
		while(qz[i]==qz[j])j++;

		if(j>n) break;

		// for(int k=0;k<=n-j;k++){
		// 	// cout<<i<<","<<k<<" ans = "<<binom(i-1+n-k,i-1)<<endl;
		// 	addmod(ans += binom(i-1+k,i-1));
		// }
		addmod(ans += binom(i+n-j,i));
	}

	for(int l=1;l<=n;l++)if(s[l]!=s[l-1]){
		int r=l;while(qz[r+1]==qz[l])r++;

		// cout<<"here "<<l<<"->"<<r<<endl;
		ans = (ans + (ull)(r-l+1) * binom(l-1+n-r,l-1)) % mod;

		// cout<<l<<"->"<<r<<" ans = "<<(ull)(r-l+1) * binom(l-1+n-r,l-1) % mod<<endl;

		if(l>1){
			for(int x=l;x<r;x++){
				ans = (ans + (ull)(x-l+1) * binom(l-2+n-x,n-x)) % mod;
				// cout<<l<<"->"<<x<<" ans = "<<(ull)(x-l+1) * binom(l-2+n-x,n-x) % mod<<endl;
			}
		}
		if(r<n){
			for(int x=l+1;x<=r;x++){
				ans = (ans + (ull)(r-x+1) * binom(x-2+n-r,x-1)) % mod;
				// cout<<x<<"->"<<r<<" ans = "<<(ull)(r-x+1) * binom(x-2+n-r,x-1) % mod<<endl;
			}
		}
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