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
inline void addmod(int &x){ x=min<unsigned>(x,x-mod); }
inline void decmod(int &x){ x=min<unsigned>(x,x+mod); }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }
const int N=35;
int n;
char s[3005];

namespace sol{
	int sum, lst, fib[N+5];
	vector<pair<int,int>>vec,vec2;

	set<int>S;
	int get(int x){
		for(int i=N;i>=2;i--)
			if(x>fib[i]) x-=fib[i];
		return x==1;
	}
	void init(){
		fib[0]=fib[1]=1;
		for(int i=2;i<=N;i++) fib[i]=fib[i-1]+fib[i-2],S.emplace(fib[i]);
		sum=0,lst=1;

		// for(int i=1;i<=13;i++) cout<<get(i)<<" "; cout<<endl;
	}

	void ins(char ch){
		vec2.clear();
		for(auto [x,y]: vec){
			x++;
			if(ch-'0'==get(x)) vec2.pb(x,y);
		}
		swap(vec,vec2);

		int dp=sum;
		for(auto [x,y]: vec){
			// cout<<"reduce "<<x<<endl;
			if(S.count(x)) decmod(dp-=y);
		}
		if(ch=='1') vec.pb(1,lst);

		// cout<<"insert "<<ch<<" dp = "<<dp<<endl;
		addmod(sum+=lst); lst=dp;
		// cout<<"sum = "<<sum<<endl;


		// cout<<endl;
	}
}
void procedure(){
	sol::init();
	n=read();
	while(n--){
		scanf("%s",s); int x=strlen(s);
		for(int i=0;i<x;i++) sol::ins(s[i]);

		printf("%d\n",sol::lst);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif

	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}