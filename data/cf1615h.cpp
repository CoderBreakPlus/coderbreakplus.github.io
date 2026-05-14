// created time: 2026-05-14 10:18:57
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

int n,m,a[1005],s=1001,t=1002;
struct MaxFlow{
	struct Edge{
		ll to,u,w,nxt;
	}e[4005];
	ll hd[1005],cur[1005],tot;
	ll add(ll u,ll v,ll w){
		e[++tot].to=v;
		e[tot].u=u;
		e[tot].w=w;
		e[tot].nxt=hd[u];
		hd[u]=tot;
		return tot;
	}
	ll addedge(ll u,ll v,ll w){
		// cout<<"addedge "<<u<<" "<<v<<" "<<w<<endl;
		ll x=add(u,v,w);
		add(v,u,0);
		return x;
	}
	ll dep[1005];
	void clear(){
		memset(hd,0,sizeof(hd));
		memset(dep,0,sizeof(dep));
		for(int i=0;i<4005;i++)e[i]=(Edge){0,0,0,0};
		tot=1;
	}
	bool bfs(){
		memset(dep,0,sizeof(dep));
		memcpy(cur,hd,sizeof(cur));
		queue<ll>q; q.push(s);
		dep[s]=1;
		while(!q.empty()){
			ll x=q.front(); q.pop();
			for(ll i=hd[x];i;i=e[i].nxt){
				ll y=e[i].to, w=e[i].w;
				if(w && !dep[y]){
					dep[y]=dep[x]+1;
					q.push(y);
				}
			}
		}
		return dep[t];
	}
	ll dfs(ll x,ll flow){
		if(x==t) return flow;
		ll ret=0;
		for(ll &i=cur[x];i&&flow;i=e[i].nxt){
			ll y=e[i].to, w=e[i].w;
			if(dep[y]==dep[x]+1 && w){
				ll ff=dfs(y,min(flow,w));
				ret+=ff,flow-=ff;
				e[i].w-=ff, e[i^1].w+=ff;
			}
		}
		return ret;
	}
	ll dinic(){
		ll ans=0;
		while(bfs()) ans+=dfs(s, INT_MAX);
		return ans;
	}
}G;

int u[1005],v[1005],rk[1005],seq[1005],ans[1005],cnt;

int in[1005],fk[1005],tp[1005];
int ABS(int x){ return x<0?-x:x; }
void solve(int l,int r,vector<int>node){
	if(node.empty())return;
	if(l==r){
		for(auto x: node) ans[x]=seq[l];
		return;
	}

	int lm=(l+r)>>1,rm=lm+1;

	// cout<<"dividing "<<seq[lm]<<" "<<seq[rm]<<endl;
	// cout<<"dividing "<<seq[l]<<"->"<<seq[lm]<<" to "<<seq[rm]<<"->"<<seq[r]<<endl;

	G.clear();
	vector<int>ls,rs;
	for(auto x:node){
		in[x]=1;
		int val=ABS(seq[rm]-a[x])-ABS(seq[lm]-a[x]);
		if(val>0) fk[x]=G.addedge(s,x,val),tp[x]=0;
		else fk[x]=G.addedge(x,t,-val),tp[x]=1;
	}

	for(int i=1;i<=m;i++)
		if(in[u[i]] && in[v[i]]){
			G.addedge(v[i],u[i],1e18);
		}

	G.dinic();
	G.bfs();

	for(auto x: node){
		if(G.dep[G.e[fk[x]].u] && !G.dep[G.e[fk[x]].to]) tp[x]^=1;
		if(tp[x]) rs.pb(x);
		else ls.pb(x);
	}

	// for(auto x: ls) cout<<x<<" "; cout<<endl;
	// for(auto x: rs) cout<<x<<" "; cout<<endl;
	
	solve(l,lm,ls);
	solve(rm,r,rs);
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read(),seq[++cnt]=a[i];
	sort(seq+1,seq+cnt+1); cnt=unique(seq+1,seq+cnt+1)-(seq+1);

	for(int i=1;i<=n;i++)
		rk[i]=lower_bound(seq+1,seq+n+1,a[i])-seq;
	
	for(int i=1;i<=m;i++) u[i]=read(),v[i]=read();
	vector<int>ok;
	for(int i=1;i<=n;i++)ok.pb(i);
	solve(1,cnt,ok);

	ll cer=0;
	for(int i=1;i<=n;i++) printf("%d ",ans[i]),cer+=ABS(ans[i]-a[i]);
	cerr<<"cer="<<cer<<endl;
	puts("");
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