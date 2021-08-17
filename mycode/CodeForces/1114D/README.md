```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[5010],f[5010][5010];
int main(){
	cin>>n; 
	for(int i=1;i<=n;i++) cin>>a[i];
	n=unique(a+1,a+n+1)-a-1;
	int ans=2e9;
	for(int len=2;len<=n;len++)
		for(int i=1,j=len;j<=n;i++,j++){
			if(a[i]==a[j]){
				f[i][j]=f[i+1][j-1]+1;
				// if(f[i+1][j]+1<f[i][j]) f[i][j]=f[i+1][j]+1;
				// if(f[i][j-1]+1<f[i][j]) f[i][j]=f[i][j-1]+1;
			}else{
				f[i][j]=f[i+1][j]+1;
				if(f[i][j-1]+1<f[i][j]) f[i][j]=f[i][j-1]+1;
			}
		}
	cout<<f[1][n]<<endl;
}
```

#### [返回上一页](https://coderbreakplus.github.io/website/mycode/CodeForces/)
