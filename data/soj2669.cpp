// created time: 2026-09-05 08:27:33
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

int op,n,k;
char s[100005];

namespace sol0{
	int f[100005][205],g[100005][205];

	void main(){
		if(s[1]!='1') f[1][0]=1, g[1][0]=1;
		if(s[1]!='0') f[1][k]=1, g[1][k]=1;

		for(int i=2;i<=n;i++){
			for(int j=0;j<=k;j++){
				if(s[i]!='1'){
					if(j>0){
						addmod(f[i][j-1]+=f[i-1][j]);
						addmod(g[i][j-1]+=g[i-1][j]);
					}else{
						addmod(f[i][0]+=f[i-1][0]);
						g[i][0]=((ull)g[i][0]+g[i-1][0]+f[i-1][0])%mod;
					}
				}
				if(s[i]!='0'){
					if(j<k){
						addmod(f[i][j+1]+=f[i-1][j]);
						addmod(g[i][j+1]+=g[i-1][j]);
					}else{
						addmod(f[i][k]+=f[i-1][k]);
						g[i][k]=((ull)g[i][k]+g[i-1][k]+f[i-1][k])%mod;
					}
				}
			}
		}
		int ans=0;
		for(int i=0;i<=k;i++)addmod(ans+=g[n][i]);
		printf("%d\n", ans);
	}
}
namespace sol1{
	int f[100005][205],g[100005][205];

	void main(){
		if(s[1]!='1') f[1][0]=1, g[1][0]=0;
		if(s[1]!='0') f[1][1]=1, g[1][1]=0;

		for(int i=2;i<=n;i++){
			for(int j=0;j<=k;j++){
				if(s[i]!='1'){
					if(j>0){
						addmod(f[i][j-1]+=f[i-1][j]);
						addmod(g[i][j-1]+=g[i-1][j]);
					}else{
						addmod(f[i][0]+=f[i-1][0]);
						g[i][0]=((ull)g[i][0]+g[i-1][0])%mod;
					}
				}
				if(s[i]!='0'){
					if(j<k){
						addmod(f[i][j+1]+=f[i-1][j]);
						addmod(g[i][j+1]+=g[i-1][j]);
					}else{
						addmod(f[i][k]+=f[i-1][k]);
						g[i][k]=((ull)g[i][k]+g[i-1][k]+f[i-1][k])%mod;
					}
				}
			}
		}
		int ans=0;
		for(int i=0;i<=k;i++)addmod(ans+=g[n][i]);
		// cout<<"ans = "<<ans<<endl;

		memset(f,0,sizeof(f));memset(g,0,sizeof(g));

		if(s[1]!='0') f[1][0]=1, g[1][0]=0;
		if(s[1]!='1') f[1][1]=1, g[1][1]=0;

		for(int i=2;i<=n;i++){
			for(int j=0;j<=k;j++){
				if(s[i]!='0'){
					if(j>0){
						addmod(f[i][j-1]+=f[i-1][j]);
						addmod(g[i][j-1]+=g[i-1][j]);
					}else{
						addmod(f[i][0]+=f[i-1][0]);
						g[i][0]=((ull)g[i][0]+g[i-1][0])%mod;
					}
				}
				if(s[i]!='1'){
					if(j<k){
						addmod(f[i][j+1]+=f[i-1][j]);
						addmod(g[i][j+1]+=g[i-1][j]);
					}else{
						addmod(f[i][k]+=f[i-1][k]);
						g[i][k]=((ull)g[i][k]+g[i-1][k]+f[i-1][k])%mod;
					}
				}
			}
		}
		for(int i=0;i<=k;i++)addmod(ans+=g[n][i]);
		printf("%d\n",ans);
	}
}
void procedure(){
	op=read(),n=read(),k=read();
	scanf("%s",s+1);

	if(op==0) sol0::main();
	else sol1::main();
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