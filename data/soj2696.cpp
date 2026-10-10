// created time: 2026-10-10
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define pb emplace_back
inline ll read(){
	ll x=0,f=1;char ch=getchar();
	while(ch>'9'||ch<'0'){if(ch=='-')f=-1;ch=getchar();}
	while(ch>='0'&&ch<='9')x=x*10+ch-'0',ch=getchar();
	return x*f;
}
const int N=500005;
int n,m,vis[N],col[N],bel[N],st[N],cnt[N];
vector<int>E[N],R[N],ord,part[N];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		E[x].pb(y);R[y].pb(x);
	}
	vector<pair<int,int>>stk;
	for(int s=1;s<=n;s++)if(!vis[s]){
		vis[s]=1;stk.pb(s,0);
		while(!stk.empty()){
			auto &[x,i]=stk.back();
			if(i==(int)E[x].size()){
				ord.pb(x);
				stk.pop_back();
				continue;
			}
			int y=E[x][i++];
			if(!vis[y])vis[y]=1,stk.pb(y,0);
		}
	}
	int cc=0;
	vector<int>q;
	for(int i=n-1;i>=0;i--){
		int s=ord[i];
		if(bel[s])continue;
		++cc;bel[s]=cc;
		q.pb(s);
		while(!q.empty()){
			int x=q.back();q.pop_back();
			part[cc].pb(x);
			for(int y:R[x])if(!bel[y]){
				bel[y]=cc;
				col[y]=col[x]^1;
				q.pb(y);
			}
		}
	}
	for(int c=cc;c>=1;c--){
		for(int x:part[c])
			for(int y:E[x])
				if(bel[y]!=c&&st[y]==1)st[x]=2;
		for(int x:part[c])
			if(col[x]&&!st[x])st[x]=1;
		queue<int>que;
		for(int x:part[c])if(!col[x]){
			for(int y:E[x])
				if(bel[y]==c&&st[y]==1)cnt[x]++;
			if(!cnt[x]&&!st[x])que.push(x);
		}
		while(!que.empty()){
			int x=que.front();que.pop();
			st[x]=1;
			for(int y:R[x])if(bel[y]==c&&st[y]==1){
				st[y]=2;
				for(int z:R[y])
					if(bel[z]==c&&!col[z]&&!st[z])
						if(!--cnt[z])que.push(z);
			}
		}
	}
	vector<int>ans;
	for(int i=1;i<=n;i++)
		if(st[i]==1)ans.pb(i);
	printf("%d\n",(int)ans.size());
	for(int x:ans)printf("%d ",x);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("graph.in","r",stdin));
		assert(freopen("graph.out","w",stdout));
	#endif
	procedure();
}
