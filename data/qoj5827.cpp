// created time: 2026-05-15 15:44:06
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

int n,m,u[1005],v[1005];
ull a[15],c;
int f[16][1<<15],g[1<<15],h[1<<15];

void upd(int &x,ull y){ x=(x+y)%mod; }

int dp[1<<15];

int solve(vector<ull> vec){
	if(!vec.size())return c==0; // 特判
	int ret=0;
	ull sb=0;for(auto x:vec)sb^=x;

	for(int i=60;i>=0;i--){
		if((sb>>i+1)^(c>>i+1))break;

		int f[3]={1,0,0};
		for(ull x:vec){
			int g[3]={0,0,0};
			ull v0=(1ull<<i)%mod,v1=(x&((1ull<<i)-1))%mod;
			if((x>>i)&1){
				g[0]=f[0]*v1%mod;
				g[1]=(f[1]*v1+f[2]*v0+f[0])%mod;
				g[2]=(f[2]*v1+f[1]*v0)%mod;
			}else{
				g[0]=f[0]*v1%mod;
				g[1]=f[1]*v1%mod;
				g[2]=f[2]*v1%mod;
			}
			f[0]=g[0],f[1]=g[1],f[2]=g[2];
		}
		int o=((sb^c)>>i)&1;
		int now=(o?f[1]:f[2]);
		addmod(ret+=now);
	}
	return ret;
}
void procedure(){
	n=read(),m=read(),c=read();
	for(int i=0;i<n;i++)a[i]=read()+1;
	for(int i=1;i<=m;i++){
		u[i]=read()-1,v[i]=read()-1;
	}
	for(int i=0;i<n;i++)
		for(int j=i+1;j<n;j++){
			if(a[i]>a[j]){
				swap(a[i],a[j]);
				for(int x=1;x<=m;x++){
					if(u[x]==i)u[x]=j;else if(u[x]==j)u[x]=i;
					if(v[x]==i)v[x]=j;else if(v[x]==j)v[x]=i;
				}
			}
		}
	for(int i=1;i<=m;i++)
		g[(1<<u[i])|(1<<v[i])]++;
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)
			if((j>>i)&1) g[j]+=g[j^(1<<i)];

	for(int i=1;i<(1<<n);i++){
		h[i]=!g[i];
		int x=(i&-i), ii=i^x;
		for(int j=ii;j;j=(j-1)&ii)
			if(!g[j]) addmod(h[i]+=mod-h[i^j]);
	}

	f[0][0]=1;
	for(int i=0;i<n;i++){
		for(int j=0;j<(1<<n);j++){
			if((j>>i)&1){
				addmod(f[i+1][j^(1<<i)]+=f[i][j]);
				continue;
			}
			int res=(~j)&((1<<n)-(1<<i+1));
			for(int K=res;;K=(K-1)&res){int k=K^(1<<i);
				if(__builtin_parity(k))
					upd(f[i+1][j^K^(1<<i)],(ull)f[i][j]*h[k]);
				else
					upd(f[i+1][j^K],(ull)f[i][j]*h[k]%mod*(a[i]%mod));
				if(!K)break;
			}
		}
	}

	int ans=0;
	for(int i=0;i<(1<<n);i++){
		vector<ull>vec;
		for(int j=0;j<n;j++) 
			if((i>>j)&1) vec.pb(a[j]);

		if(f[n][i]){
			upd(ans,(ull)f[n][i]*solve(vec));
		}
	}
	printf("%d\n",ans);
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