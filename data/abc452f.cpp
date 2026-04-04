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

ll c[500005];
ll n,k,a[500005];

void upd(ll x,ll w){
	while(x<=n){
		c[x]+=w;
		x+=(x&-x);
	}
}
ll qry(ll x){
	ll ret=0;
	while(x){
		ret+=c[x];
		x-=(x&-x);
	}
	return ret;
}
void procedure(){
	n=read(),k=read();
	for(ll i=1;i<=n;i++)a[i]=read();	

	ll mn=n+1,mx=0,cur=0,ans=0;
	for(ll l=1;l<=n;l++){
		while(mx<n && cur+qry(n)-qry(a[mx+1])<=k){
			cur+=qry(n)-qry(a[++mx]);
			upd(a[mx],1);
			// cout<<l<<" "<<mx<<" cur="<<cur<<endl;
			if(cur==k) mn=min(mn,mx);
		}
		ans+=max(0ll,mx-mn+1);
		// cout<<"l="<<l<<" mn="<<mn<<" mx="<<mx<<endl;

		if(qry(a[l]-1)){
			cur-=qry(a[l]-1);
			mn=n+1;
		}else mn=max(mn,l+1);
		upd(a[l],-1);
		// cout<<l+1<<" "<<mx<<" cur="<<cur<<endl;
	}
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}