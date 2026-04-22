// created time: 2026-04-22 14:38:18
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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

int n,m,k,q,ans[1<<10],u[10],v[10],w[1<<10];
int que[300005],h,t;
struct Graph{
	struct Edge{
		short to,w,nxt;
	}e[20055];
	short hd[10005],dep[10005],cur[10005],tot;
	Graph(){ tot = 1; }
	void addedge(int u,int v,int w){
		e[++tot].to=v;
		e[tot].w=w;
		e[tot].nxt=hd[u];
		hd[u]=tot;
	}
	void add(int u,int v,int w){
		addedge(u,v,w), addedge(v,u,0);
	}
	bool bfs(){
		memcpy(cur,hd,sizeof(cur));
		memset(dep,0,sizeof(dep));
		que[h=t=1]=dep[1]=1;
		while(h<=t){
			int x=que[h++];
			for(int i=hd[x];i;i=e[i].nxt)if(e[i].w){
				int y=e[i].to;
				if(!dep[y]){
					dep[y]=dep[x]+1,que[++t]=y;
				}
			}
		}
		return dep[n];
	}
	int dfs(int x,int fl){
		if(x==n) return fl;
		int ret=0;
		for(short &i=cur[x];i&&fl;i=e[i].nxt){
			int y=e[i].to,w=e[i].w;
			if(dep[y]==dep[x]+1 && w){
				int f=dfs(y,min(fl,w));
				fl-=f,ret+=f;
				e[i].w-=f,e[i^1].w+=f;
			}
		}
		return ret;
	}
	int ff(){
		memset(dep,0,sizeof(dep));
		que[h=t=1]=dep[1]=1;
		while(h<=t){
			int x=que[h++];
			for(int i=hd[x];i;i=e[i].nxt)if(e[i].w){
				int y=e[i].to;
				if(!dep[y]) dep[y]=dep[x]+1,cur[y]=i,que[++t]=y;
			}
		}
		if(!dep[n])return 0;

		short val=25;
		int m=n;
		while(m!=1){
			val=min(val,e[cur[m]].w);
			m=e[cur[m]^1].to;
		}

		m=n;
		while(m!=1){
			e[cur[m]].w-=val;
			e[cur[m]^1].w+=val;
			m=e[cur[m]^1].to;
		}
		return val;
	}
	int dinic(){
		int ret=0,tmp;
		while(bfs()){
			tmp = dfs(1,25);
			ret += tmp;
		}
		return ret;
	}
	int delta(){
		int ret=0, tmp;
		while(tmp=ff()) ret+=tmp;
		return ret;
	}
}g[1<<10];
void procedure(){
	n=read(),m=read(),k=read(),q=read();
	for(int i=0;i<m;i++){
		if(i>=k){
			int u=read(),v=read(),w=read();
			g[0].add(u,v,w);
		}else{
			u[i]=read(),v[i]=read(),read();
		}
	}
	ans[0]=g[0].dinic();
	for(int i=1;i<(1<<k);i++){
		int x=__builtin_ctz(i);
		g[i]=g[i^(1<<x)];
		g[i].add(u[x],v[x],25);
		ans[i]=ans[i^(1<<x)]+g[i].delta();
	}
	while(q--){
		int ret=1e9;
		for(int i=0;i<k;i++) w[1<<i]=read();
		for(int i=1;i<(1<<k);i++){
			int j=(i&-i);
			w[i]=w[i^j]+w[j];
		}
		for(int i=0;i<(1<<k);i++)
			ret=min(ret, w[i]+ans[(1<<k)-1-i]);
		printf("%d\n",ret);
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