// created time: 2026-11-06 09:08:19
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 i128;

inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}

ll n,A[200005],BB[200005],a[200005],b[200005];
i128 c0[200005],c1[200005],v[200005],s[200005];
ll stk[200005],top;

void procedure(){
	n=read();
	ll mx=1;
	for(ll i=1;i<=n;i++){
		A[i]=read();
		if(A[i]>A[mx])mx=i;
	}
	for(ll i=1;i<=n;i++)BB[i]=read();

	for(ll i=1;i<=n;i++){
		a[i]=A[(i+mx-2)%n+1];
		b[i]=BB[(i+mx-2)%n+1];
	}
	a[n+1]=a[1],b[n+1]=b[1];

	for(ll j=1;j<=n+1;j++){
		c0[j]=c0[j-1]+b[j];
		c1[j]=c1[j-1]+(i128)b[j]*j;
		v[j]=a[j]+2*(c1[j]-j*c0[j]);
		s[j]=s[j-1]+v[j];
	}

	top=0;
	for(ll j=1;j<=n+1;j++){
		while(top>=2){
			ll k=stk[top-1],i=stk[top];
			if((v[i]-v[k])*(j-i)<=(v[j]-v[i])*(i-k))
				top--;
			else break;
		}
		stk[++top]=j;
	}

	i128 ans=0;
	for(ll j=2;j<=n+1;j++)ans+=2*(i128)a[j];

	for(ll t=2;t<=top;t++){
		ll k=stk[t-1],j=stk[t];
		ans+=(j-k-1)*(v[k]+v[j])-2*(s[j-1]-s[k]);
	}

	printf("%.12Lf\n",(long double)ans/(2*n));
}

int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	while(T--)procedure();
	return 0;
}