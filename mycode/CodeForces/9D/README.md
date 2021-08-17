```cpp
#include<iostream>
#include<cstring>
using namespace std;
#define int unsigned long long
int n,h,a[40][40]; bool vis[40][40];
int dfs(int x,int y){
    if(x==0) return 1;
    if(y==0) return 0;
    if(vis[x][y]) return a[x][y];
    a[x][y]=0; vis[x][y]=true;
    if(x>1 && y==1) return 0;
    for(int i=0;i<x;i++)
        a[x][y]+=dfs(i,y-1)*dfs(x-i-1,y-1);
    return a[x][y];
}
signed main(){
    cin>>n>>h;
    cout<<dfs(n,n)-dfs(n,h-1);
}
```

#### [返回上一页](https://coderbreakplus.github.io/website/mycode/CodeForces/)
