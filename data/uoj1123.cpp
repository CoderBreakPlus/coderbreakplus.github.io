// created time: 2026-10-24 14:17:05
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

int n,m,a[805],f[805][805],hz[805][805],C[805][805];
vector<int>buc[805],bet[805];
inline void upd(int &a,ull b){ a=(a+b)%mod; }

int tmp[805];
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read(),buc[a[i]].pb(i),bet[a[i]].pb(i),bet[(a[i]+m-1)%m].pb(i);

	int ans=0;
	for(int x=0;x<=buc[0].size();x++){
		memset(f,0,sizeof(f));
		f[0][x]=1;
		for(int i=0;i<m;i++){
			auto &a=buc[i],&b=buc[(i+1)%m];
			int sa=a.size(),sb=b.size();

			for(int j=0;j<=sa;j++) addmod(f[i+1][sb]+=f[i][j]);

			for(int p=0;p<=sa;p++)
				for(int q=0;q<=sb;q++)hz[p][q]=0;
			int cur=0;
			for(int p=sa-1;p>=0;p--){
				addmod(cur+=f[i][p+1]);
				for(int q=sb-1;q>=0;q--){
					if(a[p]<b[q]){
						addmod(hz[p][q]=cur+hz[p+1][q+1]);
						addmod(f[i+1][q]+=hz[p][q]);
					}
					hz[p][q]=((ll)hz[p][q]+hz[p+1][q]+hz[p][q+1]+mod-hz[p+1][q+1])%mod;
				}
			}
		}
		addmod(ans+=f[m][x]);
	}

	if(~m&1){
		for(int x=0;x<buc[0].size();x++){
			memset(f,0,sizeof(f));
			f[0][x]=1;
			for(int i=0;i<m;i++){
				auto &a=buc[i],&b=buc[(i+1)%m];
				int sa=a.size(),sb=b.size();

				for(int p=0;p<=sa;p++)
					for(int q=0;q<=sb;q++)hz[p][q]=0;
				int cur=0;
				for(int p=sa-1;p>=0;p--){
					cur=f[i][p];
					for(int q=sb-1;q>=0;q--){
						if(a[p]<b[q]){
							addmod(hz[p][q]=cur+hz[p+1][q+1]);
							addmod(f[i+1][q]+=hz[p][q]);
						}
						hz[p][q]=((ll)hz[p][q]+hz[p+1][q]+hz[p][q+1]+mod-hz[p+1][q+1])%mod;
					}
				}
			}
			addmod(ans+=mod-f[m][x]);
		}
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	for(int i=0;i<=800;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			addmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
	}
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}