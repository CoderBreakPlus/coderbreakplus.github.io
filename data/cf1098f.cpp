// created time: 2026-06-02 08:22:06
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

int Q;
char s[200005];

int n,m,len[400005],fa[400005],son[400005][26],lst;
int mxs[400005],sz[400005],vis[400005],wh,tim,rt;
int l[400005],r[400005]; ll ans[400005];

struct Edge{
	int to,nxt;
}e[800005];
int hd[400005],tot,f[20][400005],dfn[400005];
int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
void add(int u,int v){
	e[++tot]=(Edge){v,hd[u]};
	hd[u]=tot;
}
void ins(int p,int v){
	len[p]=len[lst]+1;
	while(lst&&!son[lst][v]) son[lst][v]=p,lst=fa[lst];
	if(!son[lst][v]) son[lst][v]=p;
	else{
		int q=son[lst][v];
		if(len[q]==len[lst]+1) fa[p]=q;
		else{
			int u=++m;
			len[u]=len[lst]+1,fa[u]=fa[q];
			memcpy(son[u],son[q],sizeof(son[u]));
			fa[p]=fa[q]=u;
			while(son[lst][v]==q){
				son[lst][v]=u,lst=fa[lst];
			}
		}
	}
	lst=p;
}
void fuck(int x){
	f[0][dfn[x]=tim++]=fa[x];
	for(int i=hd[x];i;i=e[i].nxt)
		if(e[i].to!=fa[x]) fuck(e[i].to);
}
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}

void findcent(int x,int fa){
	sz[x]=1,mxs[x]=0;
	for(int i=hd[x];i;i=e[i].nxt){
		int y=e[i].to; if(y!=fa&&!vis[y]){
			findcent(y,x),sz[x]+=sz[y];
			chkmax(mxs[x],sz[y]);
		}
	}
	chkmax(mxs[x],wh-sz[x]);
	if(mxs[x]<mxs[rt]) rt=x;
}
int vec[400005],vt;
vector<int>sb[400005],qry[400005];
vector<ll>sc[400005];
int col[400005],id[400005];
void dfs(int x,int ff,int w){
	if(1<=x && x<=n) sb[w].pb(x);
	col[x]=w;
	for(int i=hd[x];i;i=e[i].nxt){
		int y=e[i].to;
		if(!vis[y] && y!=ff) dfs(y,x,w);
	}
}
int calc(int l,int r,int i){
	if(i<=l) return 0;
	// cout<<"contri "<<l<<" "<<r<<" "<<i<<endl;
	return min(r-i+1, len[LCA(l,i)]);
}
int tmp[400005];

void represent(int x){
	sort(sb[x].begin(), sb[x].end());
	sc[x].clear(); sc[x].resize(sb[x].size(),0);
	for(int i=0;i<sb[x].size();i++) sc[x][i]=(i?sc[x][i-1]:0)+sb[x][i];
}

ll calc(int l,int r,int v,int i){
	if(sb[i].empty())return 0;
	int x=upper_bound(sb[i].begin(),sb[i].end(),l)-sb[i].begin();
	int y=max(x,int(lower_bound(sb[i].begin(),sb[i].end(),r+1-v)-sb[i].begin()));
	ll fuck=(ll)(sb[i].size()-y)*(r+1)-(sc[i][sc[i].size()-1]-(y?sc[i][y-1]:0))+(ll)(y-x)*v;
	return fuck;
}
bool ext[400005];

struct BIT{
	const int N = 4e5;
	ll c[400005],sum;
	void upd(int x,int w){
		sum+=w;
		while(x<=N){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	ll qry(int x){
		ll ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
	ll iqry(int x){ return sum-qry(x); }
	void clr(int x){
		sum=0;
		while(x<=N&&c[x]) c[x]=0, x+=(x&-x);
	}
}B1,B2,B3;
void solve(int x){
	vis[x]=1,vt=0; bool ff=0;
	for(int i=hd[x];i;i=e[i].nxt){
		int y=e[i].to; if(!vis[y]){
			sb[y].clear(), qry[y].clear();
			if(fa[y]==x) vec[++vt]=y,id[y]=vt;
			else ff=1;
			dfs(y,x,y);
		}
	}
	for(int k: sb[fa[x]]) tmp[k]=len[LCA(x,k)];
	sb[m+1].clear();
	for(int j=1;j<=vt;j++) for(int k: sb[vec[j]])
		sb[m+1].pb(k);

	represent(m+1);
	for(int j=1;j<=vt;j++)
		represent(vec[j]);

	for(int i: qry[x]){
		int l=::l[i],r=::r[i];
		ext[i]=0;
		if(l==x){
			ans[i]+=calc(l,r,len[x],m+1);
			ext[i]=1;
			continue;
		}
		if(col[l]!=fa[x]){
			ans[i]+=calc(l,r,len[x],m+1)-calc(l,r,len[x],col[l]);
			ext[i]=1;
		}else{
			ans[i]+=calc(l,r,len[LCA(l,x)],m+1);
		}
		if(1<=x&&x<=n)ans[i]+=calc(l,r,x);
		qry[col[l]].pb(i);
	}

	if(ff){
		vector<int>&vc = sb[fa[x]];
		sort(vc.begin(), vc.end(), greater<int>());
		sort(qry[x].begin(), qry[x].end(), [](int x,int y){ return l[x]>l[y]; });
		int pt=0;		
		for(int i: qry[x])if(ext[i]){
			int l=::l[i],r=::r[i];

			while(pt<vc.size() && vc[pt]>l){
				int k=vc[pt++];
				B1.upd(tmp[k]+k, tmp[k]);
				B2.upd(tmp[k]+k, k);
				B3.upd(tmp[k]+k, 1);
			}
			ans[i]+=B1.qry(r+1)+B3.iqry(r+1)*(r+1)-B2.iqry(r+1);
		}
		for(int i=0;i<pt;i++){
			int k=vc[i];
			B1.clr(tmp[k]+k),B2.clr(tmp[k]+k),B3.clr(tmp[k]+k);
		}
	}
	int cur=wh;
	if(ff)vec[++vt]=fa[x];

	vector<int>copy(vec+1,vec+vt+1);
	for(int y:copy){
		if(sz[y]>sz[x]) wh=cur-sz[x];
		else wh=sz[y];
		rt=m+1, findcent(y,x);
		swap(qry[y], qry[rt]);
		solve(rt);
	}
}
void procedure(){
	scanf("%s",s+1); n=m=strlen(s+1);
	for(int i=n;i>=1;i--)ins(i,s[i]-'a');
	for(int i=1;i<=m;i++){
		add(fa[i],i),add(i,fa[i]);
	}
	fuck(0);
	for(int i=1;(1<<i)<=m;i++)
		for(int j=1;j<=m-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
	mxs[rt=m+1]=wh=m;
	findcent(0,-1);

	Q=read();
	for(int i=1;i<=Q;i++)
		l[i]=read(),r[i]=read(),qry[rt].pb(i);

	solve(rt);

	for(int i=1;i<=Q;i++){
		ans[i]+=r[i]-l[i]+1;
		ans[i]+=(ll)(n-r[i])*(n-r[i]-1)/2;
		printf("%lld\n",ans[i]);
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