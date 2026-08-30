// created time: 2026-08-30 16:29:08
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

const int B = 3333;
int n,a[B+5];
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

bool calc(int x,int cur){
	for(int i=1;i<=B;i++)
		if(a[i]==x) {
			n=cur-i;
			return 1;
		}
	return 0;
}
void procedure(){
	int m = 0;
	for(int i=1;i<=B;i++){
		cout<<"walk "<<rng(1,1e9)<<endl;
		int x; cin>>x;
		chkmax(m,x);
	}

	for(int i=1;i<=B;i++){
		cout<<"walk 1"<<endl;
		cin>>a[i];
		for(int j=1;j<i;j++){
			if(a[j]==a[i]){
				cout<<"guess "<<i-j<<endl;
				return;
			}
		}
	}

	cout<<"walk "<<m-B<<endl;
	int x,cur=m;cin>>x;

	while(!calc(x,cur)) cout<<"walk "<<B<<endl,cin>>x,cur+=B;
	cout<<"guess "<<n<<endl;
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