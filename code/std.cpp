#include<bits/stdc++.h>
#define maxn 100010
#define eps 1e-12
using namespace std;
typedef long long ll;
template<typename T> inline void read(T &x)
{
    x=0;char c=getchar();bool flag=false;
    while(!isdigit(c)){if(c=='-')flag=true;c=getchar();}
    while(isdigit(c)){x=(x<<1)+(x<<3)+(c^48);c=getchar();}
    if(flag)x=-x;
}
int n,tot,top;
ll t,now;
double v;
struct matrix
{
    double a[5][5];
}f,g[36];
matrix operator *(const matrix &x,const matrix &y)
{
    matrix z;
    memset(z.a,0,sizeof(z.a));
    for(int k=1;k<=3;++k)
        for(int i=1;i<=3;++i)
            for(int j=1;j<=3;++j)
                z.a[i][j]+=x.a[i][k]*y.a[k][j];
    return z;
}
int sgn(double x)
{
    if(fabs(x)<eps) return 0;
    return x>0?1:-1;
}
struct line
{
    double k,b;
}l[maxn],st[maxn];
bool cmp(const line &x,const line &y)
{
    if(!sgn(x.k-y.k)) return x.b<y.b;
    return x.k<y.k;
}
double get(line x,line y)
{
    return (x.b-y.b)/(y.k-x.k);
}
int main()
{
    #ifdef LOCAL
        assert(freopen("test.in","r",stdin));
        assert(freopen("test.out","w",stdout));
    #endif
    read(n),read(t);
    for(int i=1;i<=n;++i)
    {
        double a,b,p;
        scanf("%lf%lf%lf",&a,&b,&p);
        l[i]={p,p*a},v=max(v,b*p);
    }
    sort(l+1,l+n+1,cmp);
    for(int i=1;i<=n;++i)
        if(sgn(l[i].k-l[i+1].k))
            l[++tot]=l[i];
    for(int i=1;i<=tot;++i)
    {
        while(top>1&&sgn(get(st[top],st[top-1])-get(l[i],st[top-1]))>=0) top--;
        st[++top]=l[i];
    }
    f.a[1][3]=1;
    for(int i=1;i<=top;++i)
    {
        double pos=now*v-f.a[1][1];
        while(i<top&&sgn(pos-get(st[i],st[i+1]))>=0) i++;
        if(i<top) pos=get(st[i],st[i+1]);
        g[0].a[1][2]=g[0].a[1][3]=g[0].a[2][3]=0;
        g[0].a[2][2]=g[0].a[3][2]=g[0].a[3][3]=1;
        g[0].a[1][1]=1-st[i].k,g[0].a[2][1]=st[i].k*v,g[0].a[3][1]=st[i].b;
        for(int j=1;j<=34;++j) g[j]=g[j-1]*g[j-1];
        for(int j=34;j>=0;--j)
            if(now+(1ll<<j)<t)
                if(i==top||sgn(pos-(now+(1ll<<j))*v+(f*g[j]).a[1][1])>=0)
                    f=f*g[j],now+=1ll<<j;
        f=f*g[0],now++;
        if(now==t) break;
    }
    printf("%.10lf",f.a[1][1]);
    return 0;
}
