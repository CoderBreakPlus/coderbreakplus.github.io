// created time: 2026-11-03 16:02:52
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

int n,p[200005],f[200005],g[200005],prv[200005];

pair<int,int> c[200005];

void clear(){
	for(int i=1;i<=n;i++)c[i]={0,0};
}
void upd(int x,pair<int,int> w){
	while(x<=n){
		chkmax(c[x],w);
		x+=(x&-x);
	}
}
pair<int,int> qry(int x){
	pair<int,int> ret={0,0};
	while(x){
		chkmax(ret,c[x]);
		x-=(x&-x);
	}
	return ret;
}
void procedure(){
	n=read();
	clear();
	for(int i=1;i<=n;i++)p[i]=read();

	int k=0,lst=0;
	for(int i=1;i<=n;i++){
		auto [a,b]=qry(p[i]);
		f[i]=a+1,prv[i]=b;

		if(f[i]>k){
			k=f[i];
			lst=i;
		}
		upd(p[i],{f[i],i});
	}

	if(~k&1){
		puts("YES");
		return;
	}
	vector<bool>vis(n+1);

	int now=lst;
	while(now)vis[now]=1,now=prv[now];

	clear();
	for(int i=n;i>=1;i--){
		g[i]=qry(n-p[i]+1).fi+1;
		upd(n-p[i]+1,{g[i],i});
	}
	for(int i=1;i<=n;i++){
		if(f[i]+g[i]-1>=(k+1)/2&&!vis[i]){
			puts("YES");
			return;
		}
	}
	puts("NO");
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