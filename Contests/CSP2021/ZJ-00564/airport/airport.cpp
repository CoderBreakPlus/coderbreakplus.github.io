#include<cstdio>
#include<cstring>
#include<algorithm>
#include<queue>
using namespace std;
int n,m1,m2,nr[100005];
struct Node{
	int l,r;
}a[100005],b[100005];
bool cmp(Node A,Node B){
	return A.l<B.l;
}
int count(int x){
	priority_queue<int,vector<int>,greater<int> >Q;
	for(int i=1;i<=x;i++) Q.push(0);
	int ans=0;
	for(int i=1;i<=m1;i++){
		if(Q.empty()) break;
		int tmp=Q.top(); Q.pop();
		if(!(a[i].l>tmp)) Q.push(tmp);
		else{
			ans++; Q.push(a[i].r);
		}
	}
	while(!Q.empty()) Q.pop();
	for(int i=1;i<=n-x;i++) Q.push(0);
	for(int i=1;i<=m2;i++){
		if(Q.empty()) break;
		int tmp=Q.top(); Q.pop();
		if(!(b[i].l>tmp)) Q.push(tmp);
		else{
			ans++; Q.push(b[i].r);
		}
	}
	return ans;
}
int main(){
	freopen("airport.in","r",stdin);
	freopen("airport.out","w",stdout);
	scanf("%d%d%d",&n,&m1,&m2);
	for(int i=1;i<=m1;i++)
		scanf("%d%d",&a[i].l,&a[i].r);
	for(int i=1;i<=m2;i++)
		scanf("%d%d",&b[i].l,&b[i].r);
	sort(a+1,a+m1+1,cmp); sort(b+1,b+m2+1,cmp);
	int ans=count(n);
	for(int i=0;i<n;i++){
		int tmp=count(i);
		if(tmp>ans) ans=tmp;
	}
	printf("%d\n",ans);
	return 0;
} 
