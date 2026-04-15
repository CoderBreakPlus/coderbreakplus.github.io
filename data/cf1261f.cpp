// created time: 2026-04-15 07:40:30
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
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

int n,m;
vector<pair<ll,ll>>A,B;

void update(ll l,ll r,ll ql,ll qr,vector<pair<ll,ll>>&A){
	if(ql>=qr)return;
	if(r<=ql||qr<=l)return;
	if(ql<=l&&r<=qr){
		A.pb(l,lg2(r-l));
		return;
	}
	ll mid=(l+r)>>1;
	update(l,mid,ql,qr,A),update(mid,r,ql,qr,A);
}
pair<ll,ll> seq[10000005]; int tp;
int stk[10000005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		ll l=read(),r=read();
		A.pb(l,0), A.pb(r,0);
		update(0,(1ll<<60),l+1,r,A);
	}
	m=read();
	for(int i=1;i<=m;i++){
		ll l=read(),r=read();
		B.pb(l,0), B.pb(r,0);
		update(0,(1ll<<60),l+1,r,B);
	}
	ll ans=0;
	for(auto [a,p]: A) for(auto [b,q]: B){
		if(p&&q&&p!=q)continue;
		ll bs = max(p,q);
		ll L = ((a^b)>>bs<<bs);
		seq[++tp] = {L, L+(1ll<<bs)};
	}

	sort(seq+1,seq+tp+1,[](pair<ll,ll> A,pair<ll,ll> B){
		return A.fi==B.fi?A.se>B.se:A.fi<B.fi;
	});
	for(int i=tp;i>=1;i--){
		auto [L,R]=seq[i];
		while(tp && R>=seq[stk[tp]].se) tp--;
		stk[++tp]=i;
	}

	for(int i=1;i<=tp;i++){
		auto [L,R]=seq[stk[i]];
		ans=(ans+(L+R-1)%mod*((R-L)%mod))%mod;
	}
	printf("%lld\n",ans*((mod+1)/2)%mod);
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