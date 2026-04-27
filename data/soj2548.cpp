// created time: 2026-04-23
// http://10.49.18.71/problem/2548
#include<bits/stdc++.h>
using namespace std;
#define fi first
#define se second
#define rep(i,l,r) for(int i=(l); i<=(r); ++i)
#define rep_(i,l,r) for(int i=(l); i>=(r); --i)
typedef unsigned long long ull;
constexpr int N=3000300,M=1<<19;
constexpr ull inf=1ll<<40;
int n,q; pair<int,ull> b[N],tr[N];
char buf[M],*p1=buf,*p2=buf;
#define getchar() ((p1==p2)&&(p1=buf,p2=p1+fread(buf,1,M,stdin)),p1==p2? 0:*p1++)
inline ull rd()
{
	ull t=0; char c=getchar();
	while(~c&16) c=getchar();
	while(c&16) t=t*10+(c^48),c=getchar();
	return t;
}
void Solve()
{
	rd(),n=rd(),q=rd();
	ull z; rep(i,1,n) z=rd(),b[i].fi=__builtin_clzll(z),b[i].se=__builtin_clzll(~(z<<b[i].fi));
	rep(i,1,n) tr[i].fi=130-(b[i].fi<<1),tr[i].se=inf>>b[i].se;
	rep(j,0,21) for(int p=2<<j; p<=n; p+=2<<j) tr[p].fi+=tr[p-(1<<j)].fi,tr[p].se+=tr[p-(1<<j)].se;
	while(q--)
	{
		if(rd()==1)
		{
			int l=rd(),r=rd(),op=0,s=-1; ull tp=0;
			for( ; r; r^=r&-r) s+=tr[r].fi,tp+=tr[r].se;
			for(--l; l; l^=l&-l) s-=tr[l].fi,tp-=tr[l].se;
			if((tp&-tp)>=(1ll<<39)) tp-=(1ll<<39);
			printf("%d\n",s-((tp>>39)<<1));
		}
		else
		{
			int x=rd(); ull z=rd();
			int bb=__builtin_clzll(z),cc=__builtin_clzll(~(z<<bb));
			int z1=b[x].fi-bb<<1; ull z2=(inf>>cc)-(inf>>b[x].se);
			for(int p=x; p<=n; p+=p&-p) tr[p].fi+=z1,tr[p].se+=z2;
			b[x].fi=bb,b[x].se=cc;
		}
	}
}
int main()
{
	int T=1; while(T--) Solve();
	return 0;
}