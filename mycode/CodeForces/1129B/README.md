[Prev](https://coderbreakplus.github.io/mycode/CodeForces/)

```cpp 
#include<bits/stdc++.h>
using namespace std;
int k;
int main(){
    cin>>k;
	int tmp=1000000-k%2000;
    puts("2000");
    for(int i=1;i<=1998;i++) cout<<0<<" ";
    cout<<(k+tmp)/2000-tmp<<" "<<tmp<<endl;
    return 0;
}
```
