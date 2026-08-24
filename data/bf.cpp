#include<bits/stdc++.h>
#define int long long
using namespace std;
const int N=1e5+10;
const int mod=1e9+7;
int n,k,m,ans;
int dp[N][13][16];
int cal(int x) {
	int num=0;
	while(x) {
		if(x&1) num++;
		x>>=1;
	}
	return num;
}
signed main() {
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ios::sync_with_stdio(false);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>k>>m;
	dp[0][0][0]=1;
	for(int i=0;i<n;i++)
		for(int j=0;j<=k;j++)
			for(int l=0;l<(1<<m);l++) {
				dp[i+1][j][(l<<1)&((1<<m)-1)]=(dp[i+1][j][(l<<1)&((1<<m)-1)]+dp[i][j][l])%mod;
				if(j<k) dp[i+1][j+1][((l<<1)&((1<<m)-1))|1]=((dp[i+1][j+1][((l<<1)&((1<<m)-1))|1])+dp[i][j][l]*(cal(l)+1))%mod;//一个小细节，这题的方案有顺序，所以把 i+1 插入的位置是有多种的。
			}
	for(int i=0;i<(1<<m);i++) ans=(ans+dp[n][k][i])%mod;
	cout<<ans;
	return 0;
}