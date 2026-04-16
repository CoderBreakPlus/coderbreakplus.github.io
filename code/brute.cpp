// created time: 2026-04-16 07:47:15
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
inline ll INV(ll x){ return qpow(x, mod-2); }
const int B=400,N=500000;

int n,m,a[N+5];
ll ans[N+5];
vector<pair<int,int>>q[N+5];

struct BIT{
	int c[N+5];
	void upd(int x,int w){
		while(x<=n) c[x]+=w,x+=(x&-x);
	}
	int qry(int x){
		int ret=0;
		while(x) ret+=c[x],x-=(x&-x);
		return ret;
	}
}bit;

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++){
		int y=read();
		while(y--){
			int l=read(),r=read();
			q[i].pb(l,r);

			for(int x=l;x<=r;x++) ans[i]+=bit.qry(a[x]);
			for(int x=l;x<=r;x++) bit.upd(a[x],1);
		}
		for(auto [l,r]: q[i]){
			for(int x=l;x<=r;x++) bit.upd(a[x],-1);
		}
	}
	for(int i=1;i<=m;i++) printf("%lld\n",ans[i]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}