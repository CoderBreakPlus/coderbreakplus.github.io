// created time: 2026-10-21 07:27:27
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

int n,d,a[500005],ord[500005];
const int N=1e6+5;
struct LinkCutTree{
	int ch[N][2],fa[N],rev[N],stk[N];
	ll val[N],sum[N];
	inline bool isRoot(int x){
		return ch[fa[x]][0]!=x&&ch[fa[x]][1]!=x;
	}
	inline void pushUp(int x){
		sum[x]=sum[ch[x][0]]+sum[ch[x][1]]+val[x];
	}
	inline void pushReverse(int x){
		if(!x)return;
		swap(ch[x][0],ch[x][1]);
		rev[x]^=1;
	}
	inline void pushDown(int x){
		if(!rev[x])return;
		pushReverse(ch[x][0]);
		pushReverse(ch[x][1]);
		rev[x]=0;
	}
	inline void rotate(int x){
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
	inline void splay(int x){
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
	inline void access(int x){
		for(int y=0;x;y=x,x=fa[x]){
			splay(x);
			ch[x][1]=y;
			pushUp(x);
		}
	}
	inline void makeRoot(int x){
		access(x);
		splay(x);
		pushReverse(x);
	}
	inline void split(int x,int y){
		makeRoot(x);
		access(y);
		splay(y);
	}
	inline void link(int x,int y){
		makeRoot(x);
		fa[x]=y;
	}
	inline void cut(int x,int y){
		makeRoot(x);
		access(y);
		splay(y);
		ch[y][0]=fa[x]=0;
		pushUp(y);
	}
	inline void initNode(int x,ll w=0){
		ch[x][0]=ch[x][1]=fa[x]=rev[x]=0;
		val[x]=sum[x]=w;
	}
	inline void modifyWeight(int x,ll w){
		access(x);
		splay(x);
		val[x]=w;
		pushUp(x);
	}
	inline ll queryDistance(int x,int root){
		split(root,x);
		return sum[x];
	}
}T;
void procedure(){
	n=read(),d=read();
	for(int i=1;i<=n;i++) a[i]=read(),ord[i]=i;
	for(int i=1;i<=n+1;i++) T.initNode(i);

	for(int i=1;i<=n;i++){
		int tmp=n+1+i;
		T.initNode(tmp,1);
		T.link(i,tmp),T.link(tmp,min(n+1,i+d));
	}
	sort(ord+1,ord+n+1,[&](int x,int y){ return a[x]<a[y]; });

	set<int>S;for(int i=1;i<=n+1;i++)S.emplace(i);
	ll ans=0;
	for(int I=1;I<=n;I++){
		ans+=(ll)T.queryDistance(*S.begin(),n+1)*(a[ord[I]]-a[ord[I-1]]);
		int i=ord[I];
		auto it=S.find(i);
		T.cut(i,n+1+i),T.link(i,*next(it));
		S.erase(it);
	}
	printf("%lld\n",ans);
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