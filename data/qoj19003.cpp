// created time: 2026-09-03 08:09:09
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int n,m,k,a[505][505];
ull Mod = (ull)1e16 + 2137, Base = rng(1e8,1e9);

bitset<505>b[250005];
int idx;
void procedure(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[i][j]=read();

	map<ull,int>mp;
	int ret=0;
	for(int j=1;j<=m;j++){
		set<ull>tmp;
		bitset<505>sb;
		for(int i=1;i<=n-k+1;i++){
			ull now=0;
			for(int x=i+1;x<=i+k-1;x++)
				now=((__int128)now*Base+a[x][j]-a[x-1][j]+100000)%Mod;
			if(tmp.count(now))continue;
			tmp.emplace(now);

			if(mp.count(now)) sb|=b[mp[now]];
			else mp[now]=++idx;

			b[mp[now]][j]=1;
		}
		ret+=sb.count();
	}
	printf("%d\n",ret);
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