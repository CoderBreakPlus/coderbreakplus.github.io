// created time: 2026-08-20
#include <bits/stdc++.h>
using namespace std;
#define int long long
const int MAXN=610,INF=1e9;
inline int read(){
	int x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
int n,m,x,y,z,s,t,dis[MAXN][MAXN],w[MAXN],dap[MAXN],vis[MAXN],ord[MAXN];
int proc (int x) {
	memset(vis,0,sizeof(vis));
	memset(w,0,sizeof(w));
	w[0]=-1;
	for (int i=1;i<=n-x+1;i++) {
		int mx=0;
		for (int j=1;j<=n;j++) {
			if (!dap[j]&&!vis[j]&&w[j]>w[mx]) {mx=j;}
		}
		vis[mx]=1,ord[i]=mx;
		for (int j=1;j<=n;j++) {
			if (!dap[j]&&!vis[j]) {w[j]+=dis[mx][j];}
		}
	}
	s=ord[n-x],t=ord[n-x+1];
	return w[t];
}
int sw () {
	int res=INF;
	for (int i=1;i<n;i++) {
		res=min(res,proc(i));
		dap[t]=1;
		for (int j=1;j<=n;j++) {
			dis[s][j]+=dis[t][j];
			dis[j][s]+=dis[j][t];
		}
	}
	return res;
}
signed main () {
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	int T=read();
	while(T--){
		memset(dis,0,sizeof(dis));
		s=t=0;
		memset(w,0,sizeof(w));
		memset(dap,0,sizeof(dap));
		memset(vis,0,sizeof(vis));
		memset(ord,0,sizeof(ord));
		n=read(),m=read();
		for (int i=1;i<=m;i++) {
			x=read(),y=read(),z=read();
			dis[x][y]+=z,dis[y][x]+=z;
		}
		printf("%lld\n",(n-1)*sw());
	}
	return 0;
}
