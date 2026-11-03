// created time: 2026-10-29 18:30:09
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
inline ll INV(ll x){ assert(x);return qpow(x, mod-2); }

int n,m,S,v,a,p[400005],sz[3][2];
int A[2];
int calc(int x){
	return (qpow(A[0],sz[x][0])*qpow(A[1],sz[x][1])+qpow(A[1],sz[x][0])*qpow(A[0],sz[x][1]))%mod;
}
int geosum(int a,int b,int k){
	if(a==b) return k*qpow(a,k-1)%mod;
	return (qpow(b,k)-qpow(a,k)+mod)*INV((b-a+mod)%mod)%mod;
}
void procedure(){
	n=read(),m=read(),v=read(),a=read();
	for(int i=1;i<=v;i++)addmod(p[i]=read()%mod+p[i-1]);
	S=p[v];
	ll iv=INV(S);

	int out=0;
	for(int x=1;x<=v;x++){
		A[0]=p[x-1],addmod(A[1]=S+mod-p[x-1]);
		A[0]=A[0]*iv%mod;
		A[1]=A[1]*iv%mod;

		sz[0][0]=1,sz[0][1]=0;
		sz[1][0]=0,sz[1][1]=1;
		int c=n,d=m,res=0;

		while(c && d){
			int k=min(c,d);
			sz[2][0]=sz[0][0]+sz[1][0];
			sz[2][1]=sz[0][1]+sz[1][1];

			int s0=sz[0][1]+sz[1][0];
			int s1=sz[0][0]+sz[1][1];
			ll w=qpow(A[0],s0)*qpow(A[1],s1)%mod;
			ll f=calc(0),g=calc(1),h=calc(2);

			res=(res+w*qpow(f,c-k)%mod*qpow(g,d-k)%mod*geosum(f*g%mod,h,k))%mod;

			if(c>=d){
				c-=d;
				sz[1][0]=sz[2][0];
				sz[1][1]=sz[2][1];
			}else{
				d-=c;
				sz[0][0]=sz[2][0];
				sz[0][1]=sz[2][1];
			}
		}

		if(a>=x)
			res=(res+qpow(calc(c?0:1),c+d))%mod;
		addmod(out+=res);
	}
	printf("%d\n",out);
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