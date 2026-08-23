// created time: 2026-08-21 11:28:51
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define pb emplace_back
const int mod = 1e9+7;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
template<typename T>inline void addmod(T &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,m,Q,s[100005];
int c[100005],dfn[100005],vis[100005],tim,idx,sz;

int d[45][100005],ind[100005];
int f[25][100005],fa[100005],ff[100005],cnt[100005],dep[100005];

int jp[100005];
int jump(int x){
	if(x!=jp[x]) jp[x]=jump(jp[x]);
	return jp[x];
}

vector<int>E[100005],G[100005],H[100005];
int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }

void dfs(int x,int fa){
	dfn[x]=++tim, f[0][dfn[x]]=fa;
	for(int y:E[x]){
		if(y==fa)continue;
		if(dfn[y]&&dfn[y]<dfn[x])c[++idx]=x,c[++idx]=y;
		else if(!dfn[y]){
			dep[y]=dep[x]+1;
			dfs(y,x);
			G[x].pb(y),G[y].pb(x); ::fa[y]=x;
		}
	}
}
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
int dist(int x,int y){ return dep[x]+dep[y]-2*dep[LCA(x,y)]; }

vector<int>edge[45],qz[45];
int bel[100005],pos[100005];

int dp[100005],sb[100005],final[100005];

void link(int x,int y){
	sb[x]+=sb[y];
	addmod(dp[x]+=dp[y]),addmod(dp[x]+=sb[y]);
}
void cut(int x,int y){
	addmod(dp[x]+=mod-dp[y]),addmod(dp[x]+=mod-sb[y]);
	sb[x]-=sb[y];
}
void dp1(int x,int fa){
	sb[x]=1;
	for(int y:G[x]){
		if(y==fa||ind[y])continue;
		dp1(y,x),link(x,y);
	}
}
void dp2(int x,int fa){
	final[x]=dp[x];
	for(int y:G[x]){
		if(y==fa||ind[y])continue;
		cut(x,y); link(y,x); dp2(y,x); cut(y,x); link(x,y);
	}
}
int main(){
	n=read(),m=read(),Q=read();
	int tot=0,ivn=INV(n);
	for(int i=1;i<=n;i++) addmod(tot+=mod-(s[i]=read())),jp[i]=i;

	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
		ind[u]++,ind[v]++;
	}
	dfs(1,0);

	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	if(idx==0){
		memset(ind,0,sizeof(ind));
		dp1(1,0),dp2(1,0);
		while(Q--){
			int x=read();
			int ans=(ull)(mod-tot+mod-final[x])*ivn%mod;
			printf("%d\n", ans);
		}
		return;
	}
	sort(c+1,c+idx+1,[](int x,int y){ return dfn[x]<dfn[y]; });
	sz=idx=unique(c+1,c+idx+1)-(c+1);
	for(int i=2;i<=idx;i++)c[++sz]=LCA(c[i-1],c[i]);

	sort(c+1,c+sz+1,[](int x,int y){ return dfn[x]<dfn[y]; });
	idx=unique(c+1,c+sz+1)-(c+1);
	
	for(int i=1;i<=idx;i++)vis[c[i]]=i;

	memset(d,-1,sizeof(d));
	for(int i=1;i<=idx;i++){
		int *dis=d[i];
		dis[c[i]]=0; queue<int>q; q.push(c[i]);
		while(!q.empty()){
			int x=q.front();q.pop();
			for(int y:E[x])if(!~dis[y]){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}

	queue<int>q;
	for(int i=1;i<=n;i++){
		cnt[i]=1;
		if(!vis[i]&&ind[i]==1) q.push(i);
	}
	while(!q.empty()){
		int x=q.front();q.pop();
		for(int y:E[x]){
			if(!ind[y])continue;
			ind[x]--,ind[y]--;
			addmod(tot+=cnt[x]);
			cnt[y]+=cnt[x]; jp[jump(x)]=jump(y);
			if(!vis[y]&&ind[y]==1) q.push(y);
		}
	}

	for(int i=1;i<=n;i++)
		if(ind[i]) dp1(i,0),dp2(i,0);

	for(int i=2;i<=idx;i++){
		ff[i]=vis[LCA(c[i-1],c[i])];
		int cur=fa[c[i]];
		edge[i].pb(0);
		while(!vis[cur]){
			bel[cur]=i,pos[cur]=edge[i].size();
			edge[i].pb(cnt[cur]);
			cur=fa[cur];
		}
		edge[i].pb(0);

		int siz=edge[i].size();
		qz[i].resize(siz);

		int sum=0;
		for(int x=1;x<siz;x++)
			qz[i][x]=(qz[i][x-1]+(ull)edge[i][x]*x)%mod;

		for(int x=1;x<siz;x++) edge[i][x]+=edge[i][x-1];
	}
	
	while(Q--){
		int x=read(),ans=tot;
		for(int i=1;i<=idx;i++)
			ans=(ans+(ull)cnt[c[i]]*d[i][x])%mod;
		int tx=jump(x),dis=dist(x,tx);
		addmod(ans+=final[x]);
		addmod(ans+=mod-final[tx]);

		ans=(ans+(ull)(mod-cnt[tx])*dis)%mod;
		int col=bel[tx];

		for(int i=2;i<=idx;i++){
			int siz=edge[i].size()-1;
			int L=d[i][x];
			int R=d[ff[i]][x]+siz;
			if(i!=col){
				int cut=max(0,min(siz,(R-L)/2));
				ans=(ans+(ull)edge[i][cut]*L+qz[i][cut])%mod;
				ans=(ans+(ull)(edge[i][siz]+mod-edge[i][cut])*R+qz[i][cut]+mod-qz[i][siz])%mod;
			}else{
				int p=pos[tx];
				int MR=dis+p,ML=dis-p;
				int cut=max(0,min(p,(MR-L)/2));
				ans=(ans+(ull)edge[i][cut]*L+qz[i][cut])%mod;
				ans=(ans+(ull)(edge[i][p]+mod-edge[i][cut])*MR+qz[i][cut]+mod-qz[i][p])%mod;
				cut=max(p,min(siz,(R-ML)/2));
				ans=(ans+(ull)(edge[i][cut]+mod-edge[i][p])*(ML+mod)+qz[i][cut]+mod-qz[i][p])%mod;
				ans=(ans+(ull)(edge[i][siz]+mod-edge[i][cut])*R+qz[i][cut]+mod-qz[i][siz])%mod;
			}
		}
		ans=(mod-ans)%mod;
		printf("%d\n",(int)((ull)ans*ivn%mod));
	}
}