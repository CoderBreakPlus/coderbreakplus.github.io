// created time: 2026-11-13 07:56:39
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

int n,m,vis[400005],seq[400005],tp,cnt[400005];
char s[400005];

vector<pair<int,int>>E[400005];
int hd[400005];

void dfs(int x){
	while(hd[x]<E[x].size()){
		auto [y,i]=E[x][hd[x]++];
		if(vis[i])continue;
		vis[i]=1;
		dfs(y);
	}
	seq[++tp]=x;
}
void procedure(){
	n=read(),m=read();
	int rt=0;
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		rt=u;
		E[u].pb(v,i);
		E[v].pb(u,i);
	}
	for(int i=1;i<=n;i++)
		if(E[i].size()&1){puts("No");return;}
	scanf("%s",s+1);
	dfs(rt);
	--tp;
	if(tp!=m){
		puts("No");
		return;
	}

	int sum=0,mn=0,pos=0;
	for(int i=1;i<=m;i++){
		if(s[seq[i]]=='(')sum++;
		else sum--;
		if(sum<mn) mn=sum,pos=i;
	}
	if(sum!=0){
		puts("No");
		return;
	}
	puts("Yes");
	for(int i=pos+1;i<=m;i++)
		printf("%d ",seq[i]);
	for(int i=1;i<=pos;i++)
		printf("%d ",seq[i]);
	puts("");
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