// created time: 2026-08-31 08:11:39
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

int n,m,dag[1000005],ind[1000005],ans[1000005];
vector<int>E[1000005],G[1000005];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int a=read(),b=read();
		E[a].pb(b);	
	}
	for(int i=1;i<=n;i++){
		if(!dag[i]){
			dag[i]=1;
			// cout<<"insert "<<i<<endl;
			for(int j:E[i])if(j>i)dag[j]=-1;
		}
	}

	for(int i=1;i<=n;i++)
		for(int j:E[i])if(dag[i]==1&&dag[j]==1)
			G[i].pb(j),ind[j]++;

	queue<int>q;
	for(int i=1;i<=n;i++)
		if(dag[i]==1&&!ind[i])q.push(i); 

	vector<int>stardust;
	while(!q.empty()){
		int x=q.front();q.pop();
		if(!ans[x]) ans[x]=1, stardust.pb(x);
		for(int y:G[x]){
			if(ans[x]==1) ans[y]=-1;
			if(!--ind[y]) q.push(y);
		}
	}

	printf("%d\n", (int)stardust.size());
	for(int x: stardust) printf("%d ",x);
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