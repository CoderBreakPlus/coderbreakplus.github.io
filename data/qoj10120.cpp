// created time: 2026-04-10 19:56:56
// https://qoj.ac/contest/1924/problem/10120
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

int n,k,d[1000005],nxt[1000005],f[21][1000005];
ll s[1000005];

bool check(ll x){
	int pt=1;
	for(int i=1;i<=2*n;i++){
		if(s[n]-d[i]<=x) return 1;
		while(pt+1<=2*n && s[pt]-s[i]+s[pt+1]-s[i-1]<=2*x) pt++;
		nxt[i]=pt+1;
	}
	nxt[2*n+1]=2*n+1;

	if(nxt[1]>=n+1) return 1;

	int i=1,x1=2,x2=n,cnt=0;
	// cout<<"at "<<i<<endl;
	while(i<n+1){
		int j=nxt[i];
		if(j-i<x2-x1){
			x1=i+1,x2=j;
		}
		i=j,cnt++;
	}
	if(cnt<=k) return 1;
	auto chk = [&](int i){
		int p=i; if(p>n) p-=n;
		int j=p,c=0;
		while(c<k && j<p+n) j=nxt[j],c++;
		return j>=p+n;
	};
	for(int i=x1;i<=x2;i++)
		if(chk(i)) return 1;
	return 0;
}
void procedure(){
	n=read(),k=read();
	ll l=0,r=0;
	for(int i=1;i<=n;i++){
		d[i]=d[i+n]=read();
		r+=d[i];
	}
	for(int i=1;i<=n;i++){
		l=max(l,min((ll)d[i],r-d[i]));
	}
	for(int i=1;i<=2*n;i++) s[i]=s[i-1]+d[i];
	// check(7);
	while(l<r){
		ll mid=(l+r)>>1;
		if(check(mid)){
			r=mid;
		}else l=mid+1;
	}
	printf("%lld\n",l);
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