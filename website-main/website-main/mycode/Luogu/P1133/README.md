```cpp
#include<cstdio>
using namespace std;
int n,money[100010][3],f[100010][4][2];
inline int read(){
    int x=0;char ch=getchar();
    while(ch<'0'||ch>'9') ch=getchar();
    while(ch>='0'&&ch<='9') {x=x*10+ch-'0';ch=getchar();}
    return x;
}
int maxx(int a,int b){
    return a>b?a:b;
}
int main(){
    n=read();
    for(int i=1;i<=n;i++)
    for(int j=0;j<3;j++) money[i][j]=read();
    for(int i=2;i<=n;i++){
        f[i][1][0]=maxx(f[i-1][3][1],f[i-1][2][1])+money[i][0];
        f[i][2][0]=f[i-1][3][1]+money[i][1];
        f[i][2][1]=f[i-1][1][0]+money[i][1];
        f[i][3][1]=maxx(f[i-1][1][0],f[i-1][2][0])+money[i][2];
    }
    f[1][1][0]=maxx(f[n][3][1],f[n][2][1])+money[1][0];
    f[1][2][0]=f[n][3][1]+money[1][1];
    f[1][2][1]=f[n][1][0]+money[1][1];
    f[1][3][1]=maxx(f[n][1][0],f[n][2][0])+money[1][2];
    printf("%d\n",maxx(maxx(f[1][1][0],f[1][2][0]),maxx(f[1][2][1],f[1][3][1])));
    return 0;
}
```

#### [返回上一页](https://coderbreakplus.github.io/website/mycode/Luogu)
