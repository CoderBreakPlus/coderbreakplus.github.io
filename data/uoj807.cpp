// created time: 2026-06-03
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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

const int inf = 0x3f3f3f3f;
const ll inf64 = 0x3f3f3f3f3f3f3f3fll;
const int kN = 205000, B = 400, kB = B + 5;
const ull HI = 0xffffffff00000000ull, LO = 0x00000000ffffffffull;

int n,m,q,a[kN],b[kN],rk[kN];
int nxt[kN],ptr[kN],ord[kB],trans[kN]; 
ull ans[kN],res[kN],re[kN],f[kB][kB],g[kN],c[kB];

inline void update(int x,ull y){
	for(;x<kB;x+=x&-x) chkmin(c[x],y);
}
inline ull query(int x){
	ull r=inf64;
	for(;x;x&=x-1) chkmin(r,c[x]);
	return r;
}
void solve(int L,int R,int l,int r){
	if(L>R) return;
	if(l==r){
		int i=l;
		for(int j=max(L,i+1);j<=min(R,i+m);j++){
			ull tmp=f[j-i-1][trans[i]]+(res[i]&HI);
			re[j]=tmp;
		}
		return;
	}
	int piv=-1, j=(L+R)>>1;
	for(int i=max(l,j-m);i<=min(r,j-1);i++){
		ull tmp=f[j-i-1][trans[i]]+(res[i]&HI);
		if(tmp<re[j]) re[j]=tmp, piv=i;
	}
	solve(L,j-1,l,piv), solve(j+1,R,piv,r);
}
void procedure(){
	n=read(), q=read();
	for(int i=1;i<=n;i++) a[i]=read(), b[a[i]]=i;
	for(int i=1;i<=n;i++) res[i]=inf64;
	res[0]=0;
	for(int l=1,r;l<=n;l=r+1){
		r=min(l+B-1,n), m=r-l+1;
		memset(f,0x3f,sizeof(f));
		for(int i=l;i<=r;i++) f[0][i-l]=b[i];
		for(int i=0;i<=m-1;i++) ord[i]=i;
		sort(ord,ord+r-l+1,[&](int x,int y){ return b[x+l]<b[y+l]; });
		for(int i=0;i<=m-1;i++) rk[ord[i]]=m-i;
		for(int i=1;i<=m-1;i++){
			ull v=inf64; memset(c,0x3f,sizeof(c));
			for(int j=m-1;j>=0;j--){
				chkmin(f[i][j],min(v+LO+1,query(rk[j])));
				update(rk[j],f[i-1][j]), chkmin(v,f[i-1][j]);
			}
		}
		for(int i=0;i<=m-1;i++){
			ull v=*min_element(f[i],f[i]+m)+LO+1, suf=inf64; 
			for(int j=m-1;j>=0;j--){
				int J=ord[j];
				chkmin(f[i][J],min(v,suf));
				chkmin(suf,f[i][J]);
			} 
			f[i][m]=v;
		}
		nxt[n+1]=m;
		for(int i=n;i>=0;i--){
			if(l<=a[i] && a[i]<=r) nxt[i]=a[i]-l;
			else nxt[i]=nxt[i+1];
		}
		for(int i=0;i<=r;i++) re[i]=inf64;
		for(int i=0;i<=l-1;i++) trans[i]=nxt[res[i]&LO];
		solve(1,r,0,l-1);
		for(int i=0;i<=r;i++) chkmin(res[i],re[i]);
	}
	for(int i=0;i<=n;i++) ans[i]=(res[i]>>32)*n+(res[i]&LO);
	for(int i=1;i<=q;i++){
		ull x=read();
		printf("%d\n",int(upper_bound(ans,ans+1+n,x)-ans-1));
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
