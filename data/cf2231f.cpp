// created time: 2026-06-04 16:25:56
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


int n,q;

int f1[200005],f2[200005];

bool check2(int a,int b){
	if(a>b)swap(a,b);
	return f2[b-a]<=max(a-1,n-b);
}
void procedure(){
	n=read(),q=read();
	for(int i=0;i<n;i++)f1[i]=0,f2[i]=1e9;
	int B=sqrt(n);
	for(int i=1;i<=B;i++){
		f1[i*i]=1;
		for(int j=1;i*i+j*j<n;j++)
			f2[i*i+j*j]=0;
		for(int j=1;j<i;j++)
			chkmin(f2[i*i-j*j],j*j);
	}


	while(q--){
		int a=read(),b=read();
		if(f1[b-a]){ puts("1"); continue; }
		if(check2(a,b)){ puts("2"); continue; }
		bool f3=0;
		for(int i=1;i*i<a;i++)
			if(check2(a-i*i,b)){ f3=1; break; }
		for(int i=1;a+i*i<=n;i++)
			if(check2(a+i*i,b)){ f3=1; break; }

		puts(f3?"3":"4");
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