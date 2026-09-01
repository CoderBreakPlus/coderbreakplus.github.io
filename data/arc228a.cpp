// created time: 2026-09-01
#include<bits/stdc++.h>
#define int long long 
using namespace std;
const int mod=998244353;
inline void Add(int &x,int y){((x+=y)>=mod)?(x-=mod):0;}
int tf[505][505][2],tg[505][505][2],tmp[505][505];
int f[505][505],g[505][505];
int p[505],q[505],n,m,a[505];
bool flag[505];
signed main()
{
	ios::sync_with_stdio(0);
	cin.tie(0);
	cout.tie(0);
	cin>>n>>m;
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		p[x]=i;
	}
	for(int i=1;i<=n;i++)
	{
		int x;
		cin>>x;
		q[x]=i;
	}
	for(int i=1;i<=n;i++)
		a[p[i]]=q[i];
	f[0][0]=1;
	for(int i=1;i<=n;i++)
	{
		if(flag[i])
			continue;
		int c=1,x=a[i];
		flag[i]=1;
		while(x!=i)
			c++,flag[x]=1,x=a[x];
		for(int j=0;j<=n;j++)
			for(int k=0;j+k<=n;k++)
				tmp[j][k]=tg[j][k][0]=tg[j][k][1]=0;
		for(int j=0;j<=n;j++)
			for(int k=0;j+k<=n;k++)
				tf[j][k][0]=0,tf[j][k][1]=f[j][k];
		for(int j=2;j<=c;j++)
		{
			for(int x=0;x<=n;x++)
				for(int y=0;x+y<=n;y++)
					if(tf[x][y][0]||tf[x][y][1])
						Add(tg[x+1][y][1],tf[x][y][0]),Add(tg[x][y+1][1],tf[x][y][1]),
						Add(tg[x][y][0],tf[x][y][0]),Add(tg[x][y][0],tf[x][y][1]);
			for(int x=0;x<=n;x++)
				for(int y=0;x+y<=n;y++)
					tf[x][y][0]=tg[x][y][0],tf[x][y][1]=tg[x][y][1],tg[x][y][0]=tg[x][y][1]=0;
		}
		for(int x=0;x<=n;x++)
			for(int y=0;x+y<=n;y++)
				Add(tmp[x+1][y],tf[x][y][0]),Add(tmp[x][y+1],tf[x][y][1]);
		for(int j=0;j<=n;j++)
			for(int k=0;j+k<=n;k++)
				tf[j][k][0]=f[j][k],tf[j][k][1]=0;
		for(int j=2;j<=c;j++)
		{
			for(int x=0;x<=n;x++)
				for(int y=0;x+y<=n;y++)
					if(tf[x][y][0]||tf[x][y][1])
						Add(tg[x+1][y][1],tf[x][y][0]),Add(tg[x][y+1][1],tf[x][y][1]),
						Add(tg[x][y][0],tf[x][y][0]),Add(tg[x][y][0],tf[x][y][1]);
			for(int x=0;x<=n;x++)
				for(int y=0;x+y<=n;y++)
					tf[x][y][0]=tg[x][y][0],tf[x][y][1]=tg[x][y][1],tg[x][y][0]=tg[x][y][1]=0;
		}
		for(int x=0;x<=n;x++)
			for(int y=0;x+y<=n;y++)
				Add(tmp[x][y],tf[x][y][0]),Add(tmp[x][y],tf[x][y][1]);
		for(int x=0;x<=n;x++)
			for(int y=0;x+y<=n;y++)
				f[x][y]=tmp[x][y];
	}
	for(int i=1;i<=m;i++)
	{
		for(int j=0;j<=n;j++)
			for(int k=0;j+k<=n;k++)
			{
				if(!f[j][k])
					continue;
				int x=n-2*j-k,y=n-j-k-x;
				Add(g[j][k],(((j-1)*j/2+(k-1)*k/2+(x-1)*x/2+(y-1)*y/2+j*k+j*x+k*y+x*y)*2+j+y)*f[j][k]%mod);
				if(k&&x)
					Add(g[j+1][k-1],k*x*2*f[j][k]%mod);
				if(j&&y)
					Add(g[j-1][k+1],j*y*2*f[j][k]%mod);
				if(k)
					Add(g[j][k-1],k*f[j][k]%mod);
				if(x)
					Add(g[j][k+1],x*f[j][k]%mod);
			}
		for(int j=0;j<=n;j++)
			for(int k=0;j+k<=n;k++)
				f[j][k]=g[j][k],g[j][k]=0;
	}
	int ans=0;
	for(int i=0;i<=n;i++)
		Add(ans,f[i][n-i]);
	cout<<ans<<"\n";
}
