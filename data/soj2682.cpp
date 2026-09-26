// created time: 2026-09-26 07:38:24
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
const ll INF=1e18;
int n,m,q;
ll s[1000005],mn[1000005];
int l[1000005],r[1000005];
ll ans[1000005]; bool vis[1000005];
vector<int>vec[1000005],stk[1000005];

struct BIT{
	ll c[1000005];
	void upd(int x,ll w){
		// cout<<"upd "<<x<<" with "<<w<<endl;
		while(x<=n){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	ll qry(int x){
		ll ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
}B;

void procedure(){
	n=read(),m=read();	
	for(int i=m;i<=n;i++)s[i]=read()+s[i-m];
	for(int i=n;i>=1;i--)s[i]-=s[i-1];

	q=read();
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read();
		if(r[i]-l[i]+1<m)continue;
		vec[r[i]].pb(i);
	}
	for(int i=0;i<m;i++) stk[i].reserve(n/m+1);
	// for(int i=1;i<=n;i++) cout<<s[i]<<" "; cout<<endl;
	for(int i=1;i<=n;i++){
		// cout<<"r="<<i<<endl;
		B.upd(i,s[i]);
		int o=i%m;
		if(i>m){
			int lst=stk[o].back();
			B.upd(lst,-s[i]);
			while(!stk[o].empty()&&s[lst]<s[i]){
				ll dc=s[lst]-s[i];
				B.upd(lst,-dc);
				stk[o].pop_back();
				if(!stk[o].empty()) B.upd(lst=stk[o].back(),dc);
			}
		}
		stk[o].emplace_back(i);
		for(int j:vec[i]) ans[j]=B.qry(r[j])-B.qry(l[j]-1);
	}
	for(int i=1;i<=q;i++){
		if(r[i]-l[i]+1<m){ puts("unbounded");continue; }
		// cout<<"ans="<<ans[i]<<endl;
		ll x=ans[i]/m;
		while(-ans[i]+m*x<0) x++;
		while(-ans[i]+m*(x-1)>=0) x--;
		printf("%lld\n",x);
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