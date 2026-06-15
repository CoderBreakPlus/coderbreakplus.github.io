// created time: 2026-06-15 09:00:41
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

int n,S,buc[800005],T;
vector<pair<int,int>>f[800005];

void ins(int v,int c){
	// cout<<"add "<<v<<" "<<c<<endl;
	for(int i=T;i>=v;i--){
		for(auto [l,r]: f[i-v]) f[i].pb(l+c,r+c);
		sort(f[i].begin(),f[i].end());
		vector<pair<int,int>>vec;
		for(auto [l,r]: f[i]){
			if(vec.empty() || vec.back().se < l){
				vec.pb(l,r);
			}else{
				vec[vec.size()-1] = mkp(vec.back().fi, max(vec.back().se,r));
			}
		}
		swap(f[i],vec);
	}
}
void procedure(){
	n=read(),S=read();
	for(int i=1;i<=n;i++){
		int x=read();
		buc[x]++,T+=max(x-1,1-x);
	}
	for(int i=0;i<=buc[0];i++)
		f[buc[0]-i].pb(i,i+buc[1]);

	for(int i=2;i<=S;i++){
		for(int k=0;(1<<k)<=buc[i];k++)
			ins((i-1)<<k, 1<<k), buc[i]-=(1<<k);
		if(buc[i]) ins((i-1)*buc[i], buc[i]);
	}

	ll ans=0;
	for(int i=0;i<=T;i++)
		for(auto [l,r]: f[i]) ans+=(r-l+1);
	printf("%lld\n",ans);
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