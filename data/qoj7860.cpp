// created time: 2026-04-02 16:46:22
// D. Graph of Maximum Degree 3
// https://qoj.ac/contest/1459/problem/7860
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

int n,m;
vector<int>E0[100005],E1[100005];
map<int,int>mp[100005];

int fa[100005];
int find(int x){if(x!=fa[x])fa[x]=find(fa[x]);return fa[x];}

set<vector<int>>fuck;
bool check(vector<int> S){
	sort(S.begin(),S.end());
	if(fuck.count(S)) return 0;
	fuck.emplace(S);
	bool ok=1;

	for(auto x: S) fa[x]=x;

	for(auto x: S)for(auto y: E0[x])
		if(fa[y]) fa[find(x)]=find(y);
	for(auto x: S)ok&=(find(x)==find(S[0]));

	for(auto x: S) fa[x]=x;

	for(auto x: S)for(auto y: E1[x])
		if(fa[y]) fa[find(x)]=find(y);
	for(auto x: S)ok&=(find(x)==find(S[0]));

	for(auto x: S) fa[x]=0;
	return ok;
}
void procedure(){
	n=read(),m=read();
	int ans=n;

	vector<pair<int,int>>vec,vec0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),w=read();
		if(u>v)swap(u,v);
		mp[u][v]++;
		if(!w)E0[u].pb(v),E0[v].pb(u),vec0.pb(u,v);
		else E1[u].pb(v),E1[v].pb(u);
		if(mp[u][v]>=2){
			vec.pb(u,v);
			ans+=check({u,v});
		}
	}
	int fk2=0;
	for(auto [u,v]: vec){
		int lp=0,rp=0;
		if(E0[u].size()==2){
			if(E0[u][0]==v) lp=E0[u][1];
			else lp=E0[u][0];
		}else if(E1[u].size()==2){
			if(E1[u][0]==v) lp=-E1[u][1];
			else lp=-E1[u][0];
		}

		if(E0[v].size()==2){
			if(E0[v][0]==u) rp=E0[v][1];
			else rp=E0[v][0];
		}else if(E1[v].size()==2){
			if(E1[v][0]==u) rp=-E1[v][1];
			else rp=-E1[v][0];
		}

		if(!lp||!rp) continue;
		if(lp+rp==0){
			ans+=check({u,v,max(lp,rp)});
		}
	}

	for(auto [u,v]: vec0){
		if(E0[u].size()!=2 || E0[v].size()!=2) continue;
		int lp=(E0[u][0]==v?E0[u][1]:E0[u][0]);
		int rp=(E0[v][0]==u?E0[v][1]:E0[v][0]);
		if(lp==rp) continue;
		ans+=check({u,v,lp,rp});
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