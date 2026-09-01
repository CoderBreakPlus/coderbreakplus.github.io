// created time: 2026-09-01 18:52:48
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

int n,buc[500005],a[500005];

set<int>S;

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)buc[read()]++,S.emplace(i);

	auto it = S.end();

	for(int i=n;i>=0;i--){
		if(!buc[i]) {
			if(it == S.begin()){
				puts("No");
				return;
			}
			--it;
			continue;
		}
		// cout<<"solving "<<i<<endl;
		while(buc[i]--){
			if(it==S.end()){
				puts("No");
				return;
			}
			int x = *it; a[x]=i;
			// cout<<"pos "<<x<<" with "<<i<<endl;
			S.erase(it);
			it=S.lower_bound(x);
		}
		if(i)
		--it;
	}
	puts("Yes");
	for(int i=1;i<=n;i++) printf("%d ",a[i]);
	puts("");
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