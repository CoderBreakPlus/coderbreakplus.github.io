// created time: 2026-04-15 15:43:43
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

ll n,f[3005],g[3005]={0,1,0,1,0,1,0,1,0};


ll query(ll l,ll r){
	if(l>r)return 0;
	assert((l^r)&1);
	cout<<"? "<<l<<" "<<r<<endl;

	ll x;
	#ifndef LOCAL
		if(!(cin>>x)) exit(0);
	#endif

	#ifdef LOCAL
		ll cnt=0;
		for(ll i=l;i<=r;i++)cnt+=g[i];
		x=(r-l+1)/__gcd(r-l+1,cnt);
	#endif
	return ((r-l+1)/x)&1;
}
void procedure(){
	cin>>n;
	for(ll i=1;i<=n;i++)
		f[i]=0;

	ll tot;
	if(n&1){
		ll s1=query(1,n-1), s2=query(2,n);
		f[n]=(s1^s2);

		tot=s1;
	}else{
		ll s1=query(1,n), s2=query(2,n-1);
		f[n]=(s1^s2);



		tot=s2;
	}

	// cout<<"tot="<<tot<<endl;

	for(ll i=2;i<n;i++){
		if(2*i>n){
			ll val=((i&1)?query(2,i):query(1,i));
			for(ll j=1;j<i;j++)val^=f[j];
			f[i]=val;
		}else{
			ll val=(((i^n)&1)?(query(i+1,n-1)):(query(i+1,n)^f[n]));
			f[i]=tot^val;
		}
		tot^=f[i];
	}

	cout<<"! "; for(int i=1;i<=n;i++)cout<<f[i]; cout<<endl;
	ll x; if(!(cin>>x)) exit(0); if(x) return;

	cout<<"! "; for(int i=1;i<=n;i++)cout<<(f[i]^1); cout<<endl;
	if(!(cin>>x)) exit(0); if(x) return;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;cin>>T;
	// math_init();
	while(T--) procedure();
	return 0;
}