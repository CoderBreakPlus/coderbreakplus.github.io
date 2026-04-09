// created time: 2026-04-09 07:49:09
// https://qoj.ac/contest/1924/problem/10116
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

int N;string s;
map<string,pair<vector<string>,vector<string>>>mp;

void procedure(){
	cin>>N;
	for(int i=1;i<=N;i++){
		cin>>s;
		mp[s.substr(0,4)].fi.push_back(s);
	}
	for(int i=1;i<=N;i++){
		cin>>s;
		mp[s.substr(0,4)].se.push_back(s);
	}
	for(auto [x,p]:mp){
		auto [a,b]=p;
		if(a.size()!=b.size()){
			cout<<"NO\n";
			return;
		}
	}
	cout<<"YES\n";
	for(auto [x,p]:mp){
		auto [a,b]=p;
		for(int i=0;i<a.size();i++) cout<<a[i]<<" "<<b[i]<<endl;
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ios::sync_with_stdio(0);cin.tie(0);
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}