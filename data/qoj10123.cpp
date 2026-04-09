// created time: 2026-04-09 09:38:24
// https://qoj.ac/contest/1924/problem/10123
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,m,x[305],y[305],r[305],f[305];

int s,t;
struct Graph{
	struct Edge{
		int to,w,c,nxt;
	}e[300005];
	int hd[305],tot;
	Graph(){ tot=1; }

	int addedge(int u,int v,int w,int c){
		e[++tot].to=v,e[tot].w=w,e[tot].c=c;
		e[tot].nxt=hd[u]; return hd[u]=tot;
	}
	int add(int u,int v,int w,int c){
		// cout<<"add "<<u<<"->"<<v<<" "<<w<<" "<<c<<endl;
		addedge(u,v,w,c);
		return addedge(v,u,0,-c);
	}

	ll dis[305];
	int pre[305],vis[305],mn[305];

	bool spfa(){
		memset(dis,0xc0,sizeof(dis));
		queue<int>q; q.push(s),vis[s]=1,mn[s]=1e9;
		dis[s]=0;

		while(!q.empty()){
			int x=q.front();q.pop();vis[x]=0;
			for(int i=hd[x];i;i=e[i].nxt){
				if(!e[i].w)continue;

				int y=e[i].to,v=e[i].c;
				if(dis[y]<dis[x]+v){
					dis[y]=dis[x]+v;
					mn[y]=min(mn[x],e[i].w);

					pre[y]=(i^1);
					if(!vis[y]) q.push(y),vis[y]=1;
				}
			}
		}
		return dis[t]>0; 
	}
	ll flow(){
		ll ans=0;
		int cnt=0;
		while(spfa()){
			ans+=mn[t]*dis[t];
			int cur=t, cap=mn[t];
			while(cur!=s){
				cnt++;
				if(cnt>1e4)break;

				int i=pre[cur];
				e[i].w+=cap, e[i^1].w-=cap;
				cur=e[i].to;
			}
		}
		// cout<<"end"<<endl;
		return ans;
	}
}G;

int e[305][305],col[305];
void dfs(int x){
	for(int y=1;y<=n;y++){
		if(e[x][y] && !col[y]){
			col[y]=3-col[x];
			dfs(y);
		}
	}
}
vector<int> son[305],fa[305];
int jp[305],id[305];

ll calc(ll x,ll y){ return x*x+y*y;}
void procedure(){
	n=read(),m=read();
	s=n+1,t=n+2;

	for(int i=1;i<=n;i++){
		x[i]=read(),y[i]=read(),r[i]=read(),f[i]=read();
	}

	for(int i=1;i<=n;i++)
		for(int j=i+1;j<=n;j++){
			ll d1=calc(y[j]-y[i],x[j]-x[i]);
			bool f1 = 1ll*(r[i]+r[j])*(r[i]+r[j]) < d1;
			bool f2 = d1 < 1ll*(r[j]-r[i])*(r[j]-r[i]);
			if(f1 || f2) {
				if(f2){
					if(r[i]>r[j]) son[i].pb(j),fa[j].pb(i);
					else son[j].pb(i),fa[i].pb(j);
				}
			}else
				e[i][j]=e[j][i]=1;
		}

	for(int i=1;i<=n;i++)
		if(!col[i])col[i]=1,dfs(i);

	for(int i=1;i<=n;i++){
		for(auto x: fa[i]) {
			if(col[x]==col[i]){
				if(!jp[i]) jp[i]=x;
				else if(r[x]<r[jp[i]]) jp[i]=x;
			}
		}
		if(!jp[i]){
			if(col[i]==1) jp[i]=s;
			else jp[i]=t;
		}
	}

	for(int i=1;i<=n;i++){
		if(col[i]==1) G.add(jp[i],i,f[i],0);
		else G.add(i,jp[i],f[i],0);
	}

	vector<int>ans;
	for(int i=1;i<=m;i++){
		int a=read(),b=read(),c=read();
		int lf=s;
		for(int j=1;j<=n;j++){
			if(col[j]!=1)continue;
			
			ll d=calc(b-y[j],a-x[j]);
			if(d<=1ll*r[j]*r[j]) {
				if(lf==s) lf=j;
				else if(r[j]<r[lf]) lf=j;
			}
		}

		int rh=t;
		for(int j=1;j<=n;j++){
			if(col[j]!=2)continue;
			
			ll d=calc(b-y[j],a-x[j]);
			if(d<=1ll*r[j]*r[j]) {
				if(rh==t) rh=j;
				else if(r[j]<r[rh]) rh=j;
			}
		}

		id[i]=G.add(lf,rh,1,c);
	}
	printf("%lld\n",G.flow());
	for(int i=1;i<=m;i++) if(G.e[id[i]].w) ans.pb(i);

	printf("%d\n",ans.size());
	for(auto x:ans) printf("%d ",x);puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}