// created time: 2026-09-08 07:34:42
#include<bits/stdc++.h>
#include"ball.h"
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
#define i128 __int128

void init(int c,int t){

}
pair<int,ll> ball(ll n,ll m,ll x0,ll y0,ll vx,ll vy,ll T){
	if(vx<0) x0=n-x0,vx=-vx;
	if(vy<0) y0=m-y0,vy=-vy;
	
	i128 L=(x0+n-1)/n, R=(x0+(i128)vx*T)/n;
	i128 U=(y0+m-1)/m, D=(y0+(i128)vy*T)/m;

	int w = (R-L>D-U)?1:(R-L==D-U?0:-1);
	ll sb = max((R-L)-(D-U),(D-U)-(R-L));
	return {w,sb};
}