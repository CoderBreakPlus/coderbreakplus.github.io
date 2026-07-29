// created time: 2026-07-29 19:00:45
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
const int N = 100005;

int n,dfn[N],out[N],tim;
int f[20][N],jp[20][N],dep[N];
vector<int>E[N];
vector<tuple<int,int,int>>G[N],GG[N];
int get(int x,int y){ return dfn[x]<dfn[y]?x:y; }
int LCA(int x,int y){
	if(x==y)return x;
	if((x=dfn[x])>(y=dfn[y]))swap(x,y);
	int p=lg2(y-x++);
	return get(f[p][x],f[p][y-(1<<p)+1]);
}
int dis(int x,int y){
	// cout<<x<<","<<y<<" dis="<<dep[x]+dep[y]-2*dep[LCA(x,y)]<<endl;
	return dep[x]+dep[y]-2*dep[LCA(x,y)];
}
void dfs(int x,int fa){
	dfn[x]=++tim,f[0][dfn[x]]=jp[0][x]=fa;
	for(int i=1;i<20;i++)jp[i][x]=jp[i-1][jp[i-1][x]];
	for(int y:E[x]){
		if(y==fa)continue;
		dep[y]=dep[x]+1,dfs(y,x);
	}
	out[x]=tim;
}

vector<tuple<int,int,int>>vec[N];
struct Seg{
	int mx[N<<2],tag[N<<2];
	void pushup(int p){
		mx[p]=max(mx[p<<1],mx[p<<1|1]);
	}
	void upd(int p,int v){
		mx[p]+=v,tag[p]+=v;
	}
	void pushdown(int p){
		if(tag[p]) upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=0;
	}
	void modify(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr){ upd(p,v); return; }
		int mid=(l+r)>>1; pushdown(p);
		modify(l,mid,ql,qr,v,p<<1),modify(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
}S;

void add_matrix(int x1,int x2,int y1,int y2,int v){
	// cout<<"add "<<x1<<" "<<x2<<" "<<y1<<" "<<y2<<" v="<<v<<endl;
	if(x1>x2||y1>y2)return;
	vec[x1].pb(y1,y2,v);
	vec[x2+1].pb(y1,y2,-v);
	vec[y1].pb(x1,x2,v);
	vec[y2+1].pb(x1,x2,-v);
}
void add(int x,int y,int w,int v){
	if(w){
		add_matrix(1,dfn[w]-1,dfn[x],out[x],v);
		add_matrix(out[w]+1,n,dfn[x],out[x],v);
	}else{
		add_matrix(dfn[x],out[x],dfn[y],out[y],v);
	}
}
void procedure(bool debug){
	n=read();
	tim=0;
	for(int i=1;i<n;i++){
		int u=read(),v=read(),a=read();
		E[u].pb(v),E[v].pb(u);
		G[a].pb(u,v,0);
	}
	dfs(1,0);

	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	for(int i=0;i<n;i++){
		for(int p=0;p<G[i].size();p++){ 
			for(int q=p+1;q<G[i].size();q++){
				int x=get<0>(G[i][p]),y=get<0>(G[i][q]);
				if(dis(get<1>(G[i][p]),y)>dis(x,y))x=get<1>(G[i][p]);
				if(dis(x,get<1>(G[i][q]))>dis(x,y))y=get<1>(G[i][q]);

				int d=dis(x,y);
				bool flg=0;
				for(int r=0;r<G[i].size();r++)if(r!=p&&r!=q){
					auto [a,b,w]=G[i][r];
					if(dis(x,a)+1+dis(b,y)==d || dis(x,b)+1+dis(a,y)==d){
						flg=1;
						break;
					}
				}
				if(!flg){
					int z=LCA(x,y);
					if(z==x||z==y){
						x=x+y-z;
						int w=x;
						for(int i=19;i>=0;i--)if(dep[jp[i][w]]>dep[z])w=jp[i][w];
						GG[i].pb(x,y,w);
					}else{
						GG[i].pb(x,y,0);
					}
				}
			}
		}
	}
	for(int i=0;i<n;i++){
		for(auto &[x,y,w]: G[i]){
			// cout<<"here "<<x<<" "<<y<<" "<<w<<endl;
			int z=LCA(x,y);
			if(z==x||z==y){
				x=x+y-z;
				w=x;
				for(int i=19;i>=0;i--)if(dep[jp[i][w]]>dep[z])w=jp[i][w];
			}
		}
	}
	int L=1,R=n,ans=0;
	while(L<=R){
		int mid=(L+R)>>1;
		// cout<<"mid="<<mid<<endl;
		for(int i=0;i<mid;i++){
			for(auto [x,y,w]: G[i]){
				// cout<<"add "<<x<<" "<<y<<" "<<w<<endl;
				add(x,y,w,1);
			}
			for(auto [x,y,w]: GG[i]){
				// cout<<"del "<<x<<" "<<y<<" "<<w<<endl;
				add(x,y,w,-1);
			}
		}
		bool ok=0;
		for(int i=1;i<=n+1;i++){
			for(auto [l,r,v]:vec[i]){
				S.modify(1,n,l,r,v,1);
			}
			ok|=(S.mx[1]==mid);
		}
		if(ok)ans=mid,L=mid+1;
		else R=mid-1;
		for(int i=1;i<=n+1;i++) vec[i].clear();
	}
	printf("%d\n",ans);
	
	for(int i=0;i<=n+1;i++){
		E[i].clear(),G[i].clear(),GG[i].clear();
		dfn[i]=dep[i]=0;
		for(int d=0;d<20;d++) jp[d][i]=0,f[d][i]=0;
	}
	tim=0;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	for(int i=1;i<=T;i++){
		procedure(i==8373);
	}
	return 0;
}