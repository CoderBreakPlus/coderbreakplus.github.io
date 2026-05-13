// created time: 2026-05-13 10:44:13
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
ll n,k;
struct sol{
	ll op[200005],x[200005],c[200005],m,id[200005];
	ll ans[200005];

	void ins(ll OP,ll X,ll C){
		op[++m]=OP, x[m]=X, c[m]=C;
	}
	ll f[505][505],g[505][505];
	ll getans(ll k){
		return ans[k];
	}
	void init(){
		for(ll i=1;i<=m;i++)id[i]=i;

		sort(id+1,id+m+1,[&](ll i,ll j){
			return x[i]==x[j]?op[i]>op[j]:x[i]<x[j];
		}); 
		memset(f,0x3f,sizeof(f));memset(g,0x3f,sizeof(g));
		f[0][0]=0;
		for(ll I=1;I<=m;I++){
			ll i=id[I];
			memcpy(g,f,sizeof(g));
			if(op[i]&1){
				for(ll j=0;j<=m;j++)for(ll k=0;k<=j;k++)
					chkmin(g[j+1][k+1], f[j][k]+c[i]);
			}else{
				for(ll j=0;j<=m;j++)for(ll k=1;k<=j;k++)
					chkmin(g[j][k-1], f[j][k]+c[i]);
			}
			memcpy(f,g,sizeof(f));
		}
		for(ll j=0;j<=n;j++)ans[j]=f[j][0];
		for(int j=1;j<=n;j++)
			if(ans[j]<1e17)assert(ans[j]-ans[j-1]>=ans[j-1]-ans[j-2]);
	}
}S[2];
void procedure(){
	n=read(),k=read();
	for(ll i=1;i<=n;i++){
		ll t=read()-1,x=read(),y=read(),c=read();
		S[t>>1].ins(t,(t>>1)?y:x,c);
	}
	S[0].init();
	S[1].init();

	ll ans=1e18;
	for(ll i=0;i<=k;i++)
		ans=min(ans, S[0].getans(i)+S[1].getans(k-i));
	if(ans<1e17) printf("%lld\n",(ll)ans);
	else puts("-1");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}