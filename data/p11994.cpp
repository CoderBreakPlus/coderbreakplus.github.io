// created time: 2026-07-14 19:32:13
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

int n,q,a[200005],l[200005],r[200005];
ll f[20][200005];
ll sum[200005],cur[200005];
int col[200005],ans[200005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	q=read();
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read();
	}
	for(int z=1;z<=100;z++){
		for(int i=1;i<=n;i++) 
			if(a[i]<=z) sum[i]=sum[i-1]-a[i];
			else sum[i]=sum[i-1]+a[i];

		for(int i=0;i<=n;i++)f[0][i]=sum[i];
		for(int i=1;(1<<i)<=n+1;i++)
			for(int j=0;j<=n-(1<<i)+1;j++)
				f[i][j]=min(f[i-1][j],f[i-1][j+(1<<i-1)]);

		for(int i=1;i<=n;i++) 
			if(a[i]<z) sum[i]=sum[i-1]-a[i],col[i]=col[i-1]+1;
			else sum[i]=sum[i-1]+a[i],col[i]=col[i-1];

		// cout<<"z="<<z<<endl;
		auto qry = [&](int l,int r){
			int p=lg2(r-l+1);
			return min(f[p][l],f[p][r-(1<<p)+1]);
		};
		auto check = [&](int l,int r,ll s){
			return s+qry(l-1,r)-f[0][l-1]>=0;
		};
		for(int i=1;i<=q;i++){
			if(l[i]>r[i])continue;
			int L=l[i],R=r[i],pt=r[i]+1;

			while(L<=R){
				int mid=L+R>>1;
				if(check(mid,r[i],cur[i]+sum[mid-1]-sum[l[i]-1])){
					pt=mid;
					R=mid-1;
				}else L=mid+1;
			}
			// cout<<"at "<<i<<" l="<<l[i]<<" r="<<r[i]<<" pt="<<pt<<" cur="<<cur[i]<<endl;
			cur[i]+=sum[pt-1]-sum[l[i]-1];
			ans[i]+=col[pt-1]-col[l[i]-1];
			l[i]=pt;
		}
	}
	for(int i=1;i<=q;i++){
		printf("%d\n",ans[i]+r[i]-l[i]+1);
	}
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