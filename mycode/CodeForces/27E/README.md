[Prev](https://coderbreakplus.github.io/mycode/CodeForces/)

```cpp 
#include<bits/stdc++.h>
#define int long long
using namespace std;
int n,a[1010],cnt,prime[1010],tot;
bool isprime(int x){
	for(int i=2;i*i<=x;i++)
		if(x%i==0) return false;
	return true;
}
int mx=9e18;
inline bool qtimes(int a,int b){
	int maxtimes = 920000000000000000ll /b;
	if(a>maxtimes) return false;
	return true; 
}
inline int qpow(int a,int b){
	int ans=1,base=a;
	while(b){
		if(b&1){
			if(!qtimes(ans,base)) return -1;
			ans=ans*base;
		}
		if((!qtimes(base,base))&&(b/2!=0)) return -1;
		base=base*base;
		b>>=1;
	}
	return ans;
}
inline void dfs(int now){
	if(now==1){
		int tmp=1,qwe=1;
		sort(a+1,a+cnt+1);
		for(int i=1;i<=cnt;i++){
			if(!qtimes(qwe,a[i])) return;
			qwe*=a[i];
		}
		if(qwe!=n) return;
//		for(int i=1;i<=cnt;i++) cout<<a[i]<<" "; cout<<endl;
		for(int i=1,j=cnt;i<=cnt;i++,j--){
			int temp=qpow(prime[i],a[j]-1);
		//	cout<<prime[i]<<" "<<a[j]-1<<endl;
			if(temp==-1) return;
			if(!qtimes(tmp,temp)) return;
			tmp*=temp;
		}
		if(tmp<mx) mx=tmp; return;
	}
	for(int i=2;i<=now;i++){
		if(now%i==0){
			a[++cnt]=i;
			dfs(now/i);
			a[cnt--]=0;
		}
	}
}
signed main(){
	scanf("%lld",&n);
	for(int i=2;i<=1e3;i++)
		if(isprime(i)) prime[++tot]=i;
	dfs(n);
	printf("%lld\n",mx);
	return 0;
}
```
