```cpp
#include<cstdio>
#include<cstring>
#include<cmath>
#include<algorithm>
#include<iostream>
typedef long long ll;
typedef std::pair<int,int> P;
#define ls pos<<1
#define rs pos<<1|1
#define maxn 50

int n,k,number[maxn];
char str[maxn];
struct node {
	int len;
	int a[4010];
} num[maxn][maxn],dp[maxn][10];

bool vis[maxn][10];

inline node operator* (node A,node B) {
	int lena=A.len,lenb=B.len;
	int lenc=lena+lenb,x=0;
	node C;
	memset(C.a,0,sizeof(C.a));
	for(register int i=1; i<=lena; i++) {
		x=0;
		for(register int j=1; j<=lenb; j++) {
			C.a[i+j-1]=(C.a[i+j-1]+A.a[i]*B.a[j]+x);
			x=C.a[i+j-1]/10;
			C.a[i+j-1]%=10;
		}
		C.a[i+lenb]+=x;
	}
	while(C.a[lenc]==0&&lenc>1) lenc--;
	C.len=lenc;
	return C;
}
inline bool operator< (node A,node B) {
	if(A.len!=B.len) return A.len<B.len;
	for(register int i=A.len; i>=1; i--) {
		if(A.a[i]!=B.a[i]) return A.a[i]<B.a[i];
	}
	return false;
}
inline node maxx(node A,node B) {
	return A<B?B:A;
}
inline void init() {
	for(register int i=1; i<=n; i++) number[i]=str[i-1]-'0';
	for(register int i=1; i<=n; i++)
		for(register int j=i; j<=n; j++) {
			num[i][j].len=j-i+1;
			for(register int k=j,l=1; k>=i; k--,l++)
				num[i][j].a[l]=number[k];
		}
}
inline void print(node A) {
	for(register int i=A.len; i>=1; i--)
		printf("%d",A.a[i]);
	puts("");
}
node DFS(int r,int kk) {
	if(r==1&&kk>0) {
		node tmp;
		memset(tmp.a,0,sizeof(tmp.a));
		tmp.len=0;
		return tmp;
	}
	if(kk==0) return num[1][r];
	if(vis[r][kk]) return dp[r][kk];
	node Ans;
	memset(Ans.a,0,sizeof(Ans.a));
	Ans.a[1]=1;
	Ans.len=1;
	int tr;
	for(register int i=r-1; i>=kk; i--) {
		node tmp;
		memset(tmp.a,0,sizeof(tmp.a));
		tmp=DFS(i,kk-1);
		Ans=maxx(Ans,tmp*num[i+1][r]);
	}
	vis[r][kk]=true;
	dp[r][kk]=Ans;
	return Ans;
}
signed main() {
	scanf("%d%d%s",&n,&k,str);
	init();
	print(DFS(n,k));
	return 0;
}
```

#### [返回上一页](https://coderbreakplus.github.io/website/mycode/Luogu/)
