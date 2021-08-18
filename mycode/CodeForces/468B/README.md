[Prev](https://coderbreakplus.github.io/mycode/CodeForces/)

```cpp
#include<bits/stdc++.h>
using namespace std;
int n,a,b,p[100010],col[100010],colt;
int must[100010],vis[100010]; vector<int>vec[100010];
int ans[100010];
map<int,int>mp;
inline int dfs(int x){
	vec[colt].push_back(x);
	vis[x]=true;
	if(!mp.count(a-p[x])) must[x]=2;
	else if(!vis[mp[a-p[x]]]) dfs(mp[a-p[x]]);
	
	if(!mp.count(b-p[x])){
		if(must[x]){
			puts("NO");
			exit(0);
		}else must[x]=1;
	}else if(!vis[mp[b-p[x]]]) dfs(mp[b-p[x]]);
}
int main(){
	cin>>n>>a>>b;
	for(int i=1;i<=n;i++) cin>>p[i],mp[p[i]]=i;
	for(int i=1;i<=n;i++){
		if(!vis[i]){
			colt++;
			dfs(i);
		}
	}
	for(int i=1;i<=colt;i++){
		int len=vec[i].size();
		for(int j=0;j<len;j++){
			if(must[vec[i][j]]){
				if(col[i] && col[i]!=must[vec[i][j]]){
					puts("NO");
					exit(0);
				}
				col[i]=must[vec[i][j]];
			}
		}
	}
	for(int i=1;i<=colt;i++){
		int nowcol=col[i],len=vec[i].size();
		if(nowcol==0) nowcol=1;
		for(int j=0;j<len;j++) ans[vec[i][j]]=nowcol;
	}
	puts("YES");
	for(int i=1;i<=n;i++) cout<<ans[i]-1<<" ";
	return 0;
} 
```
