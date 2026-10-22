// created time: 2026-10-22 16:03:54
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

int n,a[3005],b[3005],f[6005][6005],buc[6005][6005],iv[3005],lv[6005];
vector<int>v[6005],vv[6005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)
		iv[i]=INV(i);
	for(int i=1;i<=n;i++){
		a[i]=read(),b[i]=read();	
		v[max(a[i],b[i])].pb(i);
		vv[min(a[i],b[i])].pb(i);
		buc[min(a[i],b[i])][max(a[i],b[i])]++;
	}
	for(int i=2*n;i>=1;i--)
		for(int j=i;j<=2*n;j++)buc[i][j]+=buc[i][j-1];
	for(int i=2*n;i>=1;i--)
		for(int j=i;j<=2*n;j++)buc[i][j]+=buc[i+1][j];

	for(int l=2*n;l>=1;l--){
		int sum=0;
		for(int r=l;r<=2*n;r++){
			int cnt=buc[l][r];
			for(auto x: v[r])
				if(min(a[x],b[x])>=l) addmod(sum+=f[l][a[x]-1]);
			for(auto x: vv[l])
				if(max(a[x],b[x])<=r) addmod(lv[r]+=f[a[x]+1][r]);
			f[l][r]=((ull)f[l][r]+sum+cnt+lv[r])*iv[cnt]%mod;
		}
	}
	printf("%d\n",f[1][2*n]);
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