// created time: 2026-09-27 16:33:17
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

int n,sz[100005],dfn[100005],mxs[100005],f[20][100005],dep[100005],tim;
int p0[100005],p1[100005],p2[100005],out[100005],rt;
vector<int>E[100005];

ll k,s0,s1;
int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }

void dfs(int x,int fa){
	sz[x]=1,f[0][dfn[x]=++tim]=fa;
	mxs[x]=0;
	for(int y:E[x])if(y!=fa){
		dep[y]=dep[x]+1;
		dfs(y,x);sz[x]+=sz[y];
		chkmax(mxs[x],sz[y]);
	}
	chkmax(mxs[x],n-sz[x]);
	if(!rt||mxs[rt]>mxs[x]) rt=x;
}
int LCA(int x,int y){
	if(x==y) return x;
	if((x=dfn[x])>(y=dfn[y])) swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
int dist(int x,int y){ return dep[x]+dep[y]-2*dep[LCA(x,y)]; }

vector<int>S[100005];
void merge(int x,int fa,int op,int *p){
	for(int y:E[x])if(y!=fa)
		merge(y,x,op,p);

	priority_queue<pair<int,int>>Q;
	S[x]={x};
	int siz=0;
	Q.push({S[x].size(),x}),siz++;
	for(int y:E[x])if(y!=fa){
		if(S[y].size())Q.push({S[y].size(),y}),siz+=S[y].size();
	}

	if(!fa||!op){
		while(Q.size()>=2 && siz-2>=out[x]){
			int a=Q.top().se;Q.pop();
			int b=Q.top().se;Q.pop();
			int x=S[a].back(); S[a].pop_back();
			int y=S[b].back(); S[b].pop_back();
			p[x]=y,p[y]=x;

			if(!S[a].empty()) Q.push({S[a].size(),a});
			if(!S[b].empty()) Q.push({S[b].size(),b});
			siz-=2;
		}
	}
	for(int y:E[x]){
		if(S[y].size()>S[x].size())swap(S[x],S[y]);
		for(int e:S[y])S[x].pb(e);
		vector<int>().swap(S[y]);
	}
}

set<pair<int,int>,greater<pair<int,int>>>son[100005];
set<int>cand[100005];

int sig[100005];

#define fa(x) f[0][dfn[x]]

void init(int x){
	for(int y:E[x])if(y!=fa(x)){
		init(y);
		out[x]+=out[y];
		son[x].emplace(out[y],y);
		sig[x]+=out[y];
		if(sig[y]-1>=out[y]) cand[x].emplace(y);
	}
}
bool valid_light(int x){
	int mx = max(1, son[x].empty() ? 0 : son[x].begin()->fi);
	return sig[x]+3-out[x] <= 2*(sig[x]+3-mx);
}
bool valid_heavy(int x){
	int mx = max(1, son[x].empty() ? 0 : son[x].begin()->fi + 2);
	return sig[x]+3-out[x] <= 2*(sig[x]+3-mx);
}
void adjust(int x,int v){
	if(cand[fa(x)].count(x)) cand[fa(x)].erase(x);
	son[fa(x)].erase({out[x],x});
	out[x]+=v, sig[fa(x)]+=v;
	son[fa(x)].emplace(out[x],x);
	if(sig[x]-1>=out[x]) cand[fa(x)].emplace(x);
	if(fa(fa(x)) && sig[fa(x)]-1>=out[fa(x)]) cand[fa(fa(x))].emplace(fa(x));
}
set<int>que;

int checkL(int x){
	if(que.count(x))que.erase(x);
	if(cand[x].empty()||!valid_light(x))return 0;
	int val=son[x].begin()->fi; 
	for(int w:cand[x]) if(out[w]!=val){
		que.emplace(x);
		return w;
	}
	return 0;
}
int checkH(int x){
	if(que.count(x))que.erase(x);
	if(cand[x].empty()||!valid_heavy(x))return 0;
	que.emplace(x);
	return *cand[x].begin();
}
void flow(int x){
	adjust(x,2);
	if(!checkH(x)) checkL(x);
	if(!checkH(fa(x))) checkL(fa(x));
	if(fa(fa(x)) && !checkH(fa(fa(x)))) checkL(fa(fa(x)));
}
void procedure(){
	n=read(),k=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	merge(rt,0,0,p0);
	merge(rt,0,1,p1);

	for(int i=1;i<=n;i++) if(p0[i]>i) s0+=dist(i,p0[i]);
	for(int i=1;i<=n;i++) if(p1[i]>i) s1+=dist(i,p1[i]);

	if((k^s0)&1){ puts("NO"); return; }
	if(k<s0 || s1<k){ puts("NO"); return; }

	for(int i=1;i<=n;i++){
		if(p0[i]==p1[i])continue;
		int a=p1[i],b=p0[i],c=p1[p0[i]];
		s1-=dist(i,a)+dist(b,c);

		p1[i]=b,p1[b]=i;
		p1[a]=c,p1[c]=a;
		s1+=dist(i,b)+dist(a,c);

		if(s1<=k) break;
	}
	for(int i=1;i<=n;i++) if(p1[i]>i){
		out[i]++,out[p1[i]]++,out[LCA(i,p1[i])]-=2;
	}

	init(1);
	for(int i=1;i<=n;i++){
		if(!checkH(i)) checkL(i);
	}
	while(s1<k){
		assert(!que.empty());
		int u=*que.begin(),v=checkH(u);
		if(!v) v=checkL(u);
		flow(v),s1+=2;
	}
	merge(1,0,0,p2);

	puts("YES");
	for(int i=1;i<=n;i++) if(p2[i]>i) printf("%d %d\n",i,p2[i]);
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