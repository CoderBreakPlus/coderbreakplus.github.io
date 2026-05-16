// created time: 2026-05-16 09:12:16
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

ll n,r,a[500005],c[500005],dp[500005];

map<ll,ll>mp;

ll que[500005],hd,tl;
void procedure(){	
	n=read(),r=read();
	for(ll i=1;i<=n;i++)a[i]=(read()+a[i-1])%r;
	for(ll i=1;i<=n;i++)c[i]=read(); c[n+1]=0;

	mp.clear(); ll cnt=0;

	auto add = [&](ll x){ cnt += !(mp[x]++); };
	auto del = [&](ll x){ cnt -= !(--mp[x]); };
	
	bool flg=1;

	ll sb=1;
	hd=1,tl=0;
	
	for(ll i=1;i<=n+1;i++){
		dp[i]=flg?c[i]:1e18;

		while(cnt==r) del(a[sb++]);
		while(hd<=tl && que[hd]<sb) hd++;

		chkmin(dp[i], dp[que[hd]]+c[i]);

		while(hd<=tl && dp[que[tl]]>=dp[i])tl--;
		que[++tl]=i;

		flg&=(!!a[i]);
		add(a[i]);
	}

	printf("%lld\n",dp[n+1]);
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