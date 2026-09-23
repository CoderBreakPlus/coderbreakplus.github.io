#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };
const ll INF = 1e18;
int n,m,b[605]; ll a[605];
int C[605][605], fac[605], ifac[605], P[605][605];
int dp[605][605], ans[605];

ll s[605],mn[605],id[605],t;
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read();

	for(int i=1;i<=n;i++){
		if(!b[i]){
			ll tmp = 2*INF, idx = 0;
			for(int j=i+1;j<=n;j++)
				if(b[j] && a[j] % a[i] == 0 && a[j] < tmp){
					tmp = a[j];
					idx = b[j];
				}
			if(tmp <= INF) {
				s[++t] = a[i];
				mn[t] = tmp;
				id[t] = idx;
			}
		}else ans[b[i]]++;
	}

	for(int i=1;i<=t;i++){
		addmod(dp[i][1] += 1);
		// cout<<"node "<<i<<" mn = "<<mn[i]<<" id = "<<id[i]<<endl;
		int cnt = 0;
		for(int j=i+1;j<=t;j++){
			if(s[j] > mn[i]) break;
			if(s[j] % s[i] == 0){
				cnt ++;
				for(int k=1;k<=t;k++){
					if(!dp[i][k]) continue;
					dp[j][k+cnt] = (dp[j][k+cnt] + 1ull * dp[i][k] * P[k-1+cnt-1][cnt-1]) % mod;
				}
			} 
		}
		for(int k=1;k<=t;k++){
			if(!dp[i][k]) continue;
			ans[id[i]] = (ans[id[i]] + 1ull * dp[i][k] * P[k-1+cnt][cnt] % mod * ifac[k+cnt]) % mod;
		}
	}

	for(int i=1;i<=m;i++) printf("%d ",ans[i]);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("input.txt","r",stdin));
		assert(freopen("output.txt","w",stdout));
	#endif
	for(int i=0;i<=600;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++) addmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
	}
	fac[0]=ifac[0]=1;
	for(int i=1;i<=600;i++) fac[i]=1ull*fac[i-1]*i%mod, ifac[i]=INV(fac[i]);
	for(int i=0;i<=600;i++)
		for(int j=0;j<=i;j++) P[i][j]=1ull*C[i][j]*fac[j]%mod;
	
 	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}