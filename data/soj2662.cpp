// created time: 2026-11-11 08:52:20
#include<bits/stdc++.h>
#include"basis.h"
#ifdef LOCAL
	#include"grader.cpp"
#endif
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
const int B=8,V=64;
const int M=V/B;

ull b[V];

ull pre[M][1<<B];
int bit[M][1<<B];
void build(int x){
	for(int i=0;i<(1<<B);i++){
		bit[x][i]=-1;
		ull val=(ull)i<<(B*x);
		while(val){
			int j=__builtin_ctzll(val);
			if(j>=B*(x+1))break;
			if(!b[j]){ bit[x][i]=j; break; }
			val^=b[j];
		}
		pre[x][i]=val^(ull)i<<(B*x);
	}
}
void init_basis(){
	for(int i=0;i<V;i++)b[i]=0;
	for(int x=0;x<M;x++)build(x);
}
bool insert_number(ull v){
	if(!v) return 0;
	#pragma GCC unroll 8
	for(int x=0;x<M;x++){
		int ins=(v>>(B*x))&((1<<B)-1);
		v^=pre[x][ins];
		if(~bit[x][ins]){
			b[bit[x][ins]]=v;
			build(x);
			return 1;
		}
	}
	return 0;
}