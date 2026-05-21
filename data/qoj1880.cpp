// created time: 2026-05-21 07:57:56
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

ll n,a[200005],b[200005],x[200005];
ll tmp[400005],cnt,qz[400005];

ll stk[400005],tp;
bool check(ll i,ll j,ll k){
	return (__int128)(qz[j]-qz[i])*(tmp[k]-tmp[j])<=(__int128)(qz[k]-qz[j])*(tmp[j]-tmp[i]);
}
ll calc(ll i,ll v){
	return qz[i]-2*v*tmp[i];
}
void procedure(){
	n=read();
	for(ll i=1;i<=n;i++){
		a[i]=read(),b[i]=read(),x[i]=read();
		tmp[++cnt]=a[i],tmp[++cnt]=b[i];
	}	
	tmp[0]=1;
	sort(tmp+1,tmp+cnt+1);
	cnt=unique(tmp+1,tmp+cnt+1)-(tmp+1);

	ll out=0,ans=-9e18;
	for(ll i=1;i<=n;i++){
		a[i]=lower_bound(tmp+1,tmp+cnt+1,a[i])-tmp,
		b[i]=lower_bound(tmp+1,tmp+cnt+1,b[i])-tmp;
		out-=2*x[i];
		qz[a[i]]+=x[i],qz[b[i]]+=x[i];
	}

	for(ll i=1;i<=cnt;i++)qz[i]+=qz[i-1];
	for(ll i=0;i<=cnt;i++){
		while(tp>=2 && check(stk[tp-1],stk[tp],i)) tp--;
		stk[++tp]=i;
	}

	for(ll i=0;i<=cnt;i++){
		while(tp>=2 && calc(stk[tp-1],tmp[i]) > calc(stk[tp],tmp[i])) tp--;
		chkmax(ans, calc(stk[tp],tmp[i])+qz[i]);
	}
	printf("%.1lf\n", (ans+out)/2.0);
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