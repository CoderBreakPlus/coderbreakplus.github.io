// created time: 2026-06-09 19:28:20
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

int n,m,a[1000005],b[1000005];

bool chk(int x1,int y1,int x2,int y2){
	assert(y1&&y2);
	return (ll)x1*y2>(ll)x2*y1;
}
struct Convex{
	int que[1000005],tl;
	void ins(int *a,int n){
		que[tl=1]=1;
		for(int i=2;i<=n;i++){
			while(tl>=2 && chk(a[que[tl]]-a[que[tl-1]],que[tl]-que[tl-1],
			a[i]-a[que[tl]],i-que[tl])) tl--;
			que[++tl]=i;
		}
	}
}A,B;
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=m;i++)b[i]=read();
	A.ins(a,n),B.ins(b,m);

	int pa=1,pb=1;
	ll ans=0;
	while(pa<A.tl||pb<B.tl){
		if(pa==A.tl||(pb<B.tl&&chk(a[A.que[pa+1]]-a[A.que[pa]],A.que[pa+1]-A.que[pa],
		b[B.que[pb+1]]-b[B.que[pb]],B.que[pb+1]-B.que[pb]))){
			ans+=(ll)(B.que[pb+1]-B.que[pb])*a[A.que[pa]];
			pb++;
		}else{
			ans+=(ll)(A.que[pa+1]-A.que[pa])*b[B.que[pb]];
			pa++;
		}
	}
	printf("%lld\n",ans);
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