// created time: 2026-10-18
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb emplace_back
inline ll read(){ ll x;scanf("%lld",&x);return x; }

int n,N,sz[1<<20],ans;
vector<int>E[1<<20];

void dfs(int x,int fa){
	ll tot=(ll)(N-1)*(N-2)/2;
	sz[x]=!!x;
	for(int y:E[x])if(y!=fa){
		dfs(y,x);
		sz[x]+=sz[y];
		tot-=(ll)sz[y]*(sz[y]-1)/2;
	}
	ll w=N-1-sz[x];
	tot-=(ll)w*(w-1)/2;
	if(x && (tot&1)) ans^=x;
}
void procedure(){
	n=read(),N=1<<n;
	for(int i=0;i<(1<<n)-1;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(0,-1);
	for(int i=1;i<(1<<n);i++)ans^=i;
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("tree.in","r",stdin));
		assert(freopen("tree.out","w",stdout));
	#endif
	procedure();
} 