```cpp
#include<bits/stdc++.h>
using namespace std;
#define int long long
int n,k,a[100010],f[45][100010],ans[100010];
signed main(){
    cin>>n>>k;
    for(int i=1;i<=n;i++){
        cin>>a[i];
        f[0][i]=a[i];
    }
    for(int i=1;i<=40;i++)
        for(int j=1;j<=n;j++)
            f[i][j]=f[i-1][f[i-1][j]];
    for(int i=1;i<=n;i++){
        int tmp=i;
        for(int j=40;j>=0;j--)
            if(k&(1ll<<j)) tmp=f[j][tmp];
        ans[tmp]=i;
    }
    for(int i=1;i<=n;i++) cout<<ans[i]<<" ";
    return 0;
}
```

#### [返回上一页](https://coderbreakplus.github.io/website/mycode/Luogu)
