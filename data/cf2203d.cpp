// created time: 2026-04-01 18:49:34
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

int n,m,f[2000005];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n+m;i++) f[i]=0;
	for(int i=1;i<=n;i++) f[read()]++;

	for(int i=n+m;i>=1;i--)
		for(int j=2*i;j<=n+m;j+=i) f[j]+=f[i];

	int c0=0,c1=0,c2=0;
	for(int i=1;i<=m;i++){
		int x=read();
		if(f[x]==n) c0++;
		else if(f[x]==0) c1++;
		else c2++;
	}

	// cout<<c0<<" "<<c1<<" "<<c2<<endl;

	for(int i=1;i<=m+1;i++){
		if(i&1){
			if(c2) c2--;
			else if(c0) c0--;
			else {puts("Bob");return;}
		}else{
			if(c2) c2--;
			else if(c1) c1--;
			else {puts("Alice");return;}
		}
	}
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