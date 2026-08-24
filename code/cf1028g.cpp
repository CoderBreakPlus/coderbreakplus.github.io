// created time: 2026-08-24 09:08:52
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
const int N = 1e4;
ll dp[6][N+5];

void solve(int i,ll l,ll r){
	vector<ll>vec={l-1};

	int s=min(l,(ll)N);
	ll cur=l;
	cout<<s<<" ";
	for(int k=1;k<=s;k++){
		cur+=dp[i-1][min(cur,(ll)N)];
		cout<<cur<<" ";
		vec.pb(cur);
		cur++;
	}
	cout<<endl;
	vec.pb(r+1);

	int x;
	if(!(cin>>x)) exit(0);
	if(x==-1) return;

	solve(i-1,vec[x]+1,vec[x+1]-1);
}
void procedure(){
	for(int i=1;i<=5;i++){
		for(int j=1;j<=(i<5?N:1);j++){
			ll cur=j;
			for(int k=1;k<=j+1;k++)
				cur+=dp[i-1][min(cur,(ll)N)]+1;
			dp[i][j]=cur-j-1;
		}
	}
	solve(5,1,dp[5][1]);
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