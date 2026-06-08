// created time: 2026-06-08
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
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };

ll n; vector<ll>E[1000005];
bool dp[1000005][4];

set<int>s[1000005]; int si[1000005];
void upd(bool *f, vector<bool*> g, bool fvv){
	if(g.size() >= 4) return;

	if(g.size() == 3){
		vector<int>v={0,1,2};
		do{
			f[3] |= g[v[0]][2] && g[v[1]][1] && g[v[2]][0];
		}while(next_permutation(v.begin(),v.end()));
	}else if(g.size() == 2){
		f[0] = (g[0][0] && g[1][1]) || (g[1][0] && g[0][1]);
		f[3] = (g[0][2] && g[1][3]) || (g[1][2] && g[0][3]);
	}else if(g.size() == 1){
		f[0] = g[0][0] || (!fvv && g[0][3]);
		f[1] = g[0][2];
		f[2] = g[0][1];
		f[3] = (g[0][2] || g[0][3]);
	}else{
		f[0] = f[1] = f[2] = f[3] = 1;
	}
	assert(f[1] == f[2]);
}
void solve(int x){
	dp[x][0]=dp[x][1]=dp[x][2]=dp[x][3]=0;
	if(s[x].size()>=4)return;
	vector<bool*> tmp;
	for(auto y: s[x]){
		tmp.pb(dp[y]);
	}
	upd(dp[x], tmp, si[x]);
}
void dfs(int x,int fa){
	bool ok=0;
	for(auto y: E[x]){
		if(y==fa) continue;
		dfs(y,x);
	}

	if(fa){
		if(E[fa].size() == 1) si[x]--;
		else s[x].erase(fa);
	}
	solve(x);
	if(fa){
		if(E[fa].size() == 1) si[x]++;
		else s[x].insert(fa);
	}
}
ll ans=0;
void change(int x,int fa){
	ans |= dp[x][0];

	for(auto y: E[x]){
		if(y==fa) continue;

		if(E[y].size() == 1) si[x]--;
		else s[x].erase(y);

		solve(x);

		if(E[x].size() == 1) si[y]++;
		else s[y].insert(x);

		solve(y);

		change(y, x);

		if(E[x].size() == 1) si[y]--;
		else s[y].erase(x);

		solve(y);

		if(E[y].size() == 1) si[x]++;
		else s[x].insert(y);

		solve(x);
	}
}

void procedure(ll id){
	ans=0;
	n=read();
	for(ll i=1;i<=n;i++) E[i].clear(),dp[i][0]=dp[i][1]=dp[i][2]=dp[i][3]=si[i]=0,s[i].clear();

	for(ll i=1;i<n;i++){
		ll u=read(),v=read();
		E[u].pb(v); E[v].pb(u);
	}

	bool flg=1;
	for(ll i=1;i<=n;i++) flg&=(E[i].size()<=2);
	if(flg){
		puts("1");
		return;
	}

	for(ll i=1;i<=n;i++){
		for(auto j: E[i]){
			if(E[j].size()==1) si[i]++;
			else s[i].insert(j);

			if(E[i].size()==1) si[j]++;
			else s[j].insert(i);
		}
	}

	dfs(1,0);
	change(1,0);
	puts(ans ? "2": "3");
}
int main(){
	#ifdef LOCAL
		assert(freopen("input.txt","r",stdin));
		assert(freopen("output.txt","w",stdout));
	#endif
	ll T=read();
	// math_init();
	// NTT::init();

	for(ll i=1;i<=T;i++) procedure(i);
	return 0;
}