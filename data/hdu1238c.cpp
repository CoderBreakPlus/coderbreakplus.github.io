// created time: 2026-08-20 12:33:17
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

int S=1999,T=2000;
struct Graph{
	struct Edge{
		int to,w,nxt;
	}e[120005];
	int hd[2005],cur[2005],tot;

	void add(int u,int v,int w){
		e[++tot].to=v;
		e[tot].w=w;
		e[tot].nxt=hd[u]; hd[u]=tot;
	}
	void addedge(int u,int v,int w){
		// cout<<"add "<<u<<" "<<v<<" "<<w<<endl;
		add(u,v,w),add(v,u,0);
	}
	void clear(){
		tot=1;
		memset(hd,0,sizeof(hd));
	}

	int dep[2005];
	bool bfs(){
		memcpy(cur,hd,sizeof(cur));
		memset(dep,0,sizeof(dep));

		queue<int>q; q.push(S),dep[S]=1;
		while(!q.empty()){
			int x=q.front(); q.pop();
			for(int i=hd[x];i;i=e[i].nxt){
				int y=e[i].to;
				if(!dep[y] && e[i].w){
					dep[y]=dep[x]+1;
					q.push(y);
				}
			}
		}
		return dep[T];
	}
	int dfs(int x,int fl){
		if(x==T) return fl;
		int ret=0;
		for(int &i=cur[x];i;i=e[i].nxt){
			int y=e[i].to, w=e[i].w;
			if(dep[y]!=dep[x]+1)continue;

			int now=dfs(y,min(fl,w));
			e[i].w-=now,e[i^1].w+=now;
			fl-=now,ret+=now;

			if(!fl) break; 
		}
		return ret;
	}
	int dinic(){
		int ans=0;
		while(bfs())ans+=dfs(S,1e9);
		return ans;
	}
}G;

int n,k;
vector<int>E[1005];

void procedure(){
	n=read(),k=read();
	for(int i=1;i<=n;i++){
		char s[35];E[i].clear();
		scanf("%s",s+1);
		for(int j=1;j<=k;j++)
			if(s[j]=='1')E[i].pb(j);
	}
	int L=0,R=n/k;
	while(L<R){
		int mid=(L+R+1)>>1;

		G.clear();
		// cout<<"checking "<<mid<<endl;
		for(int i=1;i<=n;i++) {
			G.addedge(S,i,1);
			for(int j:E[i]) G.addedge(i,n+j,1);
		}
		for(int i=1;i<=k;i++)
			G.addedge(n+i,T,mid);

		if(G.dinic()==mid*k) L=mid;
		else R=mid-1;
	}
	printf("%d\n",L);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}