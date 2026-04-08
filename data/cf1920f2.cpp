// created time: 2026-04-08 15:33:20
#include<bits/stdc++.h>
#define inf 0x3f3f3f3f3f3f3f3fll
#define debug(x) cerr<<#x<<"="<<x<<endl
using namespace std;
using ll=long long;
using ld=long double;
using pli=pair<ll,int>;
using pi=pair<int,int>;
template<typename A>
using vc=vector<A>;
inline int read()
{
    int s=0,w=1;char ch;
    while((ch=getchar())>'9'||ch<'0') if(ch=='-') w=-1;
    while(ch>='0'&&ch<='9') s=s*10+ch-'0',ch=getchar();
    return s*w;
}
int dx[4]={1,-1,0,0};
int dy[4]={0,0,1,-1};
struct node
{
    int u,v;
    int w;
    node(int u=0,int v=0,int w=0):u(u),v(v),w(w){}
}e[1200001];
int fa[1200001][22];
int dep[1200001];
int w[1200001];
int f[1200001];
int dis[300005];
char s[300005];
int rx,ry;
int n,m,q;
int cntm;
int cnt;
inline void bfs()
{
    queue<int>que;
    memset(dis,0x3f,sizeof(dis));
    for(int i=0;i<n*m;i++) if(s[i]=='v') dis[i]=0,que.push(i);
    while(!que.empty())
    {
        int u=que.front();que.pop();
        int x=u/m,y=u%m;
        for(int i=0;i<4;i++)
        {
            int vx=x+dx[i],vy=y+dy[i];
            if(vx<0||vx>=n||vy<0||vy>=m) continue;
            int s=vx*m+vy;
            if(dis[s]>dis[u]+1) dis[s]=dis[u]+1,que.push(s);
        }
    }
}
inline int find(int num)
{
    if(f[num]==num) return num;
    return f[num]=find(f[num]);
}
inline int lca(int u,int v)
{
    if(dep[u]<dep[v]) swap(u,v);
    for(int i=20;i>=0;i--) if(dep[u]-(1<<i)>=dep[v]) u=fa[u][i];
    if(u==v) return u;
    for(int i=20;i>=0;i--) if(fa[u][i]!=fa[v][i]) u=fa[u][i],v=fa[v][i];
    return fa[u][0];
}
int main()
{
    n=read(),m=read(),q=read();
    for(int i=0;i<n;i++)
    {
        scanf("%s",s+i*m);
        for(int j=ry;j<=m;j++) if(s[i*m+j]=='#') rx=i,ry=j;
    }
    bfs();
    for(int i=0;i<n;i++) for(int j=0;j<m;j++) if(s[i*m+j]!='#')
    {
        int v=i*m+j;
        if(i&&s[v-m]!='#')
        {
            if(i==rx&&j>=ry)
            {
                e[++cntm]=node(v+n*m,v-m,min(dis[v],dis[v-m]));
                e[++cntm]=node(v,v-m+n*m,min(dis[v],dis[v-m]));
            }
            else
            {
                e[++cntm]=node(v,v-m,min(dis[v],dis[v-m]));
                e[++cntm]=node(v+n*m,v-m+n*m,min(dis[v],dis[v-m]));
            }
        }
        if(j&&s[v-1]!='#')
        {
            e[++cntm]=node(v,v-1,min(dis[v],dis[v-1]));
            e[++cntm]=node(v+n*m,v-1+n*m,min(dis[v],dis[v-1]));
        }
    }
    cnt=2*n*m-1;
    sort(e+1,e+cntm+1,[](node x,node y){ return x.w>y.w;});
    for(int i=0;i<=cnt;i++) f[i]=i;
    memset(fa,-1,sizeof(fa));

    for(int i=1;i<=cntm;i++)
    {
        int u=find(e[i].u),v=find(e[i].v);
        if(u==v) continue;
        cnt++,w[cnt]=e[i].w;
        f[u]=f[v]=f[cnt]=cnt;
        fa[u][0]=fa[v][0]=cnt;
    }
    for(int i=cnt;i>=0;i--)
    {
        for(int j=0;fa[i][j]>0;j++) fa[i][j+1]=fa[fa[i][j]][j];
        if(fa[i][0]>0) dep[i]=dep[fa[i][0]]+1;
    }
    for(int i=1;i<=q;i++)
    {
        int x=read()-1,y=read()-1;
        int v=x*m+y;
        printf("%d\n",w[lca(v,v+n*m)]);
    }
    return 0;
}