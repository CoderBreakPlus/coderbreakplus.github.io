// created time: 2026-05-13 14:51:02
#include"cheapai.h"
#include<bits/extc++.h>
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

const ull mod = 1428571428571429ull, base = 2137;
int n,s[200005];
ull pw[200005],qz[200005];

__gnu_pbds::gp_hash_table<ull,pair<int,int>>mp;

int cnt=0;

int calc(int x){
	cnt++;
	mp.clear();
	ull cur=qz[x]; int ans=0;
	for(int i=x;i<=n;i++){
		pair<int,int> &w = mp[cur];
		if(w.fi+x<=i) w.fi=i, chkmax(ans, ++w.se);
		cur=(cur*base+s[i-x]*(mod-pw[x])+s[i])%mod;
	}
	return ans;
}
int f[200005],ans;

void divide(int L,int R,int cl,int cr){
	if(L+1>=R||cl==cr||(ll)(R-2)*cl<ans)return;
	int mid=(L+R)>>1;
	f[mid]=calc(mid);
	chkmax(ans, (mid-1)*f[mid]);
	divide(L,mid,cl,f[mid]),divide(mid,R,f[mid],cr);
}

int solve(int K, string S){
	n=S.size();
	pw[0]=1;
	for(int i=1;i<=n;i++)
		pw[i]=pw[i-1]*base%mod;

	for(int i=0;i<n;i++) s[i]=S[i]-'a'+1;
	for(int i=0;i<n;i++)
		qz[i+1]=(qz[i]*base+s[i])%mod;

	f[1]=calc(1);
	f[K]=calc(K);
	ans=(K-1)*f[K];

	divide(1,K,f[1],f[K]);
	return n-ans;
}