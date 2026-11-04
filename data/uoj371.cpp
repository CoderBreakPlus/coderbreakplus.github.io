// created time: 2026-11-04 10:35:10
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

int n,s,t;
double x[1005],y[1005];
double get(int i, int j) {
	return sqrt((x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]));
}
double get(int i, int j, int k) {
	if ((x[i] - x[j]) * (x[k] - x[j]) + (y[i] - y[j]) * (y[k] - y[j]) > 0 &&
		(x[i] - x[k]) * (x[j] - x[k]) + (y[i] - y[k]) * (y[j] - y[k]) > 0) return
		abs((x[j] - x[i]) * (y[k] - y[i]) - (y[j] - y[i]) * (x[k] - x[i])) / get(j, k);
	return min(get(i, j), get(i, k));
}
vector<pair<int,int>>E[1005];
int u[1005],v[1005];
bool vis[1005][1005];
bool check(double D){
	if(D<get(s,t))return 0;
	memset(vis,0,sizeof(vis));
	queue<pair<int,int>>q;
	auto add=[&](int x,int y){
		if(get(x,u[y],v[y])>D||vis[x][y]) return;
		vis[x][y]=1;q.emplace(x,y);
	};
	for(auto [x,i]:E[s])add(t,i);
	for(auto [y,i]:E[t])add(s,i);
	while(!q.empty()){
		auto [x,y]=q.front();q.pop();
		// cout<<"node "<<x<<" with edge "<<u[y]<<" "<<v[y]<<endl;
		if(E[x].size()==1&&E[u[y]].size()==1&&get(x,u[y])<=D)return 1;
		if(E[x].size()==1&&E[v[y]].size()==1&&get(x,v[y])<=D)return 1;
		for(auto [xx,i]:E[x])add(xx,y),add(u[y],i),add(v[y],i);
	}
	return 0;
}
void procedure(){	
	n=read(),s=read(),t=read();
	for(int i=1;i<=n;i++)x[i]=read(),y[i]=read();
	for(int i=1;i<n;i++){
		u[i]=read(),v[i]=read();
		E[u[i]].pb(v[i],i),E[v[i]].pb(u[i],i);
	}
	// check(2);
	double L=0,R=2e6;
	while(R-L>1e-7){
		double M=(L+R)/2;
		if(check(M)) R=M;
		else L=M;
	}
	printf("%.10lf\n",L);
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