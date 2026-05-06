// created time: 2026-05-05 12:39:21
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

int n,m,q,nxt[200005],f[20][200005];
pair<int,int>a[200005];

void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;i++)a[i].fi=read(),a[i].se=read();

	for(int i=1;i<=n;i++)nxt[i]=n+2; nxt[n+1]=nxt[n+2]=n+2;
	for(int i=1;i<=m;i++){
		nxt[a[i].fi]=min(nxt[a[i].fi],a[i].se+1);
	}
	for(int i=n;i>=1;i--)nxt[i]=min(nxt[i],nxt[i+1]);

	for(int i=1;i<=n+2;i++)f[0][i]=nxt[i];
	for(int i=1;i<=19;i++)for(int j=1;j<=n+2;j++)
		f[i][j]=f[i-1][f[i-1][j]];

	while(q--){
		int l=read(),r=read(),ans=0;
		for(int i=19;i>=0;i--)
			if(f[i][l]<=r+1)ans+=(1<<i),l=f[i][l];
		printf("%d\n",ans);
	}
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