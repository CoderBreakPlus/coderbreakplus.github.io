// created time: 2026-05-16 12:47:03
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

int n; char s[250005],ss[2],c;
int f[250005];

int h[250005];
void procedure(){
	scanf("%s%s",s,ss); c=ss[0];
	n=strlen(s);

	int fs=0,ft=0,may=0;
	if(n&1) s[n/2]=c;
	for(int i=0;i<n;i++) fs+=(s[i]==c); // 初始有 fs 个 c 
	// 有 ft 个必须要打，剩下的 2may 个可打可不打

	for(int i=0,j=n-1;i<j;i++,j--){
		if(s[i]==c&&s[j]==c) continue;
		if(s[i]==c||s[j]==c) ft++;
		else if(s[i]==s[j]) may++;
		else ft+=2;
	}

	for(int j=0;j<=may;j++){
		f[j]=fac[ft+2*j];
		for(int k=0;k<j;k++)
			f[j]=(f[j]+(ull)(mod-f[k])*binom(j,k)%mod*fac[2*(j-k)])%mod;
	}

	for(int i=1;i<=n-fs;i++){
		for(int j=0;j<=fs;j++)
			h[i]=(h[i]+(ull)binom(fs,j)*binom(n-fs,i)%mod*INV(binom(n,i+j))%mod*i)%mod;
	}

	// for(int i=0;i<=n;i++) cout<<h[i]<<" ";cout<<endl;

	int ans=0;
	for(int j=0;j<=may;j++){
		f[j]=(ull)f[j]*binom(may,j)%mod*INV(perm(ft+2*may,ft+2*j))%mod;
		ans=(ans+(ull)f[j]*h[ft+2*j])%mod;
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