// created time: 2026-05-14 09:16:04
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

int a,b;
const int B=1500;
double f[2][3005];
double *dp[2] = {f[0]+B, f[1]+B};
int bas[100005];

void procedure(){
	a=read(),b=read();
	if(!b){
		printf("%d\n",a);
		return;
	}
	if(!a){
		puts("0");
		return;
	}
	int va=1, vb=-1;
	if(a<b)swap(a,b),swap(va,vb);
	for(int i=0;i<=a;i++)bas[i]=(ll)i*b/a;


	for(int i=1,o=1;i<=a;i++,o^=1){
		memset(f[o],0,sizeof(f[o]));

		int Lj=max(0,bas[i-1]-B), Rj=min(b,bas[i-1]+B);

		if(i==1){
			for(int j=Lj;j<=Rj;j++)
				chkmax(dp[o^1][j-bas[i-1]], (double)j*vb);
		}
		int Li=max(0,bas[i]-B), Ri=min(b,bas[i]+B);

		auto valj = [&](int x){
			if(Lj <= x && x <= Rj)
				return dp[o^1][x-bas[i-1]];
			return 0.0;
		};
		auto vali = [&](int x){
			if(Li <= x && x <= Ri)
				return dp[o][x-bas[i]];
			return 0.0;
		};

		for(int j=Li;j<=Ri;j++){
			double v=(double)i/(i+j)*(valj(j)+va)+(double)j/(i+j)*(vali(j-1)+vb);

			// cout<<i/(i+j)<<" * "<<(valj(j)+va)<<" + "<<j/(i+j)<<" * "<<(vali(j-1)+vb)<<endl;
			chkmax(dp[o][j-bas[i]], v);

			// cout<<"i="<<i<<" j="<<j<<" dp = "<<dp[o][j-bas[i]]<<endl;
		}
	}
	printf("%.10lf\n",dp[a&1][b-bas[a]]);
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