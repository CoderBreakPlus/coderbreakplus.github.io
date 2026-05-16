// created time: 2026-05-16 09:41:03
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

ll n,m,sx,sy,sz,tx,ty,tz;

ll x[1005],y[1005],z[1005],a[1005],b[1005],c[1005];
map<pair<ll,ll>,vector<pair<ll,ll>>>S;

bool e[1005][1005];

ll dis[1005];

void procedure(){
	n=read(),m=read();
	sx=read(),sy=read(),sz=read();
	tx=read(),ty=read(),tz=read();

	ll St=0,To=0;
	for(ll i=1;i<=n;i++){
		dis[i]=-1;
		for(ll j=1;j<=n;j++)e[i][j]=0;
	}
	S.clear();

	for(ll i=1;i<=n;i++){
		x[i]=read(),y[i]=read(),z[i]=read();
		if(x[i]==sx && y[i]==sy && z[i]==sz-1) St=i;
		if(x[i]==tx && y[i]==ty && z[i]==tz-1) To=i;
		S[{x[i],y[i]}].emplace_back(z[i],i);
	}

	for(auto &[x,y]: S){ sort(y.begin(), y.end()); }
	assert(St&&To);
	for(ll i=1;i<=m;i++)a[i]=read(),b[i]=read(),c[i]=read();
	for(ll i=1;i<=n;i++){
		for(ll j=1;j<=m;j++){
			ll cx=x[i]+a[j],cy=y[i]+b[j],cz=z[i]+1+c[j];
			auto vec = S[{cx,cy}];
			auto it = lower_bound(vec.begin(), vec.end(), (pair<ll,ll>){cz+1,0});
			if(it == vec.begin()) continue;
			it = prev(it);
			if((it->fi)==cz) continue;
			e[i][it->se]=1;
		}
	}
	queue<int>q; q.push(St), dis[St]=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int i=1;i<=n;i++){
			if(!e[x][i] || ~dis[i]) continue;
			dis[i] = dis[x] + 1;
			q.push(i);
		}
	}
	printf("%lld\n", dis[To]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}