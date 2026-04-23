// created time: 2026-04-23 07:45:21
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

int n,m,q,fa[600005],s;
int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]); return fa[x]; }

ll ans[600005];

vector<tuple<int,int,int>>edge;

int seq[300005],in[600005],tim,out[600005],x[600005],y[600005];
int lc[600005],rc[600005];

struct BIT{
	ll c[300005];
	void upd(ll x,ll w){
		while(x<=n){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	ll qry(ll x){
		// cout<<"x="<<x<<endl;
		ll ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
}B;

void dfs(int u){
	in[u]=tim;
	if(!lc[u] && !rc[u]){
		seq[++tim]=u;
	}else{
		in[u]=tim;
		dfs(lc[u]),dfs(rc[u]);
	}
	out[u]=tim;
}
void solve(int u){
	if(!lc[u]&&!rc[u]) return; // end

	ll ls=B.qry(out[lc[u]])-B.qry(in[lc[u]]);
	ll rs=B.qry(out[rc[u]])-B.qry(in[rc[u]]);
	// cout<<"at "<<u<<" have "<<ls<<" "<<rs<<endl;

	ans[lc[u]]=ans[u]+rs*(out[rc[u]]-in[rc[u]]);
	ans[rc[u]]=ans[u]+ls*(out[lc[u]]-in[lc[u]]);

	// cout<<"add "<<lc[u]<<" with "<<rs<<"*"<<(out[rc[u]]-in[rc[u]])<<endl;
	// cout<<"add "<<rc[u]<<" with "<<ls<<"*"<<(out[lc[u]]-in[lc[u]])<<endl;

	B.upd(out[x[u]], rs), B.upd(out[y[u]], ls);
	solve(lc[u]),solve(rc[u]);
}
void procedure(){
	n=s=read(),m=read(),q=read();
	for(int i=1;i<=n;i++)fa[i]=i;
	while(m--){
		int u=read(),v=read(),w=read();
		edge.pb(w,u,v);
	}	
	sort(edge.begin(), edge.end());
	for(auto [w,u,v]: edge){
		int x=find(u),y=find(v);
		if(x==y)continue;

		++s;
		fa[x]=fa[y]=fa[s]=s;
		lc[s]=x, rc[s]=y;

		::x[s]=u, ::y[s]=v;
	}
	// cout<<"shabi"<<endl;
	dfs(s);
	for(int i=1;i<=n;i++) B.upd(i,1);
	solve(s);

	while(q--){
		int x=read();
		printf("%lld\n", ans[x]);
	}
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