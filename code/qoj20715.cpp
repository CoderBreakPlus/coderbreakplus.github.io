// created time: 2026-09-28 15:15:02
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
const int M = 4.5e4, K = 800;
int n,k,q,ls[300005],rs[300005],a[200005];

ll dp[M+5][K+5],f[K+5],tmp[K+5],ans[300005];

#define dp(x) dp[(x)-l]

vector<int>vec[200005];

void solve(int l,int mid,int r){
	// cout<<"solve "<<l<<" "<<mid<<" "<<r<<endl;
	for(int i=mid+1;i<=r;i++)vec[i].clear();
	for(int i=1;i<=q;i++)
		if(l<=ls[i]&&ls[i]<=mid&&mid<rs[i]&&rs[i]<=r)vec[rs[i]].pb(i);

	memset(dp,0,sizeof(dp));
	memset(tmp,0xc0,sizeof(tmp));
	for(int i=mid;i>=l;i--){
		memcpy(dp(i),dp(i+1),sizeof(dp(i)));
		for(int j=0;j<=k;j++)
			chkmax(tmp[j],dp(i+1)[j]+a[i]);
		for(int j=1;j<=k;j++)
			chkmax(dp(i)[j],tmp[j-1]-a[i]);
	}

	memset(f,0,sizeof(f));
	memset(tmp,0xc0,sizeof(tmp));
	for(int i=mid+1;i<=r;i++){
		for(int j=0;j<=k;j++)
			chkmax(tmp[j],f[j]-a[i]);
		for(int j=1;j<=k;j++)
			chkmax(f[j],tmp[j-1]+a[i]);
		for(int o: vec[i]) {
			for(int j=0;j<=k;j++)
				chkmax(ans[o],f[j]+dp(ls[o])[k-j]);
		}
	}

	memset(dp,0xc0,sizeof(dp));
	memset(tmp,0,sizeof(tmp));
	for(int i=mid;i>=l;i--){
		memcpy(dp(i),dp(i+1),sizeof(dp(i)));
		for(int j=0;j<=k;j++)
			chkmax(tmp[j],dp(i+1)[j]+a[i]);
		for(int j=1;j<=k;j++)
			chkmax(dp(i)[j],tmp[j-1]-a[i]);
	}


	memset(f,0xc0,sizeof(f));
	memset(tmp,0,sizeof(tmp));
	for(int i=mid+1;i<=r;i++){
		for(int j=0;j<=k;j++)
			chkmax(tmp[j],f[j]-a[i]);
		for(int j=1;j<=k;j++)
			chkmax(f[j],tmp[j-1]+a[i]);
		for(int o: vec[i]) {
			for(int j=1;j<=k;j++)
				chkmax(ans[o],f[j]+dp(ls[o])[k+1-j]);
		}
	}
}
void procedure(){
	n=read(),k=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=a[i+n]=read();
	for(int i=1;i<=q;i++){
		ls[i]=read(),rs[i]=read();
		if(ls[i]>rs[i])rs[i]+=n;
	}

	int L=max(1,int(0.15*n)), R=max(1,int(0.85*n)), st=L-1;
	while(st-L+1<=n) solve(st-L+1, st, st+R), st += L;

	for(int i=1;i<=q;i++) printf("%lld\n",ans[i]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}