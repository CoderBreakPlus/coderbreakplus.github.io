// created time: 2026-04-08 07:16:21
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

int n,p[300005],ans[300005];
pair<int,int> v[300005];
vector<int>E[300005];
int son[300005],sz[300005],ff[300005];

struct Node{
	int f[2][2],g[2][2];
}t[600005];

int lc[600005],rc[600005],fa[600005],op[600005],id;
inline void upd(int &a,ull b){ a=(a+b)%mod; }

void pushup(int x){
	memset(t[x].f,0,sizeof(t[x].f));
	if(op[x]){
		for(int i:{0,1})for(int j:{0,1})for(int k:{0,1})
			upd(t[x].f[i][k],(ull)t[lc[x]].f[i][j]*t[rc[x]].f[j][k]);
	}else{
		for(int i:{0,1})for(int j:{0,1})for(int k:{0,1})
			upd(t[x].f[i][j],(ull)t[lc[x]].f[i][j]*t[rc[x]].f[i][k]);
	}
}
void ipushup(int x){
	if(op[x]){
		for(int i:{0,1})for(int j:{0,1})for(int k:{0,1}){
			upd(t[lc[x]].g[i][j],(ull)t[x].g[i][k]*t[rc[x]].f[j][k]);
			upd(t[rc[x]].g[j][k],(ull)t[x].g[i][k]*t[lc[x]].f[i][j]);
		}
	}else{
		for(int i:{0,1})for(int j:{0,1})for(int k:{0,1}){
			upd(t[lc[x]].g[i][j],(ull)t[x].g[i][j]*t[rc[x]].f[i][k]);
			upd(t[rc[x]].g[i][k],(ull)t[x].g[i][j]*t[lc[x]].f[i][j]);
		}
	}
	memset(t[x].g,0,sizeof(t[x].g));
}
vector<int>seq;

void dfs(int x){
	sz[x]=1; 
	if(x!=1) t[x].f[1][0]=t[x].f[0][1]=t[x].f[0][0]=1;
	else t[x].f[0][0]=t[x].f[0][1]=1;
	for(auto y:E[x]){
		dfs(y); ff[y]=x;
		sz[x]+=sz[y];
		if(!son[x]||sz[y]>sz[son[x]])son[x]=y;
	}
}
int merge(int x,int y,int o){
	// cout<<"link "<<x<<","<<y<<","<<o<<endl;
	++id; lc[id]=x,rc[id]=y,op[id]=o;
	fa[x]=fa[y]=id; pushup(id);
	return id;
}
int build(int l,int r,int o){
	if(l==r) return seq[l];
	int sum=0, cur=0, cut=r-1;
	for(int i=l;i<=r;i++) sum+=sz[seq[i]];
	for(int i=l;i<r;i++){
		cur+=sz[seq[i]];
		if(2*cur>=sum){ cut=i; break; }
	}
	return merge(build(l,cut,o),build(cut+1,r,o),o);
}
int build(int x){
	vector<int>now; now.pb(x);
	for(;son[x];x=son[x]){
		vector<int>cur;
		for(auto y:E[x])
			if(y!=ff[x]&&y!=son[x]) cur.pb(build(y));
		if(cur.empty()) now.pb(son[x]);
		else swap(seq,cur),now.pb(merge(son[x],build(0,seq.size()-1,0),0));
	}
	swap(seq,now);
	return build(0,seq.size()-1,1);
}
void procedure(){
	n=id=read();
	for(int i=2;i<=n;i++)p[i]=read(),E[p[i]].pb(i);
	for(int i=1;i<=n;i++)v[i].fi=read(),v[i].se=i;
	dfs(1); build(1);
	
	// cout<<t[id].f[0][1]<<endl;

	sort(v+1,v+n+1);
	
	for(int i=n;i>=1;i--){
		int nd=v[i].se;
		if(i==n){
			addmod(t[id].g[0][0]+=v[i].fi);
			addmod(t[id].g[0][1]+=v[i].fi);
		}else{
			addmod(t[id].g[0][0]+=v[i].fi-v[i+1].fi+mod);
			addmod(t[id].g[0][1]+=v[i].fi-v[i+1].fi+mod);
		}

		stack<int>stk;
		for(int x=fa[nd];x;x=fa[x]) stk.push(x);
		while(!stk.empty()) ipushup(stk.top()),stk.pop();

		ans[nd]=t[nd].g[0][1];
		t[nd].f[0][1]=0;
		while(fa[nd]) nd=fa[nd], pushup(nd);
	}
	for(int i=1;i<=n;i++)
		printf("%d ",ans[i]);
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