// created time: 2026-05-27 08:43:38
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

ll n,k,a[18],sum[1<<18],mx[1<<18];

bool f[19][1<<18];
ll mn[19][1<<18];

bool check(ll V){
	for(int i=0;i<=k;i++)
		for(int j=0;j<(1<<n);j++)f[i][j]=0,mn[i][j]=2e10;
	f[0][0]=1;
	for(int i=0;i<(1<<n);i++)mn[0][i]=0;
	for(int i=1;i<=k;i++)
		for(int j=0;j<(1<<n);j++)if(__builtin_popcount(j)>=i){
			if(f[i][j]=(sum[j]-mn[i-1][j]>=V)){
				mn[i][j]=sum[j];
			}
			int t=j;
			while(t){
				int w=(t&-t);
				chkmin(mn[i][j],mn[i][j^w]);
				t^=w;
			}
		}
	return f[k][(1<<n)-1];
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
void procedure(){
	n=read(),k=read();
	for(int i=0;i<n;i++)a[i]=read();
	sort(a,a+n);
	if(k==n){
		printf("%lld\n",a[n-1]);
		return;
	}
	ll out=0;
	for(int i:{n-1}){
		n--,swap(a[i],a[n]);
		for(int i=1;i<(1<<n);i++){
			int x=__builtin_ctz(i);
			sum[i]=sum[i^(1<<x)]+a[x];
		}
		ll L=max(0ll,out-a[n]), R=1.7e10, ans=L;
		if(check(L++)){
			while(L<=R){
				ll mid=(L+R)>>1;
				if(check(mid)){
					ans=mid;
					L=mid+1;
				}else R=mid-1;
			}
		}
		chkmax(out,ans+a[n]);
		swap(a[i],a[n]),n++;
	}
	printf("%lld\n",out);
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