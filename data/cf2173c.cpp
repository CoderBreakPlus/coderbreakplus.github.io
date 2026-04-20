// created time: 2026-04-19 18:58:06
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

int n,k,a[200005];
set<int>S,T;
void procedure(){	
	n=read(),k=read();S.clear();
	for(int i=1;i<=n;i++)a[i]=read(),S.emplace(a[i]);
	T=S;

	vector<int>vec;
	while(!S.empty()){
		int x=*S.begin();vec.pb(x);
		for(int v=x;v<=k;v+=x){
			if(!T.count(v)){puts("-1");return;}
			if(S.count(v))S.erase(v);
		}
	}
	printf("%d\n",(int)vec.size());
	for(auto x:vec)printf("%d ",x);puts("");
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