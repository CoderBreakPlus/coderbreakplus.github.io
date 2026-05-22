// created time: 2026-05-22 08:57:27
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
template<typename T>inline void addmod(T &x){ if(x >= mod) x -= mod; }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

inline void upd(int &x,ull y){ x=(x+y)%mod; }

int n,m,k,t,sub,f[1<<19],g[1<<19],h[1<<19],val[100];
vector<pair<int,int>>E[105];
vector<pair<int,int>>G[105];

int nd[19],c;
int fa[19],sz[19],st[19],vis[19];
int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
struct Edge{
	int to,w,nxt;
}e[40];
int hd[19],ind[19],tot;
void add(int u,int v,int w){
	e[++tot]=(Edge){v,w,hd[u]};
	hd[u]=tot;
}
vector<pair<int,int>>seq[19]; int sq;

int dfs(int x,int fa){
	int ret=1;
	for(int i=hd[x];i;i=e[i].nxt){
		int y=e[i].to,w=e[i].w;
		if(y==fa)ret=(ull)ret*w%mod;
		else ret=(ull)ret*dfs(y,x)%mod;
	}
	return ret;
}
void Search(int i,int x,int to,int cf){
	if(!cf)return;
	if(x==sq){
		upd(g[to], (ull)f[i]*cf);
		return;
	}
	for(auto [a,b]: seq[x])
		Search(i,x+1,to|a,(ull)cf*b%mod);
}
void procedure(){
	n=read(),m=read(),k=read(),t=read(),sub=read();
	for(int i=0;i<n;i++)val[i]=t;
	for(int i=1;i<=m;i++){
		int u=read(),v=read(),p=(mod+1-read())%mod;
		if(u>v)swap(u,v);
		int q=(ull)p*(mod+1-p)%mod;
		addmod(val[u]+=p),addmod(val[v]+=p);
		if(u/k==v/k){
			E[u].pb(v%k,q);
		}else{
			G[u].pb(v%k,q);
		}
	}

	f[0]=1;
	for(int mv=0;mv<n;mv+=k){
		int m=min(n-mv,k);
		for(int i=0;i<m;i++){
			memset(g,0,sizeof(g));
			for(int j=0;j<(1<<m);j++){
				addmod(g[j]+=f[j]);
				if((~j>>i)&1){
					upd(g[j^(1<<i)], (ull)f[j]*val[mv+i]);
					for(auto [k,q]: E[mv+i]){
						if((~j>>k)&1)
						upd(g[j^(1<<i)^(1<<k)], (ull)f[j]*q);
					}
				}
			}
			memcpy(f,g,sizeof(f));
		}
		if(mv+k>=n){
			printf("%d\n",f[(1<<m)-1]);
			return;
		}
		memset(g,0,sizeof(g));

		for(int i=0;i<(1<<m);i++){
			if(!f[i]) continue;
			memset(hd,0,sizeof(hd)); tot=1;

			c=0;
			int to=0,flg=1,cf=1;
			for(int j=0;j<m;j++)
			fa[j]=j,sz[j]=vis[j]=ind[j]=0,st[j]=(1<<j);

			for(int j=0;j<m;j++)if((~i>>j)&1){
				if(G[mv+j].empty()) { flg=0; break; }
				if(G[mv+j].size()==1){
					auto [x,y]=G[mv+j][0];
					if(to&(1<<x)) { flg=0; break; }
					cf=(ull)cf*y%mod;
					sz[find(x)]++, to|=(1<<x);
				}else{
					auto [x0,y0]=G[mv+j][0];
					auto [x1,y1]=G[mv+j][1];
					ind[x0]++,ind[x1]++;
					add(x0,x1,y0), add(x1,x0,y1);
					x0=find(x0),x1=find(x1);
					if(x0==x1)sz[x0]++;
					else fa[x0]=x1,sz[x1]+=sz[x0],st[x1]|=st[x0];
				}
			}
			if(!flg)continue;
			sq=0; int mark=to;
			for(int j=0;j<m;j++)if(find(j)==j&&__builtin_popcount(st[j])>1){
				if(sz[j]>=2){ flg=0; break; }
				if(st[j]&mark){
					int x=__builtin_ctz(st[j]&mark);
					cf=(ull)cf*dfs(x,-1)%mod, to|=st[j];
				}else{
					vector<int>node;
					for(int x=0;x<m;x++)if((st[j]>>x)&1)node.pb(x);
					if(sz[j]==1){
						queue<int>que;
						for(int x:node)
							if(ind[x]==1)que.push(x),vis[x]=1;
						while(!que.empty()){
							int x=que.front(); que.pop();
							for(int I=hd[x];I;I=e[I].nxt){
								int y=e[I].to,w=e[I].w;
								if(vis[y])continue;
								cf=(ull)cf*w%mod; ind[y]--;
								if(ind[y]==1) que.push(y),vis[y]=1;
							}
						}
						int rt=0;
						for(int x:node)
							if(!vis[x]){ rt=x; break; }

						int sb1=1,sb2=1,go1=0,go2=0,prv1=0,prv2=0;
						
						for(int I=hd[rt];I;I=e[I].nxt){
							int y=e[I].to, w=e[I].w;
							if(vis[y])continue;
							if(!go1) go1=y,sb1=w,prv1=I;
							else go2=y,sb2=w,prv2=I;
						}

						while(go1!=rt){
							for(int I=hd[go1];I;I=e[I].nxt){
								int y=e[I].to, w=e[I].w;
								if(vis[y]||(I^1)==prv1)continue;
								sb1=(ull)sb1*w%mod,prv1=I,go1=y;
								break;
							}
						}
						while(go2!=rt){
							for(int I=hd[go2];I;I=e[I].nxt){
								int y=e[I].to, w=e[I].w;
								if(vis[y]||(I^1)==prv2)continue;
								sb2=(ull)sb2*w%mod,prv2=I,go2=y;
								break;
							}
						}
						cf=(ull)cf*(sb1+sb2)%mod;
						to|=st[j];
					}else{
						seq[sq].clear();
						for(int x:node)
							seq[sq].pb(st[j]^(1<<x),dfs(x,-1));
						++sq;
					}
				}
			}
			if(!flg)continue;
			Search(i,0,to,cf);
		}
		memcpy(f,g,sizeof(f));
	}
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