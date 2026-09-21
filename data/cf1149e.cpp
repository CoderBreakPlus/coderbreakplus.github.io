// created time: 2026-09-21 09:53:46
#include<iostream>
#include<cstdio>
#include<queue>
#include<map>
#define maxn 200005
#define ll long long
using namespace std;
int n,m,u,v,deg[maxn]; ll mmax,a[maxn],sg[maxn],xxor[maxn]; queue<int> q; map<int,int> mp[maxn];
struct node{int to,nex;}g[maxn],g2[maxn]; int head[maxn],head2[maxn],cnt=0,cnt2=0;
void add(int from,int to){g[++cnt].to=to; g[cnt].nex=head[from]; head[from]=cnt;}
void add2(int from,int to){g2[++cnt2].to=to; g2[cnt2].nex=head2[from]; head2[from]=cnt2;}
int main(){
	scanf("%d%d",&n,&m); for(int i=1;i<=n;i++) scanf("%lld",&a[i]);
	for(int i=1;i<=m;i++){scanf("%d%d",&u,&v); add(v,u); add2(u,v); deg[u]++;}
        for(int i=1;i<=n;i++) if(deg[i]==0) q.push(i);
	while(!q.empty()){
		int top=q.front(); q.pop(); for(int i=0;;i++) if(!mp[top][i]){sg[top]=i; break;}
		for(int i=head[top];i;i=g[i].nex)
                        {deg[g[i].to]--; mp[g[i].to][sg[top]]=1; if(!deg[g[i].to]) q.push(g[i].to);}
	}
	for(int i=1;i<=n;i++){xxor[sg[i]]^=a[i]; mmax=max(mmax,sg[i]);}
	for(int i=mmax;i>=0;i--){
		if(xxor[i]){
			for(int j=1;j<=n;j++) if(sg[j]==i&&((a[j]^xxor[i])<a[j])){
				a[j]^=xxor[i]; xxor[i]=0;
				for(int k=head2[j];k;k=g2[k].nex) if(xxor[sg[g2[k].to]])
					{a[g2[k].to]^=xxor[sg[g2[k].to]]; xxor[sg[g2[k].to]]=0;} break;
			}
			printf("WIN\n"); for(int i=1;i<=n;i++) printf("%lld ",a[i]); return 0;
		}
		if(i==0){printf("LOSE"); return 0;}
	}
	return 0;
}
