// created time: 2026-11-09 07:51:52
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
int p[105],fa[105];
int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }

void solve(int n){
	vector<int>buc(n+1,0);
	for(int i=0;i<(1<<n-1);i++){
		int L=0,R=n+1;
		for(int j=0;j<n-1;j++){
			if((~i>>j)&1)p[++L]=j+1;
			else p[--R]=j+1;
		}
		p[++L]=n;
		for(int j=1;j<=n;j++)fa[j]=j;
		for(int j=1;j<=n;j++)fa[find(p[j])]=find(j);
		int cnt=0;
		for(int j=1;j<=n;j++)cnt+=(find(j)==j);
		buc[cnt]++;
	}
	for(int i=1;i<=n;i++)printf("%d ",buc[i]);
	puts("");fflush(stdout);
}
void procedure(){
	for(int n=1;n<=27;n++){
		solve(n);
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