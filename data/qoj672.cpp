// created time: 2026-05-20 12:29:30
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
int n,m,d,b[105],c[1005],ss[1005]; vector<int>v[1005];

int s,t;
struct Graph{
	struct Edge{
		int to,w,c,nxt;
	}e[300005];
	int hd[3005],tot;
	Graph(){ tot=1; }

	int addedge(int u,int v,int w,int c){
		e[++tot].to=v,e[tot].w=w,e[tot].c=c;
		e[tot].nxt=hd[u]; return hd[u]=tot;
	}
	int add(int u,int v,int w,int c){
		// cout<<"add "<<u<<" "<<v<<" "<<w<<" "<<c<<endl;
		addedge(u,v,w,c);
		return addedge(v,u,0,-c);
	}

	ll dis[3005];
	int pre[3005],vis[3005],mn[3005];

	bool spfa(){
		memset(dis,0x3f,sizeof(dis));
		queue<int>q; q.push(s),vis[s]=1,mn[s]=1e9;
		dis[s]=0;
		while(!q.empty()){
			int x=q.front();q.pop();vis[x]=0;
			for(int i=hd[x];i;i=e[i].nxt){
				if(!e[i].w)continue;
				int y=e[i].to,v=e[i].c;
				if(dis[y]>dis[x]+v){
					dis[y]=dis[x]+v;
					mn[y]=min(mn[x],e[i].w);
					pre[y]=(i^1);
					if(!vis[y]) q.push(y),vis[y]=1;
				}
			}
		}
		return dis[t]<1e8; 
	}
	ll flow(){
		ll ans=0;
		int cnt=0;
		while(spfa()){
			ans+=mn[t]*dis[t];
			// cout<<"contri "<<mn[t]<<" * "<<dis[t]<<endl;
			cnt+=mn[t];
			int cur=t, cap=mn[t];
			while(cur!=s){
				int i=pre[cur];
				e[i].w+=cap, e[i^1].w-=cap;
				cur=e[i].to;
			}
		}
		if(cnt<n) return -1;
		// cout<<"cnt="<<cnt<<endl;
		return ans;
	}
}G;

void procedure(){
	n=read(),m=read(),d=read();
	s=d+m+n+1,t=d+m+n+2;

	for(int i=1;i<=n;i++) G.add(d+m+i,t,1,0);
	for(int i=1;i<=m;i++){
		c[i]=read(),ss[i]=read(); int k=read();
		G.add(ss[i],d+i,1,c[i]);
		while(k--){
			int x=read();
			G.add(d+i,d+m+x,1,0);
		}
	}
	for(int i=1;i<=d;i++) G.add(s,i,read(),0);
	printf("%lld\n",G.flow());
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