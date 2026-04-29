#include<cstdio>
#include<cmath>
#include<algorithm>
#include<cassert>
typedef unsigned long long ull;
typedef __uint128_t L;
struct FastMod {
    ull b, m;
    FastMod(ull b) : b(b), m(ull((L(1) << 64) / b)) {}
    ull operator ()(ull a) {
        ull q = (ull)((L(m) * a) >> 64);
        ull r = a - q * b; // can be proven that 0 <= r < 2*b
        return r >= b ? r - b : r;
    }
}mod(2);
int p,n,fac[210],ifac[210];
int pow(int x,int y){
	int res=1;
	while(y){
		if(y&1) res=mod(1ll*res*x);
		x=mod(1ll*x*x),y>>=1; 
	}
	return res;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	scanf("%d%d",&n,&p);
	mod=FastMod(p);
	fac[0]=1;
	for(int i=1;i<=n;i++) fac[i]=mod(1ll*fac[i-1]*i);
	ifac[n]=pow(fac[n],p-2);
	for(int i=n;i;i--) ifac[i-1]=mod(1ll*ifac[i]*i);
	int ans=0;
	int lim=2*sqrt(n)+1;
	for(int a1=std::max(1,n-lim);a1<=n;a1++){
		static int f[210][210][210];
		for(int i=0;i<=n;i++) for(int j=0;j<=n;j++) for(int k=0;k<=n;k++) f[i][j][k]=0;
		for(int i=0;i<=n;i++)
			for(int sum=0;sum<=a1;sum++)
				f[i][sum][0]=mod(1ll*fac[n]*ifac[n-i]);
		for(int k=1;k<=n+1-a1;k++){
			for(int i=0;i<n;i++)
				for(int sum=0;sum<=a1;sum++){
					int &ans=f[i][sum][k];
					int r=(a1-sum)/k;
					for(int cnt=std::min(r,n-i);~cnt;--cnt)if(k<=1||i+cnt>=n-a1+2-k){
						ans=mod(ans+1ll*f[i+cnt][sum+cnt*k][k-1]*ifac[cnt]);
					}
				}
			for(int sum=0;sum<=a1;sum++) f[n][sum][k]=fac[n];
		}
		ans=mod(ans+f[0][0][n+1-a1]);
	}
	printf("%d\n",ans);
	return 0;
}
