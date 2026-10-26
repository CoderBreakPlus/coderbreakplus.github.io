// created time: 2026-10-26 15:49:12
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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
const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}
const int B = 100, K = 150;

int n,q,a[10005],l[10005],r[10005],buc[10005],ord[10005];
int ans[10005];
int s[10005],t[10005],h[10005],u[10005],v[10005],cnt[10005];

void upd(int &a,ull b){ a=(a+b)%mod; }
int eval(int *f,int x){
	int ret=0;
	for(int i=K;i>=0;i--)ret=((ull)ret*x+f[i])%mod;
	return ret;
}
void divide(int *f,int *g,int c){
	int r=f[K];
	for(int i=K-1;i>=0;i--){
		int v=f[i]; g[i]=r;
		r=(v+(ull)c*r)%mod;
	}
}
void multiply(int *f,int c){
	for(int i=K;i>=1;i--)
		f[i]=(f[i-1]+(ull)(mod-c)*f[i])%mod;
	f[0]=(ull)f[0]*(mod-c)%mod;
}
void ins(int i,int c){
	int x=buc[i],y=(buc[i]+=c);
	
	divide(s,u,x),divide(t,v,x);

	int g=0;
	for(int i=0;i<K;i++)
		g=(g+(u[i]+(ull)(mod-u[i+1])*(i+1)+mod-v[i])%mod*h[i])%mod;
	g=(ull)g*INV(eval(t,x))%mod;
	for(int i=0;i<K;i++){
		int tmp=h[i];
		upd(h[i],(ull)g*(mod-c));
		g=(tmp+(ull)x*g)%mod;
	}
	for(int i=0;i<=K;i++)addmod(t[i]+=mod-u[i]);
	if(!--cnt[x]&&x){
		for(int i=0;i<=K;i++)s[i]=u[i];
		divide(t,t,x);
	}
	if(!cnt[y]++&&y){
		multiply(t,y);
		for(int i=0;i<=K;i++)addmod(t[i]+=s[i]);
		multiply(s,y);
	}else{
		divide(s,u,y);
		for(int i=0;i<=K;i++)addmod(t[i]+=u[i]);
	}
}
void procedure(){
	n=read(),q=read();
	for(int i=0;i<n;i++)a[i]=read();
	for(int o=0;o<q;o++)
		l[o]=read(),r[o]=read()-1,ord[o]=o;
	sort(ord,ord+q,[](int x,int y){
		if(l[x]/B==l[y]/B) {
			if((l[x]/B)&1) return r[x]<r[y];
			else return r[x]>r[y];
		}else
			return l[x]<l[y];
	});
	int L=1,R=0;
	s[1]=1,t[0]=cnt[0]=n;
	h[0]=1;
	for(int i=1;i<=n;i++)h[0]=(ull)h[0]*i%mod;
	for(int i=1;i<K;i++)h[i]=(ull)h[i-1]*(n+i)%mod;
	for(int O=0;O<q;O++){
		int o=ord[O];
		while(L>l[o]) ins(a[--L],1);
		while(R<r[o]) ins(a[++R],1);
		while(L<l[o]) ins(a[L++],-1);
		while(R>r[o]) ins(a[R--],-1);
		ans[o]=h[0];
	}
	for(int o=0;o<q;o++)
		printf("%d\n",ans[o]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}