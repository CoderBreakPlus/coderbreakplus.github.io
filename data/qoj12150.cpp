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
ll n,l[500005],r[500005];
set<tuple<ll,ll,ll>>s,t;

void del(ll l,ll r,ll i){
	s.erase({l,r,i});
	t.erase({r,l,i});
}
void add(ll l,ll r,ll i){
	s.emplace(l,r,i);
	t.emplace(r,l,i);
}
ll v[500005];

void procedure(){
	n=read();
	s.clear(), t.clear();
	for(ll i=1;i<=n;i++){
		v[i]=0;
		ll l=read(),r=read();
		s.emplace(l,r,i);
		t.emplace(r,l,i);

		::l[i]=l, ::r[i]=r;
	}	

	while(!s.empty()){
		auto lst = *s.rbegin();

		auto [a,b,c] = lst;
		del(a,b,c);

		if(t.empty() || (get<0>(*t.begin()))>a){
			add(a,b,c);
			break;
		}

		auto fst = *t.begin();
		auto [e,d,f] = fst;
		del(d,e,f);

		// cout<<"here "<<a<<"->"<<b<<" "<<d<<"->"<<e<<endl;
	}

	auto ss = s;

	while(!ss.empty() && s.size() >= 2){
		auto lst = *ss.begin(); ss.erase(lst);
		auto [l,r,i] = lst;
		del(l,r,i);
		auto [R,L,I] = *t.begin();
		// cout<<"find "<<R<<","<<L<<","<<I<<" in t"<<endl;
		if(R > r){
			add(l,r,i);
			continue;
		}
		v[i] = 1;
		del(L,R,I), ss.erase({L,R,I});

		// cout<<"pair "<<i<<" "<<I<<endl;

		// for(auto [l,r,i]: s) cout<<l<<","<<r<<","<<i<<" "; cout<<endl;
		// for(auto [l,r,i]: t) cout<<l<<","<<r<<","<<i<<" "; cout<<endl;
	}

	int op=0;
	for(auto [l,r,i]: s){
		v[i] = op;
		op^=1;
	}
	for(ll i=1;i<=n;i++) putchar(v[i]?'T':'N'); puts("");

	// for(ll i=0;i<=100;i++){
	// 	int cnt = 0;
	// 	for(ll j=1;j<=n;j++){
	// 		if(l[j] <= i && i < r[j]) cnt += v[j];
	// 		else cnt += !v[j];
	// 	}
	// 	assert(cnt >= (n-1)/2);
	// }
}
int main(){
	#ifdef LOCAL
		assert(freopen("input.txt","r",stdin));
		assert(freopen("output.txt","w",stdout));
	#endif
	ll T=read();
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}