// created time: 2026-06-11 19:05:48
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

int n,q,a[200005];
bool vis[200005];

void procedure(){
	n=read(),q=read();
	if(1ull*n*(n+1)/2>q){
		while(q--)putchar('0');
		return;
	}
	while(q--){
		int o=read(),l=read(),r=read();
		if(o==1){
			for(int i=l;i<=r;i++)
				if(i&1)a[i]--; else a[i]++;
		}else{
			for(int i=l;i<=r;i++)
				if(i&1)a[i]++; else a[i]--;
		}
		bool flg=1;
		for(int i=1;i<=n;i++){
			if(1<=a[i]&&a[i]<=n)vis[a[i]]=1;
		}
		for(int i=1;i<=n;i++)flg&=vis[i];
		putchar('0'+flg);
		for(int i=1;i<=n;i++)vis[i]=0;
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