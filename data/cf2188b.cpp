// created time: 2026-04-21 14:08:06
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

int n;char s[200005];

void procedure(){
	n=read();	
	scanf("%s",s+1);
	s[n+1]='1';
	int lst=0,ans=0;

	int cnt=0;
	for(int i=1;i<=n;i++) cnt+=(s[i]=='1');

	if(!cnt){
		printf("%d\n",(n-1)/3+1);
		return;
	}
	for(int i=1;i<=n+1;i++){
		if(s[i]=='1'){
			ans+=(i<=n);
			if(!lst || i==n+1) ans+=(i-lst)/3;
			else ans+=(i-lst-1)/3;
			lst=i;
		}
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