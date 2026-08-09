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

int n,m,a[1005],f[1005],ia[1005],lca[1005][1005];

int LCA(int x,int y){
	if(x>y)swap(x,y);

	if(x==y) return x;
	if(lca[x][y])return lca[x][y];

	return LCA(x,f[y]);
}
bool ans[1005][1005];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) ia[a[i]=read()]=i;
	for(int i=2;i<=n;i++)f[i]=read();

	for(int l=1;l<=n;l++)
		for(int r=l;r<=n;r++){
			ans[l][r]=1;
			for(int x=l;x<=r;x++)
				for(int y=x+1;y<=r;y++){
					int z=LCA(ia[x],ia[y]);
					if(!(l<=a[z]&&a[z]<=r)){
						ans[l][r]=0;
						break;
					}
				}
		}
	while(m--){
		int l=read(),r=read(),ret=0;
		for(int L=l;L<=r;L++)
			for(int R=L;R<=r;R++)
				ret+=ans[L][R];
		printf("%d\n",ret);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}