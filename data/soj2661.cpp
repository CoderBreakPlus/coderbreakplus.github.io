// created time: 2026-10-22 18:41:48
#include<bits/stdc++.h>
#include"path.h"
#ifdef LOCAL
#include"grader.cpp"
#endif
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

mt19937 rnd;
const int N=2e5;

struct Tree{
	int lc=0,rc=0,fa=0,sz=0,p=0,bg=0,ed=0,sum=0,val=0;
	unsigned key=0;
	bool tag=0;
}t[N+5];

int bel[2*N+5],mch[2*N+5],res[N+5],pw[N+5],ans,tot;
map<pair<int,int>,int>mp;

void pushup(int x){
	int lc=t[x].lc,rc=t[x].rc;
	t[x].sz=t[lc].sz+t[rc].sz+1;
	t[x].bg=lc?t[lc].bg:t[x].p;
	t[x].ed=rc?t[rc].ed:(t[x].p^1);
	t[x].sum=((ull)t[lc].sum+t[rc].sum+pw[x])%mod;
	t[x].val=((ull)t[lc].val+t[rc].val+((t[x].p&1)?0:pw[x]))%mod;
	if(lc)t[lc].fa=x;
	if(rc)t[rc].fa=x;
}
void upd(int x){
	if(!x)return;
	swap(t[x].lc,t[x].rc),swap(t[x].bg,t[x].ed);
	addmod(t[x].val=t[x].sum+mod-t[x].val);
	t[x].p^=1,t[x].tag^=1;
}
void pushdown(int x){
	if(t[x].tag)
		upd(t[x].lc),upd(t[x].rc),t[x].tag=0;
}
void flip(int x){
	ans=(ans+(ull)t[x].sum+2*mod-2*t[x].val)%mod;
	upd(x);
}
int merge(int x,int y){
	if(!x||!y)return x^y;
	if(t[x].key>t[y].key){
		pushdown(x);
		t[x].rc=merge(t[x].rc,y);
		pushup(x); return x;
	}else{
		pushdown(y);
		t[y].lc=merge(x,t[y].lc);
		pushup(y); return y;
	}
}
void split(int x,int k,int &a,int &b){
	if(!x){ a=b=0; return; }
	pushdown(x);
	if(t[t[x].lc].sz>=k){
		b=x;split(t[x].lc,k,a,t[x].lc);
	}else{
		a=x;split(t[x].rc,k-t[t[x].lc].sz-1,t[x].rc,b);
	}
	pushup(x);
	t[a].fa=t[b].fa=0;
}
int getroot(int x){ while(t[x].fa)x=t[x].fa; return x; }
void pushto(int x){ if(t[x].fa)pushto(t[x].fa); pushdown(x); }

int getrank(int x){
	pushto(x);
	int k=t[t[x].lc].sz+1;
	while(t[x].fa){
		int y=t[x].fa;
		if(t[y].rc==x)k+=t[t[y].lc].sz+1;
		x=y;
	}
	return k;
}
void join(int p,int q){
	int x=getroot(p>>1),y=getroot(q>>1);
	mch[p]=q,mch[q]=p;
	if(x==y)return;
	if(t[x].ed!=p) flip(x);
	if(t[y].bg!=q) flip(y);
	merge(x,y);
}
void expose(int p){
	if(!p)return;
	int v=bel[p],q=res[v];
	if(q) res[v]=0,join(p,q);
	else res[v]=p;
}

void init(int n,int q){
	pw[0]=1;
	for(int i=1;i<=q;i++)addmod(pw[i]=pw[i-1]*2);
	rnd.seed(114514);
}
void add(int u,int v,int i){
	tot=i,mp[{u,v}]=i;
	int p=2*i,q=2*i+1;
	bel[p]=u,bel[q]=v;
	t[i].p=p,t[i].key=rnd(),pushup(i);
	addmod(ans+=pw[i]);
	expose(p),expose(q);
}
void del(int u,int v){
	int i=mp[{u,v}];mp.erase({u,v});
	int p=2*i,q=2*i+1;

	int r=getroot(i),k=getrank(i),lf,rh;
	bool cir=(mch[t[r].bg]==t[r].ed);
	split(r,k-1,lf,rh),split(rh,1,i,rh);
	if(cir) merge(rh,lf);
	addmod(ans+=mod-t[i].val);

	int a=mch[p],b=mch[q];
	mch[p]=mch[q]=0;
	if(a) mch[a]=0,expose(a); else res[u]=0;
	if(b) mch[b]=0,expose(b); else res[v]=0;
	bel[p]=bel[q]=0;
}
int query(){ return ans; }
vector<int>s; 
void print(int x){
	if(!x) return;
	pushdown(x);
	print(t[x].lc);
	if(~t[x].p&1) s.pb(x);
	print(t[x].rc);
}
vector<int> query_detail(){
	s.clear();
	for(int i=1;i<=tot;i++){
		if(bel[2*i]&&!t[i].fa)
			print(i);
	}
	return s;
}