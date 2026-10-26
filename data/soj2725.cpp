// created time: 2026-10-26 08:11:43
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

int n,a[1000005],b[1000005];
vector<pair<int,int>>E[1000005];
int up[1000005],down[1000005];

bool fail=0;

pair<int,int> dfs(int x,int fa,int j){
	map<int,int>mp;
	for(auto [y,i]:E[x])if(y!=fa){
		auto [a,b]=dfs(y,x,i);
		if(a==-1||b==-1)return {-1,-1};
		mp[a]++,mp[b]--;
	}
	mp[a[x]]++,mp[b[x]]--;
	vector<int>add,del;
	for(auto [w,cnt]:mp)if(cnt){
		if(cnt>0)while(cnt--)del.pb(w);
		else{
			cnt=-cnt;
			while(cnt--)add.pb(w);
		}
	}
	if(!j){
		if(add.size()||del.size()){fail=1;return{-1,-1};}
		return {0,0};
	}else{
		if(add.empty()&&del.empty()){
			up[j]=down[j]=0;
			return {0,0};
		}else{
			if(add.size()>1||del.size()>1){
				fail=1;return{-1,-1};
			}
			up[j]=add[0],down[j]=del[0];
			return {down[j],up[j]};
		}
	}
}

vector<int>fuck[1000005];
bool buc[1000005];

namespace Graph{
	int fa[1000005];
	int deg[1000005];
	int u[1000005],v[1000005],sz;
	void addedge(int x,int y){
		u[++sz]=x,v[sz]=y;
		deg[x]++,deg[y]++;
	}
	void clear(){
		while(sz){
			deg[u[sz]]=deg[v[sz]]=0;
			sz--;
		}
	}
	int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]); return fa[x]; }
	bool solve(int x,int y){
		if(!sz)return x==y;
		if(!deg[x]||!deg[y])return 0;

		deg[x]++,deg[y]++;
		for(int i=1;i<=sz;i++) fa[u[i]]=u[i],fa[v[i]]=v[i];
		for(int i=1;i<=sz;i++){
			fa[find(u[i])]=find(v[i]);
		}

		for(int i=1;i<=sz;i++){
			if(find(u[i])!=find(u[1])) return 0;
			if(deg[u[i]]%2||deg[v[i]]%2) return 0;
		}
		return 1;
	}
}
bool check(int x,int fa,int j){
	fuck[x].clear();
	vector<int>chk;
	for(auto [y,i]:E[x]){
		if(y!=fa){
			if(!check(y,x,i)) return 0;
			if(up[i]==down[i]){
				chk.pb(y);
				continue;
			}
		}
	}
	Graph::clear();
	for(auto [y,i]:E[x]){
		if(up[i]!=down[i]){
			Graph::addedge(up[i],down[i]);
			fuck[x].pb(up[i]),fuck[x].pb(down[i]);
		}
	}
	if(!Graph::solve(a[x],b[x])){
		return 0;
	}
	bool flg=1;
	fuck[x].pb(a[x]),fuck[x].pb(b[x]);
	for(int w:fuck[x]) buc[w]=1;
	for(int y:chk){
		bool hv=0;
		for(int z:fuck[y])hv|=buc[z];
		flg&=hv;
	}
	for(int w:fuck[x]) buc[w]=0;
	return flg;
}
void procedure(int testcase){
	n=read();fail=0;
	for(int i=1;i<=n;i++)a[i]=read(),E[i].clear();
	for(int i=1;i<=n;i++)b[i]=read();
	if(testcase==92){
		cerr<<n<<endl;
	}
	if(n==1){ puts("YES"); return; }
	for(int i=1;i<n;i++){
		up[i]=down[i]=0;
		int u=read(),v=read();
		E[u].pb(v,i),E[v].pb(u,i);
	}
	dfs(1,0,0);
	if(fail){ puts("NO");return; }
	puts(check(1,0,0)?"YES":"NO");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	for(int i=1;i<=T;i++) procedure(i);
	return 0;
}