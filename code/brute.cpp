// created time: 2026-10-21 09:11:50
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

int n,m,x[200005],a[200005],b[200005],seq[200005],ord[200005];


int ans[200005],buc[200005];
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		x[i]=read(),a[i]=read(),b[i]=read();
	}
	int q=read();
	while(q--){
		int l=read(),r=read();
		for(int j=1;j<=n;j++)buc[j]=1;

		bool flg=1;
		for(int i=l;i<=r;i++){
			if(!x[i])
				for(int j=a[i];j<=b[i];j++)buc[j]=0;
		}
		for(int i=l;i<=r;i++)if(x[i]){
			bool ok=0;
				for(int j=a[i];j<=b[i];j++)ok|=buc[j];
			flg&=ok;
		}
		puts(flg?"YES":"NO");
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}