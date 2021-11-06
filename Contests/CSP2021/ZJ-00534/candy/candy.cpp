#include<cstdio>
using namespace std;
typedef long long ll;
ll n,L,R;
int main(){
	freopen("candy.in","r",stdin);
	freopen("candy.out","w",stdout);
	scanf("%lld%lld%lld",&n,&L,&R);
	if(R-L+1>=n){
		printf("%lld\n",n-1);
		return 0;
	}
	ll maxk=R/n*n;
	if(maxk>L){
		printf("%lld\n",n-1);
		return 0;
	}
	printf("%lld\n",R%n);
	return 0;
}
