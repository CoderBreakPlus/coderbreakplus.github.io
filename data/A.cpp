// created time: 2026-04-28 10:10:11
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
const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}
vector<int>E[100005];
int n,k,m,f[20][100005],dep[100005],coef[100005],ans[100005],dfn[100005],bfn[100005],sb[100005],tim;

int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
int dis(int x,int y){
	return dep[x]+dep[y]-2*dep[LCA(x,y)];
}
void dfs(int x,int fa){
	dfn[x]=(++tim); f[0][dfn[x]]=fa;
	for(auto y:E[x]){
		if(y==fa)continue;
		dep[y]=dep[x]+1;
		dfs(y,x);
	}
}
int rt,sz[100005],vis[100005],mxs[100005],jp[100005],wh;

void findcent(int x,int fa){
	sz[x]=1,mxs[x]=0;
	for(auto y:E[x]){
		if(vis[y]||y==fa)continue;
		findcent(y,x);
		sz[x]+=sz[y];
		mxs[x]=max(mxs[x],sz[y]);
	}
	mxs[x]=max(mxs[x],wh-sz[x]);
	if(mxs[x]<mxs[rt])rt=x;
}
void solve(int x){
	vis[x]=1; int cur=wh;
	for(auto y:E[x]){
		if(vis[y])continue;
		rt=0,wh=(sz[y]>cur?cur-sz[x]:sz[y]);
		findcent(y,x);
		jp[rt]=x;
		// cout<<rt<<"->"<<x<<endl;
		solve(rt);
	}
}
int val[10000005],lc[10000005],rc[10000005],cnt;
int gen[100005],gen2[100005];
void update(int l,int r,int x,int &pos){
	if(!pos)pos=++cnt;
	val[pos]++;
	if(l==r)return;
	int mid=(l+r)>>1;
	if(x<=mid)
		update(l,mid,x,lc[pos]);
	else
		update(mid+1,r,x,rc[pos]);
}
int query(int l,int r,int ql,int qr,int pos){
	if(!pos||r<ql||qr<l)return 0;
	if(ql<=l && r<=qr) return val[pos];
	int mid=(l+r)>>1;
	return query(l,mid,ql,qr,lc[pos])+query(mid+1,r,ql,qr,rc[pos]);
}
void procedure(){
	n=read(),k=read(),m=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		E[u].pb(v),E[v].pb(u);
	}
	dfs(1,0);
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	queue<int>q;q.push(1);tim=0;
	while(!q.empty()){
		int x=q.front();q.pop();
		bfn[x]=++tim, sb[tim]=x;
		for(auto y:E[x]){
			if(!bfn[y]) q.push(y);
		}
	}
	mxs[0]=wh=n,rt=0;
	findcent(1,0);
	solve(rt);

	for(int i=1;i<=n;i++){
		int x=sb[i];
		// cout<<"x="<<x<<endl;
		int cur=sb[i];
		ans[x]=query(0,n-1,0,k,gen[x]);
		while(jp[cur]){
			int nd=dis(x,jp[cur]);
			int v1=query(0,n-1,0,k-nd,gen[jp[cur]]);
			int v2=query(0,n-1,0,k-nd,gen2[cur]);
			ans[x]+=v1-v2;
			// cout<<"at "<<jp[cur]<<" find "<<v1<<"-"<<v2<<endl;
			cur=jp[cur];
		}
		// cout<<x<<" ans="<<ans[x]<<endl;

		cur=x;
		while(cur){
			int nd=dis(x,cur);
			update(0,n-1,nd,gen[cur]);
			if(jp[cur])update(0,n-1,dis(x,jp[cur]),gen2[cur]);
			// cout<<"upd on "<<cur<<" with "<<nd<<endl;
			cur=jp[cur];
		}
	}

	coef[0]=1;
	for(int i=1;i<=1e5;i++){
		coef[i]=(2ull*coef[i-1]+mod-binom(i-1,m-1))%mod;
	}

	int out=0;
	for(int i=1;i<=n;i++)
		addmod(out+=coef[ans[i]]);
	printf("%d\n",out);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}