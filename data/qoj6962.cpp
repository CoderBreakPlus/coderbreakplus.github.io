// created time: 2026-08-03
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

ll n,c,x[100005];
ll s0,s1;
vector<ll>vec[500005];

tuple<ll,ll,ll> seq[8000005]; ll tl;

void procedure(){
	n=read(),c=read();
	s0=0,s1=0;
	for(ll i=1;i<=c;i++)vec[i]={0};
	for(ll i=1;i<=n;i++){
		x[i]=2*read();
		ll t=read();while(t--)vec[read()].pb(x[i]);
	}
	tl=0;
	for(ll i=1;i<=c;i++){
		vec[i].pb(2e9);
		sort(vec[i].begin(),vec[i].end());
		ll bef=tl;
		for(int x=0;x+1<vec[i].size();x++){

			if(x && x+2<vec[i].size()){
				seq[++tl]={vec[i][x],-vec[i][x],1};
				ll mid=(vec[i][x]+vec[i][x+1])/2;
				seq[++tl]={mid,vec[i][x]+vec[i][x+1],-2};
				seq[++tl]={vec[i][x+1],-vec[i][x+1],1};
			}else if(!x){
				seq[++tl]={vec[i][x],vec[i][x+1],-1};
				seq[++tl]={vec[i][x+1],-vec[i][x+1],1};
			}else{
				seq[++tl]={vec[i][x],-vec[i][x],1};
			}
		}
		// cout<<"c = "<<i<<endl;
		// for(ll i=bef+1;i<=tl;i++) {
		// 	auto [x,y,z]=seq[i];
		// 	cout<<x<<" "<<y<<" "<<z<<endl;
		// }
	}
	sort(seq+1,seq+tl+1);

	ll mn=1e18;
	get<0>(seq[tl+1])=-114514;
	for(int i=1;i<=tl;i++){
		auto [a,b,c]=seq[i];
		// cout<<"add "<<a<<" "<<b<<" "<<c<<endl;
		s0+=b,s1+=c;
		if(a!=get<0>(seq[i+1])){
			// cout<<"here "<<s0<<" + "<<s1<<" * "<<a<<endl;
			chkmin(mn,s0+s1*a);
		}
	}
	printf("%lld\n",mn/2);
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