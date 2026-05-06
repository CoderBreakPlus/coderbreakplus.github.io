// created time: 2026-04-15 10:00:59
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

int n,vis[400005],sz[400005],tag[400005],mxs[400005],wh,rt;
vector<int>E[400005];
set<pair<int,int>>S;

int now[13], tp;
int cnt=0;
int upd(int x){
	int pos=0;
	for(int i=1;i<=12;i++)
		if(!now[i]){pos=i;break;}
	assert(pos);

	now[pos]=x;
	tag[x]=pos;
	
	printf("1 %d %d\n",pos,x);

	for(int i=1;i<=12;i++){
		if(i==pos||!now[i])continue;

		int p=now[i],q=now[pos];
		if(p>q)swap(p,q);
		if(S.count({p,q})) printf("2 %d %d\n",i,pos),S.erase({p,q});
	}

	return pos;
}
void undo(int x){ now[tag[x]]=0; }

void findcent(int x,int fa){
	sz[x]=1,mxs[x]=0;
	for(auto y:E[x]){
		if(vis[y]||y==fa)continue;
		findcent(y,x); sz[x]+=sz[y];
		mxs[x]=max(mxs[x],sz[y]);
	}
	mxs[x]=max(mxs[x],wh-sz[x]);
	if(!rt || mxs[x]<mxs[rt])
		rt=x;
}
int son[400005];
void dfs(int x,int fa){
	sz[x]=1,son[x]=0;
	for(auto y:E[x]){
		if(vis[y]||y==fa)continue;
		dfs(y,x);
		if(!son[x]||sz[y]>sz[son[x]])son[x]=y;
		sz[x]+=sz[y];
	}
}
void solve(int x){
	int cur=wh;
	rt=0; findcent(x,0);
	dfs(rt,0);

	int y=rt;
	vector<int>ret;
	while(y)ret.pb(y),y=son[y];
	reverse(ret.begin(),ret.end());

	for(auto w:E[rt]){
		if(vis[w]||w==son[rt])continue;
		if(!y||sz[w]>sz[y]) y=w;
	}
	while(y)ret.pb(y),y=son[y];
	for(auto to: ret) vis[to]=1;

	int mx=0;
	for(int i=0;i<ret.size();i++){
		upd(ret[i]);
		if(i>=1) undo(ret[i-1]);
		for(auto to:E[ret[i]])
			if(!vis[to]){
				wh=sz[to];
				mx=max(mx,sz[to]);
				solve(to);
			}
	}
	assert(3*mx<=cur);
	undo(ret.back());
}
void procedure(){
	n=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();if(u>v)swap(u,v);
		S.emplace(u,v);
		E[u].pb(v),E[v].pb(u);
	}
	printf("%d\n", 2*n-1);
	wh=n;
	solve(1);
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