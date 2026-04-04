#include<bits/stdc++.h>
using namespace std;
struct node{int len,fa,s[10];}a[1000005];
int n,lst=1,cnt=1;long long ans[1000005][10];
inline void ins(int c)
{
	int p=lst,np=lst=++cnt;a[np].len=a[p].len+1;
	for(;p&&!a[p].s[c];p=a[p].fa) a[p].s[c]=np;
	if(!p) return(void)(a[np].fa=1);
	int q=a[p].s[c];
	if(a[q].len==a[p].len+1) return(void)(a[np].fa=q);
	int nq=++cnt;a[nq]=a[q],a[nq].len=a[p].len+1,a[q].fa=a[np].fa=nq;
	for(;p&&a[p].s[c]==q;p=a[p].fa) a[p].s[c]=nq;
}
inline long long dfs(int x,int w)
{
	if(ans[x][w]) return ans[x][w];
	for(int i=1;i<=9;i++){
		if(i==w)continue;
		int y=x;
		for(int j=1;j<=i;j++){
			y=a[y].s[i];
			if(!y)break;
		}
		if(y)ans[x][w]+=dfs(y,i)+1;
	}
	return ans[x][w];
}
int main()
{
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	scanf("%d",&n),memset(ans,0,sizeof(ans));
	for(int i=1;i<=n;i++) {
		int x;scanf("%d",&x);
		ins(x);
	}
	printf("%lld\n",dfs(1,0));
	return 0;
}