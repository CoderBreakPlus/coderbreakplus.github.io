// created time: 2026-04-04 10:38:58
// F. 1e16 Cities
// https://qoj.ac/contest/3575/problem/17718
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }
ll A,B,Q;

ll hsh[10000005];
ll fa[10000005];
ll find(ll x){if(x!=fa[x])fa[x]=find(fa[x]);return fa[x];}

map<ll,ll>mp;
ll ic;
ll getid(ll v){
	if(!mp.count(v)) {
		++ic;
		hsh[ic]=v, fa[ic]=ic;
		mp[v]=ic;
	}
	return mp[v];
}
void merge(ll x,ll y){
	x=find(x),y=find(y);
	if(x!=y)
	hsh[y]^=hsh[x],fa[x]=y;
}
const ll UP = 1e16;

void chk(ll d){
	ll val=B/d+A;
	for(ll i=1;i*i<=val;i++){
		if(val%i==0 && __gcd(i,val/i)==1){
			ll p=1ll*d*i,q=1ll*d*(val/i);
			if(p>UP || q>UP) continue;
			merge(getid(p),getid(q));
		}
	}
}

void procedure(){
	A=read(),B=read(),Q=read();
	for(ll d=1;d*d<=B;d++){
		if(B%d==0){
			chk(d);
			if(d*d!=B)chk(B/d);
		}
	}
	while(Q--){
		ll w=read();
		printf("%lld\n", hsh[find(getid(w))]);
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