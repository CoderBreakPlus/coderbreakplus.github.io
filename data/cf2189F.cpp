// created time: 2026-04-19 19:18:19
#pragma GCC optimize(3,"Ofast","inline","unroll-loops")
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,q,a[150005]; ll sum[150005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read(),sum[i]=sum[i-1]+a[i];
	sum[n+1]=sum[n];
	while(q--){
		int l=read()-1,r=read(),w=read();
		int ans0=0,ans1=0;

		int lst=0;

		while(l<r){
			int x;
			int sb=min(n+1-l, int(1.2*lst));
			if(sum[l+sb]>=sum[l]+w)
				x=lower_bound(sum+l+1,sum+l+sb,sum[l]+w)-sum;
			else
				x=lower_bound(sum+l+1,sum+n+2,sum[l]+w)-sum;


			// cout<<l+1<<" to "<<x<<endl;
			if(x>r){
				ans1=sum[r]-sum[l];
				break;
			}
			int len=x-l, jp=1;
			
			int L=2,R=(r-l)/len;
			while(L<=R){
				int mid=(L+R)>>1;
				if(sum[l+mid*len]-sum[l+(mid-1)*len]>=w){
					jp=mid;
					L=mid+1;
				}else R=mid-1;
			}

			l += len*jp;
			ans0 += jp;
			// cout<<"jp = "<<jp<<endl;
		}
		printf("%d %d\n",ans0,ans1);
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