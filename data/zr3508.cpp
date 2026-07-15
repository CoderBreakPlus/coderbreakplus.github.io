// created time: 2026-07-15 09:08:06
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
const ll LOW = 1e18;
int c,o,n,m,lst;
void solve(int m,basic_string<array<int,2>> &a,basic_string<ll> b){
	basic_string<int>seq(a.size(),0);
	for(int i=0;i<a.size();i++)seq[i]=a[i][1];

	nth_element(seq.begin(), seq.begin()+m-1, seq.end());
	int cut=seq[m-1];
	stable_partition(a.begin(),a.end(),[&](auto w){ return w[1]<=cut; });

	auto L=a.substr(0,m), R=a.substr(m);

	int tp=0,it=1,sz=b.size();
	for(auto [x,y]: R){
		while(it<sz&&b[tp]<-x) b[++tp]=b[it++];
		if(b[tp]>=-x) b[tp-1]+=b[tp]+x;
		tp--;
	}	
	while(it<sz) b[++tp]=b[it++];
	b.erase(tp+1);

	a=L;
	if(m==1){
		int x=read()^(o*lst),y=read()^(o*lst);
		if(a[0][1]<y) a[0]={x,y};
		if(b[1]>=-a[0][0]) b[0]+=b[1]+a[0][0];
		ll ans;
		printf("%lld\n", ans=b[0]+LOW);
		lst=ans%(1<<30);
	}else{
		solve((m+1)/2,a,b),solve(m/2,a,b);
	}
	a=a+R;
	inplace_merge(a.begin(),a.begin()+m,a.end(),greater<>());
}
void procedure(){
	c=read(),o=read();
	n=read(),m=read();
	basic_string<array<int,2>>a(n,{0,0});
	basic_string<ll>b(n,0);

	for(int i=0;i<n;i++) a[i][0]=read();
	for(int i=0;i<n;i++) a[i][1]=read();
	for(int i=0;i<n;i++) b[i]=-read();
	sort(b.begin(),b.end());
	sort(a.begin(),a.end(),greater<>());

	ll ans=0,cur=0;
	for(int i=0;i<n;i++){
		cur+=a[i][0]+b[i];
		chkmax(ans,cur);
	}
	printf("%lld\n", ans); lst=ans%(1<<30);
	b=-LOW+b;
	solve(m,a,b);
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