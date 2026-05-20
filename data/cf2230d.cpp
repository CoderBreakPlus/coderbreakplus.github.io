// created time: 2026-05-20 18:49:31
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
int n,a[500005],b[500005],buca[500005],bucb[500005],fr[500005];

void procedure(){
	n=read();
	for(int i=1;i<=n+1;i++)buca[i]=n+1,bucb[i]=n+1;
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();

	ll ans=0;
	for(int i=n;i>=1;i--){
		if(a[i]==b[i]){
			if(buca[a[i]+1]==bucb[a[i]+1]&&buca[a[i]+1]!=n+1) fr[i]=fr[buca[a[i]+1]];
			else fr[i]=min(buca[a[i]+1],bucb[a[i]+1])-1;
		}
		buca[a[i]]=i,bucb[b[i]]=i;

		if(buca[1]==bucb[1] && buca[1]<=n){
			int sb=fr[buca[1]];
			ans+=(sb-i+1);
		}else{
			ans+=min(buca[1],bucb[1])-i;
		}
	}
	printf("%lld\n",ans);
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