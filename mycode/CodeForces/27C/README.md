```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a[100010],mx1,mx2,mn1,mn2;
int lmn[100010],lmx[100010],rmn[100010],rmx[100010];
int main(){
    cin>>n;
    memset(lmn,-1,sizeof(lmn));
    memset(lmx,-1,sizeof(lmx));
    memset(rmn,-1,sizeof(rmn));
    memset(rmx,-1,sizeof(rmx));
    for(int i=1;i<=n;i++) cin>>a[i],a[i]+=(1e6);
    for(int i=1;i<=n;i++){
        if(a[mx1]>a[i]) lmx[i]=mx1; 
        else mx1=i;
        if(a[mn1]<a[i] && mn1!=0) lmn[i]=mn1;
        else mn1=i;
    }
    for(int i=n;i>=1;i--){
        if(a[mx2]>a[i]) rmx[i]=mx2;
        else mx2=i;
        if(a[mn2]<a[i] && mn2!=0) rmn[i]=mn2;
        else mn2=i;
        // cout<<mx2<<" "<<mn2<<endl;
    }
    for(int i=2;i<n;i++){
        if(lmn[i]!=-1 && rmn[i]!=-1){
            cout<<3<<endl;
            cout<<lmn[i]<<" "<<i<<" "<<rmn[i]<<endl;
            return 0;
        }
        if(lmx[i]!=-1 && rmx[i]!=-1){
            cout<<3<<endl;
            cout<<lmx[i]<<" "<<i<<" "<<rmx[i]<<endl;
            return 0;
        }
    }
    cout<<0<<endl;
}// NB 构造题
```

#### [返回上一页](https://coderbreakplus.github.io/website/mycode/CodeForces/)
