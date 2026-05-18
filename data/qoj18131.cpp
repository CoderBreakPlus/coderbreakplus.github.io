// created time: 2026-05-17 19:06:19
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

int n,a[200005];

struct BIT{
	int c[200005];
	void upd(int x,int w){
		while(x<=n){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	int qry(int x){
		int ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
	void clear(){ for(int i=1;i<=n;i++) c[i]=0; }
}B,C;

ll ans;
int b[200005],bm,c[200005],cm;
void insb(int x,int w){ ans+=C.qry(x-1)*w,B.upd(x,w); }
void insc(int x,int w){ ans+=(B.qry(n)-B.qry(x))*w,C.upd(x,w); }
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	B.clear(),C.clear();
	bm=cm=0;

	ans=0;
	for(int i=1;i<=n;i++){
		if(!bm||a[i]>b[bm])b[++bm]=a[i],insb(a[i],1);
		else{
			int x=lower_bound(b+1,b+bm+1,a[i])-b;
			insb(b[x],-1);
			b[x]=a[i];
			insb(b[x],1);
		}
		// cout<<"ans="<<ans<<endl;

		if(!cm||a[i]<c[cm])c[++cm]=a[i],insc(a[i],1);
		else{
			int x=lower_bound(c+1,c+cm+1,a[i],greater<int>())-c;
			insc(c[x],-1);
			// cout<<"delete "<<c[x]<<" on B "<<B.qry(n)-B.qry(c[x])<<endl;
			// cout<<"newans="<<ans<<endl;
			c[x]=a[i];
			insc(c[x],1);
		}
		// cout<<"ans="<<ans<<endl;

		// for(int j=1;j<=bm;j++)cout<<b[j]<<" ";cout<<endl;
		// for(int j=1;j<=cm;j++)cout<<c[j]<<" ";cout<<endl;

		// int ret=0;
		// for(int j=1;j<=bm;j++)
		// 	for(int k=1;k<=cm;k++)
		// 		ret+=(b[j]>c[k]);
		printf("%lld ",ans);
	}
	puts("");
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