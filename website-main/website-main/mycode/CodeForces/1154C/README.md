```cpp
#include<bits/stdc++.h>
using namespace std;
int a,b,c,a1,b1,c1;
void minus_(int week){
    if(week==1||week==4||week==7) a1--;
    else if(week==2||week==6) b1--;
    else c1--;
}
int check(int start){
    a1=a,b1=b,c1=c;
    int ans=7-start+1;
    for(int i=start;i<=7;i++){
        minus_((i-1)%7+1);
        if(a1<0 ||b1<0 || c1<0) return i-start;
    }
    int canmi=min(min(a1/3,b1/2),c1/2);
    ans+=canmi*7;
    a1-=canmi*3,b1-=canmi*2,c1-=canmi*2;
    for(int i=1;;i++){
        minus_((i-1)%7+1);
        if(a1<0 || b1<0 || c1<0) return ans;
        ans++;
    }
}
int main(){
    cin>>a>>b>>c;
    int ans=0;
    for(int i=1;i<=7;i++) ans=max(ans,check(i));
    cout<<ans<<endl;
}
```

#### [返回上一页](https://coderbreakplus.github.io/website/mycode/CodeForces/)
