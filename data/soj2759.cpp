// created time: 2026-11-19 08:58:47
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
const int V=62;

int n;
ll a[2000005];

ll dp[64],dp2[64],cnt[64];
int lst;
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	lst=-1;
	memset(dp,0,sizeof(dp));

	ll ans=0;
	for(int i=n;i>=1;i--){
		for(int j=1;j<=V;j++)
			chkmax(ans, i+dp[j]+(j==lst));
		if(i==1)break;
		
		ll dc=a[i]-a[i-1],n0=1,n1=0;
		memset(cnt,0,sizeof(cnt));

		int p=0;
		while(dc>1){
			cnt[++p]=n0+(dc>2?n1:0);
			if(dc&1)
				n1=n1*2+n0;
			else
				n0=n0*2+n1;
			
			dc=(dc+1)/2;

			// cnt[p]+=n0;
			// if(dc>1) cnt[p]+=n1;
			// cout<<"at "<<p<<" feel "<<cnt[p]<<endl;
		}
		int lst2=-1;
		p=lg2(a[i]-a[i-1]);
		if((1ull<<p)!=a[i]-a[i-1]) lst2=p+1;
		memset(dp2,0,sizeof(dp2));
		for(int j=1;j<=V;j++){
			auto trans=[&](int k){
				if(k>=1&&k<=V&&k<=j){
					int add=0;
					if(k+1<j)add=(j==lst)+(k+1==lst2);
					else if(k<j)add=(j==lst||k+1==lst2);
					chkmax(dp2[k], dp[j]+cnt[k]+add);
				}
			};
			trans(j);
			trans(j-1);
			// trans(j-2);
			trans(p+1);
			trans(p);
			trans(p-1);
			// for(int k=1;k<=j;k++){
			// }
		}
		memcpy(dp,dp2,sizeof(dp));
		lst=lst2;
		// cout<<"lst="<<lst<<endl;

		// cout<<"i="<<i-1<<endl;
		// for(int j=1;j<=5;j++) cout<<dp[j]<<" "; cout<<endl;
		// cout<<"lst="<<lst<<endl;
	}
	printf("%lld\n",ans);
}
int main(){
	// assert(freopen("test.in","r",stdin));
	// assert(freopen("test.out","w",stdout));
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}