// created time: 2026-05-27 08:58:01
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

int n,a[200005];
ll qz[200005],hz[200005];

void procedure(){
	n=read();
	ll ans=0,pt=0;
	for(int i=1;i<=n;i++){
		a[i]=read(),ans+=a[i],qz[i]=qz[i-1]+a[i];
		hz[i]=hz[i-1]+max(a[i],-a[i]);
	}

	for(int i=1;i<=n;i++){
		if(a[i]>0){
			ll cur=hz[i-1]-a[i]+qz[n]-qz[i];
			if(cur>ans) ans=cur,pt=i;
		}
	}

	int o=0;
	vector<int>vec;
	for(int i=pt-1;i>=1;i--){
		if(o)a[i]=-a[i];
		if(a[i]>0)o^=1,vec.pb(i);
	}
	if(pt)
		vec.pb(pt);
	printf("%d\n",(int)vec.size());
	for(auto x:vec) printf("%d ",x);puts("");
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