// created time: 2026-07-29 18:44:26
// very smart problem
// [1, n] \ [dfn[x], out[x]]

#include<bits/stdc++.h>
using namespace std;
typedef long long ll;

int n,dfn[100005],out[100005],seq[100005],tim;
vector<int>E[100005];
vector<int>tr[400005];
void dfs(int x){
	dfn[x]=++tim,seq[tim]=x;
	for(int y:E[x])dfs(y);
	out[x]=tim;
}
void insert(int l,int r,int x,int p){
	int mid=(l+r)>>1;
	if((l==r)||(dfn[x]<=mid&&mid<out[x])){
		tr[p].push_back(x);
		return;
	}
	if(out[x]<=mid)insert(l,mid,x,p<<1);
	else insert(mid+1,r,x,p<<1|1);
}
void dfs2(int x){
	insert(1,n,x,1);
	for(int y:E[x])dfs2(y);
}
void add(int x){ printf("+%d",seq[x]); }
void del(){ printf("-"); }
void solved(int x){ printf("=%d",x); }
void solve(int l,int r,int p){
	int L=l,R=r;
	for(int x:tr[p]){
		while(L<dfn[x])add(L++);while(R>out[x])add(R--);
		solved(x);
	}
	if(l==r)return;
	int mid=(l+r)>>1;
	while(L>l)del(),L--;
	while(R<r)del(),R++;
	
	for(int i=mid+1;i<=r;i++)add(i); solve(l,mid,p<<1);
	for(int i=mid+1;i<=r;i++)del();
	
	for(int i=l;i<=mid;i++)add(i); solve(mid+1,r,p<<1|1);
	for(int i=l;i<=mid;i++)del();
}
void procedure(){
	tim=0;
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<=4*n;i++)tr[i].clear();
	for(int i=2;i<=n;i++){
		int x;scanf("%d",&x);
		E[x].push_back(i);
	}
	dfs(1);dfs2(1);
	solve(1,n,1);
	puts("!");
}
int main(){
	while(~scanf("%d",&n))procedure();
}