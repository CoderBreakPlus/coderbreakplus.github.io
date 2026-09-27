#include<bits/stdc++.h>
using namespace std;
const int N=5010;
int fac[N],infac[N],mi[N][N],n,mod,ans;
int inc(const int &a,const int &b){return a+b>=mod?a+b-mod:a+b;}
int dec(const int &a,const int &b){return a-b<0?a-b+mod:a-b;}
int mul(const int &a,const int &b){return 1ll*a*b%mod;}
int sqr(const int &a){return 1ll*a*a%mod;}
void Inc(int &a,const int &b){a=a+b>=mod?a+b-mod:a+b;}
void Dec(int &a,const int &b){a=a-b<0?a-b+mod:a-b;}
void Mul(int &a,const int &b){a=1ll*a*b%mod;}
void Sqr(int &a){a=1ll*a*a%mod;}
int qmi(int a,int b)
{
	int res=1;
	while(b)
	{
		if(b&1) Mul(res,a);
		Sqr(a),b>>=1;
	}
	return res;
}
void init()
{
	fac[0]=1;
	for(int i=1;i<N;i++) fac[i]=mul(fac[i-1],i);
	infac[N-1]=qmi(fac[N-1],mod-2);
	for(int i=N-2;i>=0;i--) infac[i]=mul(infac[i+1],i+1);
	for(int i=1;i<N;i++)
	{
		mi[i][0]=1;
		for(int j=1;j<N;j++)
			mi[i][j]=mul(mi[i][j-1],i);
	}
}
int binom(int a,int b)
{
	if(a<b) return 0;
	return mul(fac[a],mul(infac[b],infac[a-b]));
}
int main()
{
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	cin>>n>>mod;
	init();
	for(int i=1;i*2<=n;i++)
		for(int j=0;j+i*2<=n;j++)
			Inc(ans,mul(binom(n,j),mul(fac[n-j],mul(mi[n-1][i],mul(mi[n-i-j][j],mul(binom(n-i-j-1,i-1),infac[i]))))));
	cout<<ans<<endl;
	return 0;
 } 

