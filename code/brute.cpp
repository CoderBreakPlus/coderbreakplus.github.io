// created time: 2026-06-15 10:08:44
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

int n,a[105],pos[105];
bool b[105],c[105];

int calc1(){
	memcpy(b,c,sizeof(b));
	bool ok=0;
	for(int i=1;i<n;i++)
		if(b[i]>b[i+1])ok=1;
	if(!ok)return 0;
	for(int k=1;;k++){
		if(k&1) sort(b+1,b+k+1);
		else sort(b+n-k+1,b+n+1);
		// for(int i=1;i<=n;i++)putchar('0'+b[i]);
		// puts("");
		ok=0;
		for(int i=1;i<n;i++)
			if(b[i]>b[i+1])ok=1;
		if(!ok) return k;
	}
}
int calc2(){
	memcpy(b,c,sizeof(b));
	bool ok=0;
	for(int i=1;i<n;i++)
		if(b[i]>b[i+1])ok=1;
	if(!ok)return 0;
	for(int k=1;;k++){
		if(~k&1) sort(b+1,b+k+1);
		else sort(b+n-k+1,b+n+1);
		// for(int i=1;i<=n;i++)putchar('0'+b[i]);
		// puts("");
		ok=0;
		for(int i=1;i<n;i++)
			if(b[i]>b[i+1])ok=1;
		if(!ok) return k;
	}
}
void procedure(){
	n=read();
	int ans1=0, ans2=0;
	for(int i=1;i<=n;i++)c[i]=0;
	for(int i=1;i<=n;i++)a[i]=read(),pos[a[i]]=i;
	for(int i=n;i>=1;i--){
		c[pos[i]]=1;
		chkmax(ans1, calc1());
		chkmax(ans2, calc2());
	}
	if(ans1 <= ans2)
		for(int i=1;i<=ans1;i++)putchar("SP"[i&1]);
	else
		for(int i=1;i<=ans2;i++)putchar("PS"[i&1]);

	puts(".");
}
int main(){
	ll T=1;
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
		T=read();
	#endif
	// math_init();
	while(T--) procedure();
	return 0;
}