#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x;scanf("%lld",&x);return x;
}
int n,m,a[100005];
int buc[1<<18];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)a[i]=read();

	if(n>5000){
		printf("%d\n",m);
		return;
	}
	ll sum=0;
	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++)
			sum+=buc[a[i]^a[j]]++;
	printf("%lld\n",min((ll)m,sum/3));
}
int main(){
	assert(freopen("shengdan.in","r",stdin));
	assert(freopen("shengdan.out","w",stdout));
	procedure();
}