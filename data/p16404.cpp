// created time: 2026-05-01
// https://www.luogu.com.cn/problem/P16404
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
const int T=8;
int dp[106][401][401][T+1];

int n,a,b,c,d;
void procedure(){
	n=read(),a=read(),b=read(),d=read(),c=read();
	// cout<<"n="<<n<<endl;
	int t=0;
	for(int i=0;i<=c;i++){
		t=max(t,dp[n][a][b][i]+(c-i)*5);
	}
	__int128 m=t;
	while(d--)m=m+m/5;
	vector<char>ch;while(m)ch.pb(m%10+'0'),m/=10;
	reverse(ch.begin(),ch.end());
	for(auto x:ch)putchar(x);puts("");
}
int go1(int x){return 10*sqrt(x);}
int go2(int x){return 0.7*x+30;}

int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif

	for(int j=0;j<=400;j++)for(int k=0;k<=400;k++)for(int l=0;l<=T;l++){
		for(int i=0;i<=100;i++){
			dp[i][j][k][l]=-1e9;
			if(!j&&!k&&!l) dp[i][j][k][l]=i;
			if(j)dp[i][j][k][l]=max(dp[i][j][k][l],dp[go1(i)][j-1][k][l]);
			if(k)dp[i][j][k][l]=max(dp[i][j][k][l],dp[go2(i)][j][k-1][l]);
			if(l)dp[i][j][k][l]=max(dp[i][j][k][l],dp[i+5][j][k][l-1]);
		}
	}
	// cout<<go1(go1(10))<<endl;
	// cout<<go1(go2(go1(50)))<<endl;
	// cout<<go1(go1(go2(50)))<<endl;
	ll T=read();
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}