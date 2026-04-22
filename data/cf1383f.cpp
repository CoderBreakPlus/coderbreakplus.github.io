// created time: 2026-04-22 14:38:18
// #pragma GCC optimize(3,"inline")
// #pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
// #pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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

int n,m,k,q,ans[1<<10],u[10],v[10],tmp[1<<10];
int que[300005],h,t;
int hd[10005],to[20055],nxt[20055],tot=1;
int dep[10005],cur[10005],id[10];

struct Graph{
	int w[20055];
	bool bfs(){
		memcpy(cur,hd,sizeof(cur));
		memset(dep,0,sizeof(dep));
		que[h=t=1]=dep[1]=1;
		while(h<=t){
			int x=que[h++];
			for(int i=hd[x];i;i=nxt[i])if(w[i]){
				int y=to[i];
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
		for(int &i=cur[x];i&&fl;i=nxt[i]){
			int y=to[i],ww=w[i];
			if(dep[y]==dep[x]+1 && ww){
				int f=dfs(y,min(fl,ww));
				fl-=f,ret+=f;
				w[i]-=f,w[i^1]+=f;
			}
		}
		return ret;
	}
	int ff(){
		// cout<<"fuckit"<<endl;
		memset(dep,0,sizeof(dep));
		que[h=t=1]=dep[1]=1;
		while(h<=t){
			int x=que[h++];
			for(int i=hd[x];i;i=nxt[i])if(w[i]){
				int y=to[i];
				if(!dep[y]) dep[y]=dep[x]+1,cur[y]=i,que[++t]=y;
			}
		}
		if(!dep[n])return 0;

		int val=25;
		int m=n;
		while(m!=1){
			val=min(val,w[cur[m]]);
			m=to[cur[m]^1];
		}

		m=n;
		while(m!=1){
			w[cur[m]]-=val;
			w[cur[m]^1]+=val;
			m=to[cur[m]^1];
		}
		// cout<<"val="<<val<<endl;
		return val;
	}
	int dinic(){
		int ret=0,sb;
		while(bfs()){
			sb = dfs(1,25);
			ret += sb;
		}
		return ret;
	}
	int delta(){
		// cout<<"shabi1"<<endl;
		int ret=0, sb;
		while(sb=ff()) ret+=sb;
		return ret;
	}
}g[1<<10];

int addedge(int u,int v,int w){
	to[++tot]=v;
	g[0].w[tot]=w;
	nxt[tot]=hd[u];
	hd[u]=tot;
	return tot;
}
int add(int u,int v,int w){
	int x=addedge(u,v,w);
	addedge(v,u,0);
	return x;
}
void procedure(){
	n=read(),m=read(),k=read(),q=read();
	for(int i=0;i<m;i++){
		if(i>=k){
			int u=read(),v=read(),w=read();
			add(u,v,w);
		}else{
			u[i]=read(),v[i]=read(),read();
			id[i]=add(u[i],v[i],0);
		}
	}
	ans[0]=g[0].dinic();
	// cout<<"fuck1"<<endl;
	for(int i=1;i<(1<<k);i++){
		int x=__builtin_ctz(i);
		g[i]=g[i^(1<<x)];
		g[i].w[id[x]]=25;
		ans[i]=ans[i^(1<<x)]+g[i].delta();
	}
	while(q--){
		int ret=1e9;
		for(int i=0;i<k;i++) tmp[1<<i]=read();
		for(int i=1;i<(1<<k);i++){
			int j=(i&-i);
			tmp[i]=tmp[i^j]+tmp[j];
		}
		for(int i=0;i<(1<<k);i++)
			ret=min(ret, tmp[i]+ans[(1<<k)-1-i]);
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