// created time: 2026-05-29 11:32:25
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
char s[55];
int n;

void procedure(){
	n=read();
	scanf("%s",s);
	int ans=0;
	for(int i=0;i<(1<<n);i++){
		if(__builtin_parity(i))continue;
		int d=0,f=1;
		vector<char>vec;
		for(int j=0;j<n;j++)if((i>>j)&1){
			vec.pb(s[j]);
			if(s[j]=='(')d++;
			else d--;
			f&=(d>=0);
		}
		f&=(d==0);
		for(int i=1,j=(int)vec.size()-2;i<j;i++,j--){
			f&=(vec[i]==vec[j]);
		}
		if(f)chkmax(ans, __builtin_popcount(i));
	}	
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