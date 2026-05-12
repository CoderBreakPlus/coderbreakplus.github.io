// created time: 2026-05-12 14:46:29
// https://qoj.ac/contest/1906/problem/10073
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
#include<bits/extc++.h>
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

mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ull msk = rnd();
ull shift(ull x) {
	x ^= msk;
	x ^= x << 13;
	x ^= x >> 7;
	x ^= x << 17;
	x ^= msk;
	return x;
}
int n,k,c[100005],cid,rt[100005];
ull hsh[100005];


vector<int>E[100005];

void dfs(int x,int fa){
	for(auto y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
	}
}
bool f=0;

void down(int x,int fa){
	if(c[x])return;
	c[x]=cid;
	for(auto y:E[x]){
		if(y==fa)continue;
		down(y,x);
	}
}
void link(int x,int y){ hsh[x]+=shift(hsh[y]); }
void cut(int x,int y){ hsh[x]-=shift(hsh[y]); }

int solve(int x,int fa){
	if(f)return 0;
	int sz=1;
	hsh[x]=1;
	for(auto y:E[x]){
		if(y==fa)continue;
		sz+=solve(y,x);
		if(!c[y]) link(x,y);
	}
	if(sz>k){
		f=1;
		return 0;
	}
	if(sz==k){
		rt[++cid]=x;
		down(x,fa);
		return 0;
	}
	return sz;
}


__gnu_pbds::gp_hash_table<ull,int>mp;
__gnu_pbds::gp_hash_table<ull,int>st;

void change(int x,int fa){
	if(!st[hsh[x]]){
		st[hsh[x]]=1;
		mp[hsh[x]]++;
	}
	for(auto y:E[x]){
		if(y==fa||c[y]!=c[x])continue;
		cut(x,y),link(y,x);
		change(y,x);
		cut(y,x),link(x,y);
	}
}
void procedure(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}

	int ans=0;
	for(k=1;k<=n;k++){
		if(n%k==0){
			memset(c,0,sizeof(c));
			f=cid=0;
			if(solve(1,0) || f)continue;
			mp.clear();

			// cout<<"k="<<k<<" split: ";
			// for(int i=1;i<=n;i++)cout<<c[i]<<" ";cout<<endl;

			for(int i=1;i<=cid;i++){
				st.clear();
				change(rt[i],0);
			}

			for(auto [x,y]: mp)if(y==cid){
				f=1;
				break;
			}
			ans+=f;
		}
	}
	printf("%d\n",ans);
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