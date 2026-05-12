// created time: 2026-05-06 14:10:17
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

int n,a[2005],b[2005],t;
tuple<ll,int,int> s[4000005];

struct BIT{
	int c[2005];
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
	void clear(){
		for(int i=1;i<=n;i++)c[i]=0;
	}
}B[2005],C;
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();

	t=0;
	for(int i=1;i<=n;i++)
		for(int j=1;j<=n;j++) s[++t]={(ll)a[i]*b[j],i,j};
	sort(s+1,s+t+1);
reverse(s+1,s+t+1);

	C.clear();
	for(int i=1;i<=n;i++) B[i].clear();

	ll cnt=0;
	for(int l=1;l<=t;l++){
		int r=l;while(r<t&&get<0>(s[r+1])==get<0>(s[l]))r++;
		for(int x=l;x<=r;x++){
			auto [v,i,j]=s[x];
			// cout<<v<<","<<i<<","<<j<<" ";
			cnt+=C.qry(i-1);
			cnt-=B[j].qry(i-1);
		}
		// cout<<endl;
		for(int x=l;x<=r;x++){
			auto [v,i,j]=s[x];
			C.upd(i,1);
			B[j].upd(i,1);
		}l=r;
		// cout<<"cnt="<<cnt<<endl;
	}
	cnt%=mod;
	printf("%d\n", cnt*INV((ull)n*(n-1))%mod);
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