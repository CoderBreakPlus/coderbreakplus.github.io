// created time: 2026-09-30 07:58:24
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
const int N = 500005;
struct LinkCutTree{
	int ch[N][2],fa[N],rev[N],siz[N],stk[N];
	bool isRoot(int x){
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	void pushUp(int x){
		siz[x]=siz[ch[x][0]]+siz[ch[x][1]]+1;
	}
	void pushReverse(int x){
		if(!x)return;
		swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}
	void pushDown(int x){
		if(!rev[x])return;
		pushReverse(ch[x][0]);
		pushReverse(ch[x][1]);
		rev[x]=0;
	}
	void rotate(int x){
		int y=fa[x],z=fa[y],k=ch[y][1]==x,w=ch[x][k^1];
		if(!isRoot(y))ch[z][ch[z][1]==y]=x;
		ch[x][k^1]=y;
		ch[y][k]=w;
		if(w)fa[w]=y;
		fa[y]=x;
		fa[x]=z;
		pushUp(y);
		pushUp(x);
	}
	void splay(int x){
		int y=x,top=0;
		stk[++top]=y;
		while(!isRoot(y))stk[++top]=y=fa[y];
		while(top)pushDown(stk[top--]);
		while(!isRoot(x)){
			y=fa[x];
			int z=fa[y];
			if(!isRoot(y))rotate((ch[y][1]==x)==(ch[z][1]==y)?y:x);
			rotate(x);
		}
	}
	void access(int x){
		for(int y=0;x;y=x,x=fa[x]){
			splay(x);
			ch[x][1]=y;
			pushUp(x);
		}
	}
	void makeRoot(int x){
		access(x);
		splay(x);
		pushReverse(x);
	}
	void split(int x,int y){
		makeRoot(x);
		access(y);
		splay(y);
	}
	void link(int x,int y){
		// cout<<"link "<<x<<"<->"<<y<<endl;
		makeRoot(x);
		fa[x]=y;
	}
	void cut(int x,int y){
		// cout<<"cut "<<x<<"<->"<<y<<endl;
		makeRoot(x);
		access(y);
		splay(y);
		ch[y][0]=fa[x]=0;
		pushUp(y);
	}
	int kth(int x,int k){
		// assert(siz[x]>=k);
		while(1){
			pushDown(x);
			if(siz[ch[x][0]]>=k)x=ch[x][0];
			else if(siz[ch[x][0]]+1==k){
				splay(x);
				return x;
			}else{
				k-=siz[ch[x][0]]+1;
				x=ch[x][1];
			}
		}
	}
	int kth_path(int x,int y,int k){
		split(x,y);
		return kth(y,k);
	}
	void init(int x){
		ch[x][0]=ch[x][1]=fa[x]=rev[x]=0;
		siz[x]=1;
	}
}T;
int n,a[250005],b[250005],c[250005],d[250005],ans[250005],eid;
set<pair<int,int>>E[250005];
set<int>G[250005];
int fa[250005];

int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }
void procedure(){
	n=eid=read();
	for(int i=1;i<=n;i++) fa[i]=i;
	for(int i=1;i<n;i++){
		a[i]=read(),b[i]=read();
		E[a[i]].emplace(b[i],i),E[b[i]].emplace(a[i],i);
	}
	for(int i=1;i<2*n;i++) T.init(i);
	for(int i=1;i<n;i++){
		++eid;
		c[i]=read(),d[i]=read();
		T.link(c[i],eid),T.link(eid,d[i]);
		G[c[i]].emplace(eid),G[d[i]].emplace(eid);
	}

	queue<int>q;
	for(int i=1;i<=n;i++)if(E[i].size()==1)q.push(i);
	
	while(!q.empty()){
		int x=q.front();q.pop();
		if(E[x].empty())continue;
		auto [y,i]=*E[x].begin(); E[x].erase({y,i});
		E[y].erase({x,i}); if(E[y].size()==1)q.push(y);

		// cout<<"here edge "<<x<<"->"<<y<<" id = "<<i<<endl;

		int X=find(x),Y=find(y);
		// cout<<"here "<<X<<"->"<<Y<<endl;
		int edge=T.kth_path(X,Y,2), Z=T.kth_path(X,Y,3);
		// cout<<"on T2: "<<X<<"->"<<edge<<"->"<<Z<<endl;
		ans[edge-n]=i;

		// cout<<"ans "<<edge-n<<" = "<<i<<endl;
		T.cut(X,edge),T.cut(edge,Z);
		G[X].erase(edge),G[Z].erase(edge);

		if(G[X].size()<G[Y].size()){
			fa[X]=Y;
			for(int e:G[X]){
				T.cut(X,e),T.link(Y,e);
				G[Y].emplace(e);
			}
			G[X].clear();
		}else{
			fa[Y]=X;
			for(int e:G[Y]){
				T.cut(Y,e),T.link(X,e);
				G[X].emplace(e);
			}
			G[Y].clear();
		}
	}
	printf("%d\n",n-1);
	for(int i=1;i<n;i++)
		printf("%d %d %d %d\n",a[ans[i]],b[ans[i]],c[i],d[i]);
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