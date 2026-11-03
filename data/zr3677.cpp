// created time: 2026-11-03 07:24:47
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

int n,k;
pair<ll,ll> seq[2000005];
ll sum[2000005];

void procedure(){
	n=read(),k=read();
	ll bas=0;
	for(int i=1;i<=n;i++){
		int l=read();seq[i].fi=l;
		for(int j=1;j<=l;j++){
			int x=read();
			seq[i].se+=x,bas+=(ll)j*x;
		}
	}
	sort(seq+1,seq+n+1,[](pair<ll,ll> A,pair<ll,ll> B){
		return A.se*B.fi<B.se*A.fi;
	});
	for(int i=1;i<=n;i++)sum[i]=sum[i-1]+seq[i].fi;

	ll add=0,ans=-4e18;
	for(int i=1;i<=n;i++)
		add+=sum[i-1]*seq[i].se;

	if(k==1){
		printf("%lld\n",add+bas);
		return;
	}
	for(int i=1;i<n;i++){
		ll now=-sum[i-1]*seq[i].se-sum[i]*seq[i+1].se;
		now+=sum[i-1]*seq[i+1].se+(sum[i-1]+seq[i+1].fi)*seq[i].se;
		chkmax(ans,now);
	}
	printf("%lld\n",add+ans+bas);
}
int main(){
	assert(freopen("seq.in","r",stdin));
	assert(freopen("seq.out","w",stdout));
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}