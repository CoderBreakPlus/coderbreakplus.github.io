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

int n,x,y,vis[100005],i[100005],j[100005];

map<pair<int,int>,int>mp;
map<int,int>mx,my;

int flg=0;
void dfsy(int o);
void dfsx(int o){
	if(flg||vis[o])return;
	int x=i[o],y=j[o];
	if(mp.count({x-2,y})^mp.count({x-1,y})){flg=1;return;}
	if(mp.count({x+2,y})^mp.count({x+1,y})){flg=2;return;}
	int now=1+mp.count({x-2,y})+mp.count({x-1,y})+mp.count({x+2,y})+mp.count({x+1,y});
	if(now!=my[y]){ flg=3;return; }

	vis[o]=1;
	if(mp.count({x-2,y})){
		if(!mp.count({x-1,y-1})||!mp.count({x-1,y+1})){flg=-1;return;}
		dfsy(mp[{x-2,y}]);
	}
	if(mp.count({x+2,y})){
		if(!mp.count({x+1,y-1})||!mp.count({x+1,y+1})){flg=-1;return;}
		dfsy(mp[{x+2,y}]);
	}
}
void dfsy(int o){
	if(flg||vis[o])return;
	int x=i[o],y=j[o];
	if(mp.count({x,y-2})^mp.count({x,y-1})){flg=4;return;}
	if(mp.count({x,y+2})^mp.count({x,y+1})){flg=5;return;}
	int now=1+mp.count({x,y-2})+mp.count({x,y-1})+mp.count({x,y+2})+mp.count({x,y+1});
	if(now!=mx[x]){ flg=6;return; }

	vis[o]=1;
	if(mp.count({x,y-2})){
		if(!mp.count({x-1,y-1})||!mp.count({x+1,y-1})){flg=-2;return;}
		dfsx(mp[{x,y-2}]);
	}
	if(mp.count({x,y+2})){
		if(!mp.count({x-1,y+1})||!mp.count({x+1,y+1})){flg=-2;return;}
		dfsx(mp[{x,y+2}]);
	}
}
void procedure(){
	flg=0;
	n=read(),x=read(),y=read();
	mp.clear(),mx.clear(),my.clear();
	mp[{x,y}]=n+1;
	i[n+1]=x,j[n+1]=y;
	mx[x]++,my[y]++;

	for(int o=1;o<=n+1;o++)vis[o]=0;
	for(int o=1;o<=n;o++){
		x=read(),y=read();
		mx[x]++,my[y]++;
		mp[{x,y}]=o;
		i[o]=x,j[o]=y;
	}
	dfsx(n+1);
	for(int i=1;i<=n+1;i++)vis[i]=0;
	dfsy(n+1);
	// cerr<<"flg="<<flg<<endl;
	puts(flg?"YES":"NO");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}