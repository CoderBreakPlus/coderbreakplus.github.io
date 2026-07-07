// created time: 2026-07-07 14:08:50
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

int n,a[305],d[305][305];

pair<ll,int> f[305][305];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++){
			f[i][j].fi=d[i][j]=-read();
			f[i][j].se=(i!=j);
		}

	for(int k=1;k<=n;k++)
	for(int i=1;i<=n;i++)
	for(int j=1;j<=n;j++)
		chkmax(f[i][j],{f[i][k].fi+f[k][j].fi,f[i][k].se+f[k][j].se});

	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++)
			if(d[i][j]!=f[i][j].fi){ puts("-1"); return; }

	vector<tuple<int,int,int>>vec;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(f[i][j].se==1)
				vec.pb(i,j,-d[i][j]);

	printf("%d\n",(int)vec.size());
	for(auto [a,b,c]:vec) printf("%d %d %d\n",a,b,c);
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