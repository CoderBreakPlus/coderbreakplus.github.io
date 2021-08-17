```cpp
#include<cstdio>
using namespace std;

int d(int x){
    return (x%9>0)?(x%9):9;
}
int cnt[1000010];
long long ans=0;
int main(){
    int n; scanf("%d",&n);
    for(int i=1;i<=n;i++) cnt[d(i)]++;
    for(int i=1;i<=9;i++)
        for(int j=1;j<=9;j++)
            for(int k=1;k<=9;k++){
                if(i*j%9 == k%9){
                    ans+=1ll*cnt[i]*cnt[j]*cnt[k];
                }
            }
    for(int l=1,r;l<=n;l=r+1){
        r=n;
        if(n/(n/l)<r) r=n/(n/l);
        ans-=1ll*(n/l)*(r-l+1);
    }
    printf("%lld\n",ans);
}// 感觉还不太理解……
```

#### [返回上一页](https://coderbreakplus.github.io/website/mycode/CodeForces/)
