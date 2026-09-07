// created time: 2026-09-07 07:22:34
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

int n,q,sz[300005];
vector<int>E[300005];
char s[300005];

void dfs(int x,int fa){
	sz[x]=1;
	for(int y:E[x]){
		if(y==fa)continue;
		dfs(y,x);
		sz[x]+=sz[y];
	}
}
bool has[300005];

void procedure(){
	n=read(),q=read();
	scanf("%s",s+1);
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	int rt=1; has[rt]=1;
	if(E[rt].size()==1){
		rt=E[rt][0],has[rt]=1;
		while(E[rt].size()==2) rt=(has[E[rt][0]]?E[rt][1]:E[rt][0]),has[rt]=1;
	}

	int all=0;
	for(int i=1;i<=n;i++)all+=has[i];

	int cnt=0, ban=0, low=0, low2=0, low3=0;
	for(int i=1;i<=n;i++){
		if(sz[i]!=1) cnt+=(s[i]=='?');
		else ban+=(s[i]=='D');
	}

	for(int i=1;i<=n;i++)
		if(has[i]) low+=(s[i]=='U'),low2+=(s[i]=='?'),low3+=(s[i]=='D');


	auto solve = [&](){
		if(n==1){
			if(s[1]=='?')puts("2");
			else puts("1");
			return;
		}
		if(all==n){
			if(s[1]=='U'||s[rt]=='D')puts("0");
			else
				printf("%d\n",qpow(2,cnt-(s[1]=='?')));
			return;
		}
		if(ban || low==all) puts("0");
		else{
			if(low+low2==all) printf("%d\n",(qpow(2,cnt)-qpow(2,cnt-low2)+mod)%mod);
			else printf("%d\n", qpow(2,cnt));
		}
	};

	solve();

	while(q--){
		int x=read(); char w[5];
		scanf("%s",w);

		if(sz[x]!=1){
			cnt-=(s[x]=='?');
			cnt+=(w[0]=='?');
		}else{
			ban-=(s[x]=='D');
			ban+=(w[0]=='D');
		}
		if(has[x]){
			low-=(s[x]=='U'), low2-=(s[x]=='?'), low3-=(s[x]=='D');
			low+=(w[0]=='U'), low2+=(w[0]=='?'), low3+=(w[0]=='D');
		}
		s[x]=w[0];

		solve();
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