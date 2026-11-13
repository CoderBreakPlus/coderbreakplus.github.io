// created time: 2026-11-13 09:07:17
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

int n,m;

#define lb long double
void procedure(){
	n=read(),m=read();
	ll ans=0;
	if(n&1){
		ans=(m+1ll)*(2ll*m+1);
		vector<int> exact(m+1,-1);
		for(ll t=1;;t++){
			ll v=1,lim=m/n;
			bool ok=true;
			for(int i=0;i<n-1;i++){
				if(v>lim/t){
					ok=false;
					break;
				}
				v*=t;
			}
			if(!ok) break;
			exact[n*v]=min<ll>(m,(n-1LL)*v*t);
		}
		for(int p=1;p<=m;p++){
			lb C=(lb)p*(n-1)/n*expl(logl((lb)p/n)/(n-1));
			int k;
			if(exact[p]!=-1) k=exact[p];
			else if(C>=m) k=m;
			else k=floorl(C);
			ans+=2LL*(m-k);
		}
	}else{
		ans=1;
		for(ll t=1;;t++){
			ll v=1,lim=m/n;
			bool ok=true;
			for(int i=0;i<n-1;i++){
				if(v>lim/t){
					ok=false;
					break;
				}
				v*=t;
			}
			if(!ok) break;
			if(v>m/(n-1)/t) break;
			ans+=2;
		}
	}
	printf("%lld\n",ans);
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