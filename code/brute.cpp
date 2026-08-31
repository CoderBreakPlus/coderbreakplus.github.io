// created time: 2026-08-31 13:49:52
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
const int M=2e5;
#define mid ((l+r)>>1)
int n,a[100005],b[100005],c[100005],d[100005];

bool solve(vector<int> s){
	if(s.size() == 1) return 1;

	{
		sort(s.begin(),s.end(),[](int x,int y){ return a[x]<=a[y]; });
		int mx=0;
		for(int i=0; i+1<s.size(); i++){
			chkmax(mx, c[s[i]]);
			if(mx <= a[s[i+1]]) {
				return solve(vector<int>(s.begin(), s.begin()+i+1))
					&& solve(vector<int>(s.begin()+i+1, s.end()));
			}
		}
	}
	{
		sort(s.begin(),s.end(),[](int x,int y){ return b[x]<=b[y]; });
		int mx=0;
		for(int i=0; i+1<s.size(); i++){
			chkmax(mx, d[s[i]]);
			if(mx <= b[s[i+1]]) {
				return solve(vector<int>(s.begin(), s.begin()+i+1))
					&& solve(vector<int>(s.begin()+i+1, s.end()));
			}
		}
	}
	return 0;
}
void procedure(){
	n=read();
	vector<int>vec;
	for(int i=1;i<=n;i++){
		a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
		vec.pb(i);
	}
	puts(solve(vec)?"YES":"NO");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}