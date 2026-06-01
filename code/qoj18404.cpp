// created time: 2026-06-01 18:28:55
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e6+3;
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
int n,k,f[10],g[10],h[10],d[10];
char s[10];

void procedure(){
	scanf("%s",s);
	n=read(),k=read();
	if(s[0]=='f'){
		f[0]=1;
		for(int i=1;i<=n+k;i++){
			int x=read();
			for(int j=k-1;j>=0;j--)
				f[j]=((j?f[j-1]:0)+(ull)f[j]*(mod-x))%mod;
		}
		for(int j=0;j<k;j++) printf("%d ",f[j]);puts("");
	}else{
		for(int i=0;i<k;i++) h[i]=read();
		f[0]=1;
		for(int i=1;i<=n;i++){
			int x=read();
			for(int j=k-1;j>=0;j--)
				f[j]=((j?f[j-1]:0)+(ull)f[j]*(mod-x))%mod;
		}
		int iv=INV(f[0]);
		g[0]=(ull)iv*h[0]%mod;
		for(int i=1;i<k;i++){
			g[i]=h[i];
			for(int j=0;j<i;j++)
				g[i]=(g[i]+(ull)(mod-g[j])*f[i-j])%mod;
			g[i]=(ull)g[i]*iv%mod;
		}
		memset(f,0,sizeof(f));
		for(int i=1;i<=(1<<20);i++){
			int ans=1;
			for(int x=k-1;x>=0;x--)
				ans=((ull)ans*i+g[x])%mod;
			if(!ans) printf("%d ",i);
		}
		puts("");
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	while(T--) procedure();
	return 0;
}