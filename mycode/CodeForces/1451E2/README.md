[Prev](https://coderbreakplus.github.io/mycode/CodeForces/)

```cpp 
#include<bits/stdc++.h>
using namespace std;
int n,c[1000010],they;
int use[1000010],a[1000010];
inline void doit(){
	for(int i=2;i<=n;i++)
		a[i]=c[i]^a[1];
}
int main(){
	cin>>n;
	for(int i=2;i<=n;i++){
		cout<<"XOR 1 "<<i<<endl;
		fflush(stdout);
		cin>>c[i];
	}
	for(int i=1;i<=n;i++){
		if(use[c[i]]){
			cout<<"AND "<<use[c[i]]<<" "<<i<<endl;
			fflush(stdout);
			cin>>they;
			a[1]=c[i]^they;
			doit();
			cout<<"! ";
			for(int i=1;i<=n;i++) cout<<a[i]<<" ";
			cout<<endl; return 0;
		}
		use[c[i]]=i;
	}
	int id1=0,id2=0,tmp,ans;
	for(int i=1;i<=n;i++)
		if(c[i]==1) id1=i;
		else if(c[i]==n-2) id2=i;
	cout<<"AND 1 "<<id1<<endl;
	fflush(stdout);
	cin>>tmp; ans=((tmp>>1)<<1);
	cout<<"AND 1 "<<id2<<endl;
	fflush(stdout);
	cin>>tmp; ans+=(tmp&1);
	a[1]=ans;
	doit(); cout<<"! ";
	for(int i=1;i<=n;i++) cout<<a[i]<<" ";
			cout<<endl; return 0;
}
```
