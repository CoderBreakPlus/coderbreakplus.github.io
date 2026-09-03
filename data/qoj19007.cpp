// created time: 2026-09-03 08:42:31
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

int n,q,a[200005];

template<typename T>struct BIT{
	T c[200005];
	void upd(int x,T w){
		while(x<=n){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	T qry(int x){
		T ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
};

BIT<ll>b1;
BIT<double>b2;

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) {
		a[i]=read(), b1.upd(i,INV(a[i])), b2.upd(i, 1.0/a[i]);
	}

	while(q--){
		int o=read();
		if(o==1){
			int i=read(),x=read();
			b1.upd(i, (mod-INV(a[i])+INV(x))%mod);
			b2.upd(i, 1.0/x-1.0/a[i]);
			a[i]=x;
		}else{
			int l=read(),r=read();
			int val=((b1.qry(r)-b1.qry(l-1))%mod+mod)%mod;
			int val2 = floor(b2.qry(r)-b2.qry(l-1));

			// cout<<val<<","<<val2<<endl;

			puts(abs(val-val2)<=5?"yes":"no");
		}
	}
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