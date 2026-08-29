#include<bits/stdc++.h>
using namespace std;
int n,a,jc[10010000],ij[10100000];
const int mod=1e9+7;
int qpow(int a,int b){
	int c=1;
	for(;b;b>>=1){
		if(b&1)c=1ll*a*c%mod;
		a=1ll*a*a%mod;
	}
	return c;
}
int C(int a,int b){if(a<b)return 0;return 1ll*jc[a]*ij[b]%mod*ij[a-b]%mod;}
int sol(int a,int b,int c){
	return 1ll*a*jc[a+b+c]%mod*(1ll*ij[a+c]*jc[a+c-1]%mod)%mod;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	scanf("%d%d",&n,&a);
	jc[0]=1;
	for(int i=1;i<=n;i++)jc[i]=1ll*jc[i-1]*i%mod;
	ij[n]=qpow(jc[n],mod-2);
	for(int i=n;i;i--)ij[i-1]=1ll*i*ij[i]%mod;
	int ans=0;
	for(int i=1;i<=a;i++)
		for(int j=0;j<i;j++)
		(ans+=((j&1)?-1ll:1ll)*C(i-1,j)*sol(i-1-j,a-i,n-a)%mod)%=mod;
	for(int i=0;i<=a;i++)
	(ans+=((i&1)?-1ll:1ll)*C(a,i)*sol(a-i,0,n-a)%mod)%=mod;
	return printf("%d",(ans+mod)%mod),0;
}
//第一个自环。
