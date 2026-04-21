// created time: 2026-04-21 15:35:54
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

int n;
ll x,y;
char s[100005];

bitset<100005>b[2][2];

void procedure(){
	n=read(),x=read(),y=read();

	scanf("%s",s+1);
	b[0][0].reset(),b[0][1].reset();
	b[0][0][0]=1;

	set<ll>S;

	for(int i=1,op=1;i<=n;i++,op^=1){
		b[op][0].reset(),b[op][1].reset();
		if(s[i]!='0'){
			for(auto o:{0,1})
				b[op][o] |= (b[op^1][o^1] << o); 
		}
		if(s[i]!='1'){
			for(auto o:{0,1})
				b[op][o] |= (b[op^1][o] << o);
		}
	}
	int o=n&1; b[o][0]|=b[o][1];
	for(int i=b[o][0]._Find_first(); i<=n; i=b[o][0]._Find_next(i)){
		ll c=(ll)(n-2*i)*(n-2*i+1)/2;
		S.emplace(c*x+i*y);
	}
	int ans=0;
	for(auto x:S) ans=(ans+x)%mod;
	printf("%d\n",ans);
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