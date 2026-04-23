// created time: 2026-04-18 09:12:43
// https://qoj.ac/contest/3588/problem/17756
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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

ll n,a[200005];
ll op[200005],x[200005];
char s[5];
multiset<ll>S0;
multiset<ll,greater<ll>>S1;

void procedure(){
	n=read();
	ll t0=0;
	S0.clear();S1.clear();

	for(ll i=1;i<=n;i++){
		scanf("%s",s);
		if(s[0]=='W') op[i]=1;
		else op[i]=0, x[i]=read();
	}
	op[n+1]=1;
	ll lst=0, cur=0;

	// S0: 前面的前 cur 大
	// S1: 比较小的

	ll ans=0;
	for(ll i=1;i<=n+1;i++){
		if(op[i]==1){
			ll sb=i-lst;

			ll res=cur-S0.size();

			vector<ll>vec;
			for(ll j=lst+1;j<i;j++){
				vec.pb((ll)x[j]*(i-j));
			}
			sort(vec.begin(),vec.end());

			ll now=t0*sb;
			auto it = S0.begin();

			while(res-- && vec.size()) {
				now += vec.back();
				vec.pop_back();
			}
			while(it != S0.end() && vec.size() && (*it)*sb <= vec.back()){
				now -= (*it)*sb;
				now += vec.back();
				it = next(it);
				vec.pop_back();
			}

			// cout<<"from "<<lst<<" to "<<i-1<<endl;
			// cout<<"now = "<<now<<endl;

			ans += now;

			for(ll j=lst+1;j<i;j++){
				if(S0.size()&&x[j]<*S0.begin()) S1.emplace(x[j]);
				else S0.emplace(x[j]),t0+=x[j];
			}

			cur++;
			while(S0.size()<cur && S1.size()){
				ll it = *S1.begin();
				S1.erase(S1.begin()),S0.emplace(it),t0+=it;
			}

			while(S0.size()>cur){
				ll it = *S0.begin();
				S0.erase(S0.begin()),S1.emplace(it),t0-=it;
			}

			lst = i;
		}
	}
	printf("%lld\n",ans);
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