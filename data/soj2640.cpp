// created time: 2026-08-16
#include<vector>
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const int mod = 998244353;
inline void addmod(int &x){ if(x>=mod)x-=mod; }
int c,n,m,a[305][305],ia[305][305],vis[305],cur[305];
vector<int>p,q,r;

int ans;

bool f0[305][305][305],f1[305][305][305];
int dp[305][305][305];

void dfs(int x){
	if(x==n){
		addmod(ans+=1);
		return;
	}
	if(*min_element(r.begin(),r.end())){
		addmod(dp[r[0]][p[0]][q[0]]+=1);
		return;
	}
	for(int i=1;i<=n;i++){
		if(vis[i]) continue;
		vector<int>P=p,Q=q,R=r;
		
		bool flg=1;
		for(int j=0;j<m;j++){
			if(r[j]) flg&=vis[a[j][ia[j][i]-1]],(ia[j][i]>=r[j]?++q[j]:++p[j]);
			else{
				if(!vis[a[j][ia[j][i]-1]]) q[j]=r[j]=ia[j][i];
				else ++p[j];
			}
		}
		if(flg){
			vis[i]=1,cur[x+1]=i,dfs(x+1);
			vis[i]=0;
		}		
		p=P,q=Q,r=R;
	}
}
int qz[305][305];
int b[305];

int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	scanf("%d%d%d",&c,&n,&m);
	p.resize(m,0),q.resize(m,0),r.resize(m,0);
	vis[n+1]=1;
	for(int i=0;i<m;i++){
		for(int j=1;j<=n;j++)
			scanf("%d",&a[i][j]),ia[i][a[i][j]]=j;
		a[i][0]=n+1;
	}
	for(int i=0;i<m;i++) qz[0][a[i][1]]++;
	for(int r=1;r<=n;r++){
		for(int z=1;z<=n;z++) qz[r][z]=qz[r-1][z];
		for(int i=0;i<m;i++){
			int pos=ia[i][a[0][r]]+1;
			if(pos<=n) qz[r][a[i][pos]]++;
		}
	}
	for(int z=2;z<=n;z++){
		for(int i=1;i<=n;i++)b[i]=0;
		for(int y=z-1;y<=n;y++){
			if(y>=z)
				for(int i=0;i<m;i++){
					int pos=ia[i][a[0][y]]+1;
					if(pos<=n) b[a[i][pos]]++;
				}
			for(int x=0;x<z;x++){
				bool f0=(x+1<z),f1=(y<n);
				int v0=a[0][x+1],v1=a[0][y+1];
				f0&=(qz[x][v0]+b[v0]==m);
				f1&=(qz[x][v1]+b[v1]==m);
				::f0[z][x][y]=f0;
				::f1[z][x][y]=f1;
			}
		}
	}
	dfs(0);
	for(int z=2;z<=n;z++){
		for(int x=0;x<z;x++)for(int y=z-1;y<=n;y++){
			if(f0[z][x][y])addmod(dp[z][x+1][y]+=dp[z][x][y]);
			if(f1[z][x][y])addmod(dp[z][x][y+1]+=dp[z][x][y]);
		}
		addmod(ans+=dp[z][z-1][n]);
	}
	printf("%d\n",ans);
}