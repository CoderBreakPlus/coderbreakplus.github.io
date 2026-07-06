// created time: 2026-07-02 08:18:12
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

ll n,v[200005],c[200005],x[200005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)v[i]=read();
	for(int i=1;i<=n;i++)c[i]=read();
	for(int i=1;i<n;i++)x[i]=read();

	int ans=0;
	multiset<pair<ll,ll>>S;
	for(int i=1;i<=n;i++){
		while(!S.empty()&&S.begin()->fi<v[i]){
			ans=(ans+(ll)(2*mod-S.begin()->fi)*((S.begin()->se)%mod))%mod;
			c[i]+=S.begin()->se;
			S.erase(S.begin());
		}
		ans=(ans+(ll)v[i]*(c[i]%mod))%mod; S.emplace(v[i],c[i]);
		if(i==n)break;

		if(x[i]==1)continue;
		multiset<pair<ll,ll>>T;
		while(!S.empty()){
			int t=0; ll sum=0;
			while(t<x[i]&&!S.empty()){
				auto [V,C]=*S.begin();S.erase(S.begin());

				if(t+C<=x[i]){
					sum+=V*C;
					t+=C;
				}else{
					ll d=x[i]-t;
					sum+=V*d,t+=d; C-=d;

					if(C>x[i]){
						if(V*x[i]<=1e9)T.emplace(V*x[i],C/x[i]);
						C%=x[i];
					}
					if(C)S.emplace(V,C);
				}
			}
			if(sum>1e9||t<x[i])break;
			T.emplace(sum,1);
		}
		swap(S,T);
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	read();
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}