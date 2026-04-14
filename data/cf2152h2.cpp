// created time: 2026-04-14 09:23:18
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
 
int n,q;
ll ans[250005],l;
pair<int,int> que[250005];
 
vector<pair<int,int>>E[250005];
 
struct Num{
	ll k,b;
	Num(){ k=b=0;} 
	Num(ll x,ll y){ k=x,b=y; }
	ll val(){ return k*l+b; }
};
inline Num operator+ (const Num &A, const Num &B){
	return Num(A.k+B.k,A.b+B.b);
}
ll tmp;
inline ll CEIL(ll x,ll y){ return (x+y-1)/y; }
inline void upd(Num A,Num B, Num &C){
	bool ret = A.val()<B.val();
	if(!ret) swap(A, B); C = B;
	// A.k * l + A.b >= B.k * l + B.b
	if(A.k<=B.k) return;
	// (A.k - B.k) * l >= B.b - A.b
	tmp = min(tmp, CEIL(B.b-A.b, A.k-B.k));
}
 
 
struct Node{
	Num a[2][2];
	Num *operator [](int x){ return a[x]; }
	const Num *operator [](int x)const{ return a[x]; }
}t[500005];
 
int lc[500005],rc[500005],fa[500005],op[500005],tim[500005],szt[500005],id;
int ff[250005],fw[250005],sz[250005],son[250005];
 
void pushup(int x){
	if(x <= n){
		t[x][1][1]=Num(1,-2*fw[x]);
		tim[x] = 2e9;
		return;
	}
	szt[x] = szt[lc[x]] + szt[rc[x]];
	tmp = 2e9;
	if(op[x]){
		for(int p:{0,1})for(int q:{0,1})
			upd(t[lc[x]][p][0]+t[rc[x]][0][q], t[lc[x]][p][1]+t[rc[x]][1][q], t[x][p][q]);
		tim[x] = min({tim[lc[x]], tim[rc[x]], (int)tmp});
	}else{
		for(int p:{0,1})for(int q:{0,1})
			upd(t[lc[x]][p][q]+t[rc[x]][p][0], t[lc[x]][p][q]+t[rc[x]][p][1], t[x][p][q]);
		tim[x] = min({tim[lc[x]], tim[rc[x]], (int)tmp});
	}
}
int newnode(int x,int y,int o){
	++id;
	lc[id]=x,rc[id]=y,op[id]=o;
	fa[x]=fa[y]=id, pushup(id);
	return id;
}
vector<int>seq;
int build(int l,int r,int o){
	if(l==r) return seq[l];
	int sum=0, cur=0, cut=r-1;
	for(int i=l;i<=r;i++) sum+=szt[seq[i]];
	for(int i=l;i<r;i++){
		cur+=szt[seq[i]];
		if(2*cur>=sum){
			cut=i; break;
		}
	}
	return newnode(build(l,cut,o),build(cut+1,r,o),o);
}
int build(int x){
	vector<int>now = {x};
	for(;son[x];x=son[x]){
		vector<int>cur;
		for(auto [y,w]:E[x])
			if(y!=ff[x]&&y!=son[x]) cur.pb(build(y));
		if(cur.empty()) now.pb(son[x]);
		else{
			swap(seq,cur);
			now.pb(newnode(son[x],build(0,(int)seq.size()-1,0),0));
		}
	}
	swap(seq,now);
	return build(0,(int)seq.size()-1,1);
}
void dfs(int x,int f){
	ff[x]=f,sz[x]=szt[x]=1;
	t[x][0][0] = Num(0,0);
	t[x][0][1] = Num(1,-fw[x]);
	t[x][1][0] = Num(0,-fw[x]);
	t[x][1][1] = Num(0,0);
	tim[x]=2*fw[x]; 
	son[x]=0;
	for(auto [y,w]:E[x]){
		if(y==f)continue;
		fw[y]=w;
		dfs(y,x),sz[x]+=sz[y];
		if(!son[x] || sz[y]>sz[son[x]]) son[x]=y;
	}
}
 
void update(int x){
	if(tim[x]>l) return;
	if(lc[x]) update(lc[x]);
	if(rc[x]) update(rc[x]);
	pushup(x);
}
void procedure(){
	n=id=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read(),w=read();
		E[u].pb(v,w),E[v].pb(u,w);
	}
	dfs(1,0);
	int rt = build(1);
	q=read();
	for(int i=1;i<=q;i++){
		que[i].fi=read(),que[i].se=i;
	}
	sort(que+1,que+q+1);
	for(int i=1;i<=q;i++){
		l=que[i].fi;
		update(rt);
		ans[que[i].se]=max(t[rt][0][0].val(), t[rt][0][1].val());
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);

	for(int i=1;i<=n;i++) E[i].clear(),ff[i]=fw[i]=sz[i]=son[i]=0;
	l=0;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	tim[0]=2e9;
	// math_init();
	while(T--) procedure();
	return 0;
}
