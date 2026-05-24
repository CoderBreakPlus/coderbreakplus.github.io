// created time: 2026-05-24 19:44:13
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

int n,c,a[20005];
const int M=2e4;
int F[40005],G[40005];
int *f=F+M, *g=G+M;

void procedure(){
	n=read(),c=read();
	for(int i=1;i<=n;i++)a[i]=read();
	int sum=0,p=n;
	for(int i=1;i<=n;i++){
		if(sum+a[i]>c){
			p=i-1;
			break;
		}
		sum+=a[i];
	}
	for(int i=-M;i<=M;i++)f[i]=0;
	if(p==n){
		printf("%d\n",sum);
		return;
	}
	// cout<<"sum="<<sum<<" c="<<c<<endl;
	f[sum-c]=p+1;
	for(int i=p+1;i<=n;i++){
		for(int j=-M;j<=M;j++)g[j]=f[j];
		for(int j=-M;j<=0;j++)chkmax(g[j+a[i]],f[j]);

		for(int j=M;j>=1;j--)
			for(int k=g[j]-1;k>=max(1,f[j]);k--)
				chkmax(g[j-a[k]],k);

		for(int j=-M;j<=M;j++)f[j]=g[j];
	}
	int fk=0;
	for(int j=0;j>=-M;j--)
		if(f[j]){
			// cout<<j<<" f="<<f[j]<<endl;
			printf("%d\n",c+j);return;
		}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}