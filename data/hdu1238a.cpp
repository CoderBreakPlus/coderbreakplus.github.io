#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N=500005,B1=131,B2=13331,M1=1e9+7,M2=1e9+9;
int pw1[N],pw2[N],h1[N],h2[N],dp[N],ndp[N];
char s[N];
inline int g1(int l,int r){return (h1[r]-(ll)h1[l-1]*pw1[r-l+1]%M1+M1)%M1;}
inline int g2(int l,int r){return (h2[r]-(ll)h2[l-1]*pw2[r-l+1]%M2+M2)%M2;}
inline bool eq(int l1,int r1,int l2,int r2){
	return g1(l1,r1)==g1(l2,r2)&&g2(l1,r1)==g2(l2,r2);
}
void solve(){
	int n,k;
	scanf("%d%d%s",&n,&k,s+1);
	ll sk=(ll)k*(k-1)/2;
	if((ll)k+sk>n){puts("0");return;}
	for(int i=1;i<=n;++i){
		h1[i]=((ll)h1[i-1]*B1+s[i])%M1;
		h2[i]=((ll)h2[i-1]*B2+s[i])%M2;
		ndp[i]=0;
	}
	int max_l=(n-sk)/k;
	ll ans=0;
	for(int l1=max_l;l1>=1;--l1){
		int tot=k*l1+sk;
		for(int p=1;p<=n;++p){
			if(p+2*l1-1<=n&&eq(p,p+l1-1,p+l1,p+2*l1-1))
				dp[p]=ndp[p+l1]+1;
			else dp[p]=0;
			if(dp[p]>=k-1&&p+tot-1<=n)++ans;
		}
		for(int p=1;p<=n;++p)ndp[p]=dp[p];
	}
	printf("%lld\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	pw1[0]=pw2[0]=1;
	for(int i=1;i<N;++i){
		pw1[i]=(ll)pw1[i-1]*B1%M1;
		pw2[i]=(ll)pw2[i-1]*B2%M2;
	}
	int T;
	if(scanf("%d",&T)!=EOF)while(T--)solve();
	return 0;
}