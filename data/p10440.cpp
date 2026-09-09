// created time: 2026-09-07 19:22:38
#include<bits/stdc++.h>
#ifdef LOCAL
	#include"grader.cpp"
#endif
#include"island.h"
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

int fa[305],vis[305];
set<int>E[305];


void solve(int n,int l){
	for(int i=1;i<=n;i++) vis[i]=0;
	vis[1]=1;
	for(int i=1;i<n;i++){
		int v=query(1,i);
		vis[v]=1;
		for(int j=1;!fa[v];j++){
			int u=query(v,j);
			if(vis[u]) fa[v]=u;
			else fa[u]=v;
		}
	}
	for(int i=2;i<=n;i++){
		answer(fa[i],i);
	}
}
