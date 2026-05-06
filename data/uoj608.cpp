// created time: 2026-05-06 09:31:56
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
template<typename T>inline void chkmin(T &a,T b){ a=max(a,b); }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,m,q,fa[200005],dep[200005]; char s[100005];
vector<int>E[200005];

namespace SAM{
	int len[200005],fa[200005],son[200005][26],lst;
	inline void ins(int p,int v){
		len[p]=len[lst]+1;
		while(lst&&!son[lst][v]){
			son[lst][v]=p;
			lst=fa[lst];
		}
		if(!son[lst][v]){
			son[lst][v]=p;
		}else{
			int q=son[lst][v];
			if(len[q]==len[lst]+1){
				fa[p]=q;
			}else{
				int u=++m;
				len[u]=len[lst]+1,fa[u]=fa[q];
				memcpy(son[u],son[q],sizeof(son[u]));
				fa[p]=fa[q]=u;
				while(son[lst][v]==q){
					son[lst][v]=u;
					lst=fa[lst];
				}
			}
		}
		lst=p;
	}
}

int ql[100005],qr[100005],ans[100005];

vector<tuple<int,int,int>>c1[200005],c2[100005];
set<int>S[200005];
struct Seg{
	int val[800005];
	Seg(){ memset(val,0xc0,sizeof(val)); }

	void update(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr)return chkmax(val[p],v);
		int mid=(l+r)>>1;
		update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
	}
	int query(int l,int r,int x,int p){
		if(l==r)return val[p];
		int mid=(l+r)>>1,ret=val[p];
		if(x<=mid)chkmax(ret,query(l,mid,x,p<<1));else chkmax(ret,query(mid+1,r,x,p<<1|1));
		return ret;
	}
}t1,t2;

void modify(int l,int r,int d){
	// cout<<l<<" "<<r<<" "<<d<<endl;
	c1[l].pb(r+d,n,d),c2[l].pb(r,r+d-1,1-r);	
}
void dfs(int x){
	if(1<=x&&x<=n)S[x].emplace(x);
	for(auto y:E[x]){
		dfs(y);
		if(S[y].size()>S[x].size())swap(S[x],S[y]);
		for(auto w:S[y]){
			auto it=S[x].lower_bound(w);
			if(it!=S[x].end())modify(w,*it,dep[x]);
			if(it!=S[x].begin())modify(*prev(it),w,dep[x]);
		}
		for(auto w:S[y])S[x].emplace(w);S[y].clear();
	}
}

vector<int>qry[100005];
void procedure(){
	n=m=read(),q=read();
	scanf("%s",s+1);
	for(int i=n;i>=1;i--)SAM::ins(i,s[i]-'a');
	for(int i=1;i<=m;i++){
		fa[i]=SAM::fa[i];
		dep[i]=SAM::len[i];
		E[fa[i]].pb(i);
		// cout<<i<<" fa="<<fa[i]<<endl;
	}
	dfs(0);
	for(int i=1;i<=q;i++){
		ql[i]=read(),qr[i]=read();
		qry[ql[i]].pb(i);
	}
	for(int i=n;i>=1;i--){
		for(auto [l,r,w]:c1[i]) t1.update(1,n,l,r,w,1);
		for(auto [l,r,w]:c2[i]) t2.update(1,n,l,r,w,1);	

		for(int o:qry[i])
		chkmax(ans[o], max(t1.query(1,n,qr[o],1),qr[o]+t2.query(1,n,qr[o],1)));
	}
	for(int i=1;i<=q;i++)
		printf("%d\n",qr[i]-ql[i]+1-ans[i]);
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