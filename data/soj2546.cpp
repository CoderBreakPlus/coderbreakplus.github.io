// created time: 2026-04-21 08:13:04
// http://10.49.18.71/problem/2546
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

int n,m,q,fa[100005];
ll out[500005];

set<int>S[100005];
vector<tuple<int,int,int>>edge;
vector<pair<int,int>>vec[100005],que[100005];

ll c[100005];
void upd(int x,ll w){
	while(x<=n){
		c[x]+=w;
		x+=(x&-x);
	}
}
ll qry(int x){
	ll ret=0;
	while(x){
		ret+=c[x];
		x-=(x&-x);
	}
	return ret;
}
void procedure(){
	n=read(),m=read(),q=read();

	for(int i=1;i<=n;i++)S[i].emplace(i),fa[i]=i;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		edge.pb(w,u,v);
	}	
	sort(edge.begin(), edge.end());

	ll ans=0;
	for(auto [w,u,v]: edge){
		u=fa[u],v=fa[v];
		if(u==v)continue;
		ans+=w;
		if(S[u].size()<S[v].size()) swap(u,v);
		vector<pair<int,int>>now;
		for(auto x: S[v]) S[u].emplace(x);
		for(auto x: S[v]){
			auto it = S[u].find(x);
			if(it != S[u].begin() && fa[*prev(it)] == u)
				now.pb(*prev(it), x);
			if(next(it) != S[u].end() && fa[*next(it)] == u)
				now.pb(x, *next(it));
		}
		for(auto [l,r]: now){
			if(l<=r) vec[l].pb(r,-w);
		}

		for(int i=0;i+1<now.size();i++){
			int l=now[i].fi,r=now[i+1].se;
			if(l<=r) vec[l].pb(r,w);
		}
		for(auto x: S[v]) fa[x]=u;
		S[v].clear();
	}
	for(int i=1;i<=q;i++){
		int l=read(),r=read();
		que[l].pb(r,i);
	}

	for(int l=n;l>=1;l--){
		for(auto [r,w]: vec[l]) upd(r,w);
		for(auto [r,i]: que[l]) out[i]=ans+qry(r);
	}

	for(int i=1;i<=q;i++) printf("%lld\n",out[i]);
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