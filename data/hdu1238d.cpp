// created time: 2026-08-20 12:52:38
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

const int N=1e5;
int n,m,a[100005],l[100005],r[100005],k[100005];
ll ww[100005],ans[100005];

int buc[200005];
vector<int>fac[100005],qry[100005];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read(),qry[i].clear();
	memset(buc,0,sizeof(buc));
	for(int i=1;i<=m;i++){
		ans[i]=0;
		l[i]=read(),r[i]=read(),k[i]=read();
		qry[l[i]-1].pb(-i),qry[r[i]].pb(i);
	}
	for(int i=1;i<=n;i++){
		for(int j:fac[a[i]]) buc[j]++;
		for(int j:qry[i]){
			ll cf=1,tot=0;
			if(j<0)j=-j,cf=-1;
			for(int w:fac[k[j]])
				tot+=buc[w]*ww[w];
			ans[j]+=cf*tot;
		}
	}
	for(int i=1;i<=m;i++)
		printf("%lld\n",ans[i]);
}
void dft(ll *a){
	for(int i=N;i>=1;i--)
		for(int j=2*i;j<=N;j+=i)a[j]+=a[i];
}
void idft(ll *a){
	for(int i=1;i<=N;i++)
		for(int j=2*i;j<=N;j+=i)a[j]-=a[i];
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	for(int i=1;i<=N;i++)
		for(int j=i;j<=2*N;j+=i) fac[j].pb(i);
	for(int i=1;i<=N;i++) ww[i]=(ll)i*i;
	idft(ww);

	// for(int i=1;i<=12;i++) cout<<ww[i]<<" "; cout<<endl;
	
	// math_init();
	while(T--) procedure();
	return 0;
}