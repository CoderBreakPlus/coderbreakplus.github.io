// created time: 2026-08-21 11:28:51
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define pb emplace_back
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }

ll n,m,Q,s[100005];
ll c[100005],dfn[100005],vis[100005],tim,idx,sz;

ll d[200][100005],ind[100005];
ll f[25][100005],fa[100005],ff[100005],cnt[100005],dep[100005];

ll jp[100005];
ll jump(ll x){
	if(x!=jp[x]) jp[x]=jump(jp[x]);
	return jp[x];
}

vector<ll>E[100005],G[100005],H[100005];
ll get(ll x,ll y){ return dfn[x]<dfn[y]?x:y; }

void dfs(ll x,ll fa){
	dfn[x]=++tim, f[0][dfn[x]]=fa;
	for(ll y:E[x]){
		if(y==fa)continue;
		if(dfn[y]&&dfn[y]<dfn[x])c[++idx]=x,c[++idx]=y;
		else if(!dfn[y]){
			dep[y]=dep[x]+1;
			dfs(y,x);
			G[x].pb(y),G[y].pb(x); ::fa[y]=x;
		}
	}
}
ll LCA(ll x,ll y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	ll p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
ll dist(ll x,ll y){ return dep[x]+dep[y]-2*dep[LCA(x,y)]; }

vector<ll>edge[200],qz[200];
ll bel[100005],pos[100005];

ll dp[100005],sb[100005],final[100005];

void link(ll x,ll y){
	sb[x]+=sb[y];
	dp[x]+=dp[y],dp[x]+=sb[y];
}
void cut(ll x,ll y){
	dp[x]-=dp[y],dp[x]-=sb[y];
	sb[x]-=sb[y];
}
void dp1(ll x,ll fa){
	sb[x]=1;
	for(ll y:G[x]){
		if(y==fa||ind[y])continue;
		dp1(y,x),link(x,y);
	}
}
void dp2(ll x,ll fa){
	final[x]=dp[x];
	for(ll y:G[x]){
		if(y==fa||ind[y])continue;
		cut(x,y); link(y,x); dp2(y,x); cut(y,x); link(x,y);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	n=read(),m=read();
	ll tot=0;
	for(ll i=1;i<=n;i++) jp[i]=i;

	for(ll i=1;i<=m;i++){
		ll u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
		ind[u]++,ind[v]++;
	}
	dfs(1,0);

	for(ll i=1;(1<<i)<=n;i++)
		for(ll j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	if(idx==0){
		memset(ind,0,sizeof(ind));
		dp1(1,0),dp2(1,0);
		ll ans=0;
		for(ll x=1;x<=n;x++)
			ans+=final[x];
		printf("%lld\n",ans/2);
		return 0;
	}
	sort(c+1,c+idx+1,[](ll x,ll y){ return dfn[x]<dfn[y]; });
	sz=idx=unique(c+1,c+idx+1)-(c+1);
	for(ll i=2;i<=idx;i++)c[++sz]=LCA(c[i-1],c[i]);

	sort(c+1,c+sz+1,[](ll x,ll y){ return dfn[x]<dfn[y]; });
	idx=unique(c+1,c+sz+1)-(c+1);
	
	for(ll i=1;i<=idx;i++)vis[c[i]]=i;

	memset(d,-1,sizeof(d));
	for(ll i=1;i<=idx;i++){
		ll *dis=d[i];
		dis[c[i]]=0; queue<ll>q; q.push(c[i]);
		while(!q.empty()){
			ll x=q.front();q.pop();
			for(ll y:E[x])if(!~dis[y]){
				dis[y]=dis[x]+1;
				q.push(y);
			}
		}
	}

	queue<ll>q;
	for(ll i=1;i<=n;i++){
		cnt[i]=1;
		if(!vis[i]&&ind[i]==1) q.push(i);
	}
	while(!q.empty()){
		ll x=q.front();q.pop();
		for(ll y:E[x]){
			if(!ind[y])continue;
			ind[x]--,ind[y]--;
			tot+=cnt[x];
			cnt[y]+=cnt[x]; jp[jump(x)]=jump(y);
			if(!vis[y]&&ind[y]==1) q.push(y);
		}
	}

	for(ll i=1;i<=n;i++)
		if(ind[i]) dp1(i,0),dp2(i,0);

	for(ll i=2;i<=idx;i++){
		ff[i]=vis[LCA(c[i-1],c[i])];
		ll cur=fa[c[i]];
		edge[i].pb(0);
		while(!vis[cur]){
			bel[cur]=i,pos[cur]=edge[i].size();
			edge[i].pb(cnt[cur]);
			cur=fa[cur];
		}
		edge[i].pb(0);

		ll siz=edge[i].size();
		qz[i].resize(siz);

		ll sum=0;
		for(ll x=1;x<siz;x++)
			qz[i][x]=qz[i][x-1]+edge[i][x]*x;

		for(ll x=1;x<siz;x++) edge[i][x]+=edge[i][x-1];
	}
	ll all=0;
	for(ll x=1;x<=n;x++){
		ll ans=tot;
		for(ll i=1;i<=idx;i++)
			ans+=cnt[c[i]]*d[i][x];
		ll tx=jump(x),dis=dist(x,tx);
		ans+=final[x]-final[tx];

		ans-=cnt[tx]*dis;
		ll col=bel[tx];

		for(ll i=2;i<=idx;i++){
			ll siz=edge[i].size()-1;
			ll L=d[i][x];
			ll R=d[ff[i]][x]+siz;
			if(i!=col){
				ll cut=max(0ll,min(siz,(R-L)/2));
				ans+=edge[i][cut]*L+qz[i][cut];
				ans+=(edge[i][siz]-edge[i][cut])*R+qz[i][cut]-qz[i][siz];
			}else{
				ll p=pos[tx];
				ll MR=dis+p,ML=dis-p;
				ll cut=max(0ll,min(p,(MR-L)/2));
				ans+=edge[i][cut]*L+qz[i][cut];
				ans+=(edge[i][p]-edge[i][cut])*MR+qz[i][cut]-qz[i][p];
				cut=max(p,min(siz,(R-ML)/2));
				ans+=(edge[i][cut]-edge[i][p])*ML+qz[i][cut]-qz[i][p];
				ans+=(edge[i][siz]-edge[i][cut])*R+qz[i][cut]-qz[i][siz];
			}
		}
		all+=ans;
	}
	printf("%lld\n",all/2);
}