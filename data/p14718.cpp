// created time: 2026-05-12

#include<bits/stdc++.h>
#define lc (u<<1)
#define rc (lc|1)
#define mid ((l+r)>>1)
#define Lc lc,l,mid
#define Rc rc,mid+1,r
using namespace std;
const int N=2010;
const int M=N*(N+1)/2;
struct SG
{
    short w[N<<2],p[N<<2],tag[N<<2];
    void pushup(int u) {w[u]=min(w[lc],w[rc]),p[u]=p[w[u]==w[lc]?lc:rc];}
    void pt(int u,int x) {tag[u]+=x,w[u]+=x;}
    void pushdown(int u) {if(tag[u]) pt(lc,tag[u]),pt(rc,tag[u]),tag[u]=0;}
    void build(int u,int l,int r,int R)
    {
        if(l==r) {w[u]=R-l+1,p[u]=l; return;}
        build(Lc,R),build(Rc,R),pushup(u);
    }
    void update(int u,int l,int r,int R)
    {
        if(r<=R) {pt(u,-1); return;}
        pushdown(u);
        if(R<=mid) update(Lc,R);
        else pt(lc,-1),update(Rc,R);
        pushup(u);
    }
}T[N];
int n,m,cc,lim[N]; short l[M],r[M]; long long res;
struct nod{int x,l,r;}a[N];
bool cmp(nod A,nod B) {return A.l<B.l;}
priority_queue <pair<int,int> > Q;
void ini()
{
    lim[n+1]=n+1;
    for(int i=n;i;i--) lim[i]=min(lim[i+1],T[i].w[1]?n+1:T[i].p[1]);
}
void solve(int tn,vector<vector<int>> A,long long& answer,vector<int>& solution)
{
    n=tn,m=n*(n+1)/2;
    for(int i=1;i<=n;i++)
    {
        T[i].build(1,1,i,i);
        for(int j=1,x;j<=i;j++) x=A[i-1][j-1],l[x]=j,r[x]=i;
    }
    ini();
    for(int i=m;i;i--) if(lim[r[i]]>l[i]) 
    {
        for(int j=r[i];j<=n;j++) T[j].update(1,1,j,l[i]);
        ini(),res+=i,a[++cc]={i,l[i],r[i]};
    }
    answer=res,sort(a+1,a+1+cc,cmp),solution.clear();
    for(int i=1,tp=1;i<=n;i++)
    {
        while(tp<=cc&&a[tp].l==i) Q.push({-a[tp].r,a[tp].x}),tp++;
        solution.push_back(Q.top().second),Q.pop();
    }
}
