// created time: 2026-06-07 09:48:43
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

int n,m,k,a[405][405];

void procedure(){
	n=read(),m=read(),k=read();
	for(int i=1;i<=k;i++)
		for(int j=1;j<=n;j++)a[j][i]=read();

	int L=-k,R=k; ll ans=0;
	ll sum=0;
	for(int i=1;i<=n;i++){
		sort(a[i]+1,a[i]+k+1);
		for(int j=1;j<=k;j++)sum+=a[i][j];
		a[i][k+1]=m;
	}
	
	while(L<=R){
		int mid=(L+R)>>1;
		ll fk=0,w=0;
		for(int i=1;i<=n;i++){
			for(int j=1,d=-k;j<=k+1&&d<=mid;j++,d+=2){
				fk+=(ll)(a[i][j]-a[i][j-1])*d;
				w+=a[i][j]-a[i][j-1];
			}
		}
		// cout<<"w="<<w<<endl;
		if(w>=m){
			// cout<<"mid="<<mid<<endl;
			ans=fk-(ll)(w-m)*mid;
			R=mid-1;
		}else L=mid+1;
	}
	printf("%lld\n",(ans+sum)/2);
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