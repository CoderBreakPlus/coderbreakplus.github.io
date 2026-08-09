// created time: 2026-08-09
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e8+7;
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
const int pw[9]={1,6,6*6,6*6*6,6*6*6*6,6*6*6*6*6,6*6*6*6*6*6,6*6*6*6*6*6*6,6*6*6*6*6*6*6*6};
const int N=8;
const int i2 = INV(2);
int n,a[6*6*6*6*6*6*6*6],b[6*6*6*6*6*6*6*6];

void fwt(int *a){
	for(int m=0;m<n;m++)
		for(int x=0;x<pw[n];x+=pw[m+1])for(int y=x;y<x+pw[m];y++){
			auto f = [&](int w){ return y+w*pw[m]; };

			auto [a0,a1,a2,a3,a4,a5]=(tuple<int,int,int,int,int,int>)
				{a[f(0)],a[f(1)],a[f(2)],a[f(3)],a[f(4)],a[f(5)]};
			a[f(0)]=(a0+a1+a2+a3+a4+a5)%mod;
			a[f(1)]=(a1+a5)%mod;
			a[f(2)]=(a1-a5+mod)%mod;
			a[f(3)]=(a1+a3+a5)%mod;
			a[f(4)]=(a1+a4+a2+a5)%mod;	
			a[f(5)]=(a1+a4-a2-a5+2*mod)%mod;
		}
}
void ifwt(int *a){
	for(int m=0;m<n;m++)
		for(int x=0;x<pw[n];x+=pw[m+1])for(int y=x;y<x+pw[m];y++){
			auto f = [&](int w){ return y+w*pw[m]; };

			auto [a0,a1,a2,a3,a4,a5]=(tuple<int,int,int,int,int,int>)
				{a[f(0)],a[f(1)],a[f(2)],a[f(3)],a[f(4)],a[f(5)]};

			a[f(1)]=(ull)(a1+a2)*i2%mod;
			a[f(5)]=(ull)(a1-a2+mod)*i2%mod;
			
			a[f(3)]=(a3-a[f(1)]-a[f(5)]+2*mod)%mod;

			a[f(4)]=((ull)(a4+a5)*i2-a[f(1)]+mod)%mod;	
			a[f(2)]=((ull)(a4-a5+mod)*i2-a[f(5)]+mod)%mod;

			a[f(0)]=(a0-a[f(1)]-a[f(2)]-a[f(3)]-a[f(4)]-a[f(5)]+5*mod)%mod;
		}
}
void procedure(){
	n=read();
	for(int i=0;i<pw[n];i++) a[i]=read();
	for(int i=0;i<pw[n];i++) b[i]=read();

	fwt(a),fwt(b);
	for(int i=0;i<pw[n];i++) a[i]=(ull)a[i]*b[i]%mod;
	ifwt(a);

	for(int i=0;i<pw[n];i++) printf("%d ",a[i]); puts("");
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