// created time: 2026-03-31 16:38:59
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

int n,m,a[2000005];
vector<int>E[2000005];

struct Node{
	ll f[2]; int sz;
	Node(){ memset(f,0,sizeof(f)),sz=0; }
}t[2000005];
int lc[2000005],rc[2000005],fa[2000005],op[2000005],id;

inline Node operator* (const Node& A,const Node& B){
	Node C; C.sz=A.sz+B.sz;
	for(int y:{0,1})
		C.f[y]=max(C.f[y],A.f[0]+B.f[y]);
	C.f[1]=max(C.f[1],A.f[1]);
	return C;
}
inline Node operator+ (const Node& A,const Node& B){
	Node C; C.sz=A.sz+B.sz;
	for(int x:{0,1})
		C.f[x]=A.f[x]+B.f[1];
	return C;
}
int sz[2000005],son[2000005];
void dfs(int x){
	sz[x]=1;
	t[x].sz=1,t[x].f[0]=0,t[x].f[1]=a[x];
	for(auto y: E[x]){
		dfs(y),sz[x]+=sz[y];
		if(sz[y]>sz[son[x]])son[x]=y;
	}
}
void pushup(int x){
	if(op[x]==0) t[x]=t[lc[x]]*t[rc[x]];
	else t[x]=t[lc[x]]+t[rc[x]];
}
int newnode(int x,int y,int o){
	++id;
	lc[id]=x, rc[id]=y, op[id]=o;
	fa[x]=fa[y]=id,pushup(id); return id;
}
vector<int>seq;
int build(int l,int r,int o){
	if(l==r) return seq[l];
	int sum=0, cur=0, cut=r-1;
	for(int i=l;i<=r;i++)sum+=t[seq[i]].sz;
	for(int i=l;i<r;i++){
		cur+=t[seq[i]].sz;
		if(2*cur>=sum) {cut=i; break;}
	}
	return newnode(build(l,cut,o),build(cut+1,r,o),o);
}
int build(int x){
	vector<int>now; now.pb(x);
	for(;son[x];x=son[x]){
		vector<int>cur;
		for(auto y:E[x]) if(y!=son[x]) cur.pb(build(y));
		if(cur.empty()) now.pb(son[x]);
		else{
			seq=cur;
			now.pb(newnode(son[x],build(0,(int)seq.size()-1,1),1));
		}
	}
	seq=now;
	return build(0,(int)seq.size()-1,0);
}
void procedure(){
	n=id=read(),m=read();
	for(int i=2;i<=n;i++) E[read()].pb(i);
	for(int i=1;i<=n;i++) a[i]=read();
	dfs(1);
	int rt=build(1);
	printf("%lld\n",t[rt].f[1]);
	while(m--){
		int x=read(),y=read();
		t[x].f[1]=y;
		while(fa[x]) x=fa[x],pushup(x);
		printf("%lld\n",t[rt].f[1]);
	}
	for(int i=1;i<=id;i++)t[i]=Node(),lc[i]=rc[i]=fa[i]=0;
	for(int i=1;i<=n;i++) E[i].clear(),son[i]=sz[i]=0;
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