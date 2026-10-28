#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
const ll mod2=1000000007;
int t,n,l,k;
ll dp[5005][52][102];
ll s[5005][52][102];
ll f(int L,int K,int N){return (N/n*s[L][K][n]+s[L][K][N%n])%mod2;}
ll f(int L,int K,int a,int b){return (f(L,K,b+100000*n)-f(L,K,a+100000*n-1)+mod2)%mod2;}
ll qkpw(ll a,ll b){ll r=1;while(b){if(b&1)r=r*a%mod2;a=a*a%mod2;b>>=1;}return r;}
ll inv(ll x){return qkpw((x%mod2+mod2)%mod2,mod2-2);}
void Q()
{
	cin>>n>>l>>k;
	for(int L=1;L<=l;++L) for(int K=0;K<=k;++K)
	{
		ll p1=inv(2*L+K-2)*(L+K-1)%mod2,p2=(mod2+1-p1)%mod2,q=inv(L+K);p1=p1*q%mod2;p2=p2*q%mod2;
		for(int i=1;i<=n;++i)
		{
			ll cur=((L+K-i+n)/n*p1+(L-i+n)/n*p2);if(K)cur+=K*p2%mod2*dp[L][K-1][((i-L-1+L*n)%n+1)];
			cur+=f(L-1,K,i-L-K,i-1)*p1+f(L-1,K,i-L,i-1)*p2;
			s[L][K][i]=(s[L][K][i-1]+(dp[L][K][i]=cur%mod2))%mod2; 
		}
	}
    for(int i=1;i<=n;++i) cout<<dp[l][k][i]<<" \n"[i==n];
}
int main()
{
	cin>>t;while(t--)Q();return 0; 
}
