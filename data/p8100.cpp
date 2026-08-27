#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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

int n,a[5005],f[5005][5005],h[2][5005];
int id[5005];
void procedure(){
	n=read();
	int c[2]={0,0};
	for(int i=1;i<=n;i++){
		a[i]=read();
		id[i]=++c[a[i]&1];
	}
	memset(h,0x3f,sizeof(h));
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			if(((a[i]^a[j])&1)&&abs(a[i]-a[j])!=1){
				chkmin(h[a[i]&1][id[i]],id[j]);
			}

	// cout<<c[0]<<endl;
	// for(int i=0;i<=c[0];i++) cout<<h[0][i]<<" "; cout<<endl;
	// cout<<c[1]<<endl;
	// for(int i=0;i<=c[1];i++) cout<<h[1][i]<<" "; cout<<endl;
	

	for(int i=0;i<=c[0];i++)
		for(int j=0;j<=c[1];j++)f[i][j]=0;
	f[0][0]=1;
	for(int i=0;i<=c[0];i++)
		for(int j=0;j<=c[1];j++){
			if(i<c[0]&&h[0][i+1]>j)addmod(f[i+1][j]+=f[i][j]);
			if(j<c[1]&&h[1][j+1]>i)addmod(f[i][j+1]+=f[i][j]);
		}
	printf("%d\n",f[c[0]][c[1]]);
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