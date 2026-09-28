// created time: 2026-09-28 19:42:56
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
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
const ll INF = 1e12;
int n,q,a[100005];

vector<pair<ll,ll>>t[100005][2][2];

#define mid ((l+r)>>1)
template<class A, class B> pair<A, B> operator+(const pair<A, B>& x,const pair<A, B>& y) {
    return {x.fi + y.fi, x.se + y.se};
}
pair<ll,ll> query(int p,int a,int b,ll v){
	return t[p][a][b][upper_bound()];
}
void build(int l,int r,int p){
	if(l==r){
		t[p][0][0]={{2*a[l],0},{INF,-a[l]}};
		t[p][1][1]={{-2*a[l],0},{INF,a[l]}};
		return;
	}
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);

	auto calc=[&](int a,int b,ll v){
		auto t1 = t[p<<1][a][0]
	};
	for(int a:{0,1})for(int b:{0,1}){
		ll L=-INF,R=INF-1,ans=INF;

		while(L<=R){
			ll M=(L+R)>>1;

		}
	}
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();


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