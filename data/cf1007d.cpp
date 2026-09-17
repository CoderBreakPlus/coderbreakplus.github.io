// created time: 2026-09-17 14:15:25
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
#define mid ((l+r)>>1)
int n,m,id;
const int M = 3e6+5;
namespace sat{
	struct Edge{
		int to,nxt;
	}e[M<<2];
	int hd[M],tot,tim;
	void add(int u,int v){
		if(!u||!v)return;
		e[++tot].to=v;
		e[tot].nxt=hd[u];
		hd[u]=tot;
	}

	int low[M],dfn[M],vis[M],col[M],stk[M],tp,colt;
	void tarjan(int x){
		low[x]=dfn[x]=++tim; stk[++tp]=x,vis[x]=1;
		for(int i=hd[x];i;i=e[i].nxt){
			int y=e[i].to;
			if(!dfn[y]){
				tarjan(y);
				chkmin(low[x],low[y]);
			}else if(vis[y])
				chkmin(low[x],dfn[y]);
		}
		if(low[x]==dfn[x]){
			++colt;
			do{
				int y=stk[tp];
				vis[y]=0,col[y]=colt;
			}while(stk[tp--]!=x);
		}
	}
	void main(){
		for(int i=1;i<=id;i++)
			if(!dfn[i])tarjan(i);

		bool fiasco=1;
		for(int i=1;i<=m;i++)
			fiasco&=(col[i]!=col[i+m]);
		if(!fiasco){ puts("NO"); return; }
		puts("YES");
		for(int i=1;i<=m;i++)
			puts(col[i]<col[i+m]?"1":"2"); 
	}
}
vector<int>E[100005];
int dfn[100005],out[100005],ff[100005],f[20][100005],jp[20][100005],tim;
int lc[M],rc[M];

int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
void dfs(int x,int fa){
	f[0][dfn[x]=++tim]=ff[x]=jp[0][x]=fa;
	for(int i=1;i<20;i++)
		jp[i][x]=jp[i-1][jp[i-1][x]];

	for(int y:E[x])if(y!=fa)
		dfs(y,x);
	out[x]=tim;
}
int LCA(int x,int y){
	if(x==y) return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-(++x)+1);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}

struct Tree{
	int op;
	void add(int u,int v){
		if(!u||!v)return;
		if(!op) sat::add(u,v);
		else sat::add(v,u);
	}
	int rt[100005];
	int update(int l,int r,int x,int w,int b){
		int p=++id;
		if(l==r) return add(p,w),p;
		if(x<=mid)
			add(p,lc[p]=update(l,mid,x,w,lc[b])),add(p,rc[p]=rc[b]);
		else
			add(p,lc[p]=lc[b]),add(p,rc[p]=update(mid+1,r,x,w,rc[b]));
		return p;
	}
	void link(int l,int r,int ql,int qr,int w,int p){
		if(!p||r<ql||qr<l)return;
		if(ql<=l&&r<=qr) {add(w,p);return;}
		link(l,mid,ql,qr,w,lc[p]),link(mid+1,r,ql,qr,w,rc[p]);
	}
	void montagem(int i,int x,int y){
		rt[i]=update(1,2*m,x,y,rt[i]);
	}
}q0,q1,h0,h1;

int u[20005],v[20005],id0[20005],id1[20005],rv[20005],ru[20005],vv[20005],vu[20005],p[20005];
vector<int>insq[100005],insh[100005];

void procedure(){
	n=read();
	q0.op=h0.op=0;
	q1.op=h1.op=1;
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
	m=read(); id=2*m;

	for(int i=1;i<=m;i++){
		int a=read(),b=read(),c=read(),d=read();
		if(dfn[a]>dfn[b])swap(a,b);
		if(dfn[c]>dfn[d])swap(c,d);
		u[2*i-1]=a,v[2*i-1]=b,id1[2*i-1]=i,id0[2*i-1]=i+m;
		u[2*i]=c,v[2*i]=d,id1[2*i]=i+m,id0[2*i]=i;
	}
	for(int i=1;i<=2*m;i++)p[i]=i;
	sort(p+1,p+2*m+1,[](int x,int y){return dfn[v[x]]<dfn[v[y]];});
	for(int i=1;i<=2*m;i++)rv[p[i]]=i,vv[i]=dfn[v[p[i]]];
	sort(p+1,p+2*m+1,[](int x,int y){return dfn[u[x]]<dfn[u[y]];});
	for(int i=1;i<=2*m;i++)ru[p[i]]=i,vu[i]=dfn[u[p[i]]];

	for(int k=1;k<=2*m;k++){
		insq[dfn[u[k]]].pb(k);
		insh[dfn[v[k]]].pb(k);
	}
	for(int i=1;i<=n;i++){
		q0.rt[i]=q0.rt[i-1],q1.rt[i]=q1.rt[i-1];
		for(int k:insq[i]){
			q0.montagem(i,rv[k],id0[k]);
			q1.montagem(i,rv[k],id1[k]);
		}
	}
	for(int i=n;i>=1;i--){
		h0.rt[i]=h0.rt[i+1],h1.rt[i]=h1.rt[i+1];
		for(int k:insh[i]){
			h0.montagem(i,ru[k],id0[k]);
			h1.montagem(i,ru[k],id1[k]);
		}
	}
	auto qry=[&](int k,int x){
		int ql=dfn[x],qr=out[x];
		int l=lower_bound(vv+1,vv+2*m+1,ql)-vv;
		int r=upper_bound(vv+1,vv+2*m+1,qr)-vv-1;
		if(l<=r){
			int t=rv[k];
			auto lk=[&](int L,int R){
				if(L<=R){
					q0.link(1,2*m,L,R,id1[k],q0.rt[dfn[x]-1]);
					q1.link(1,2*m,L,R,id0[k],q1.rt[dfn[x]-1]);
				}
			};
			lk(l,min(r,t-1)),lk(max(l,t+1),r);
		}
		l=lower_bound(vu+1,vu+2*m+1,ql)-vu;
		r=upper_bound(vu+1,vu+2*m+1,qr)-vu-1;
		if(l<=r){
			int t=ru[k];
			auto lk=[&](int L,int R){
				if(L<=R){
					h0.link(1,2*m,L,R,id1[k],h0.rt[out[x]+1]);
					h1.link(1,2*m,L,R,id0[k],h1.rt[out[x]+1]);
				}
			};
			lk(l,min(r,t-1)),lk(max(l,t+1),r);
		}
	};
	for(int k=1;k<=2*m;k++){
		int ab=LCA(u[k],v[k]);
		if(u[k]!=ab){
			int x=u[k];
			for(int o=19;o>=0;o--)
				if(dfn[jp[o][x]]>dfn[ab])x=jp[o][x];
			qry(k,x);
		}
		if(v[k]!=ab){
			int x=v[k];
			for(int o=19;o>=0;o--)
				if(dfn[jp[o][x]]>dfn[ab])x=jp[o][x];
			qry(k,x);
		}
	}
	sat::main();
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