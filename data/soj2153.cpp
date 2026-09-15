// created time: 2026-09-15 08:30:09
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
mt19937 rnd(1337);
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }

int n,m,a[200005],b[200005],p[200005];
vector<int>vec[200005];

int jump(int x,int k=1){ return (x+k-1)%n+1; }
int lc[200005],rc[200005],k[200005],sz[200005],fa[200005],val[200005];

void pushup(int p){
	if(lc[p])fa[lc[p]]=p;
	if(rc[p])fa[rc[p]]=p;
	sz[p]=sz[lc[p]]+sz[rc[p]]+val[p];
}
// int fuck=0;
int merge(int x,int y){
	if(!x||!y) return x^y;
	// cout<<"merging "<<x<<" "<<y<<endl;
	// fuck++;
	// if(fuck>100)exit(0);
	if(k[x]<k[y]){
		rc[x]=merge(rc[x],y);
		pushup(x); return x;
	}else{
		lc[y]=merge(x,lc[y]);
		pushup(y); return y;
	}
}
int kth(int x){
	int ret=sz[lc[x]],ok;
	while(fa[x]){
		ok=(rc[fa[x]]==x), x=fa[x];
		ret+=ok*(val[x]+sz[lc[x]]);
	}
	return ret;
}
void _split(int a,int k,int &x,int &y){
	if(!a){ x=y=0; return; }
	if(k>=val[a]+sz[lc[a]]){
		x=a;
		_split(rc[x],k-val[x]-sz[lc[x]],rc[x],y);
		pushup(x);
	}else{
		y=a;
		_split(lc[y],k,x,lc[y]);
		pushup(y);
	}
}
void split(int a,int k,int &x,int &y){
	_split(a,k,x,y);
	fa[x]=fa[y]=0;
}
void addsize(int x,int w){
	val[x]+=w;
	while(x) sz[x]+=w, x=fa[x];
}

void print(int x){
	// fuck++;
	// if(fuck>100)exit(0);
	if(!x)return;
	print(lc[x]);	
	// printf("x=%d, val=%d, lc=%d, rc=%d\n",x,val[x],lc[x],rc[x]);
	fflush(stdout);
	print(rc[x]);
}

void procedure(){
	n=read();

	for(int i=1;i<=n;i++) k[i]=rnd(),val[i]=sz[i]=1;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) b[i]=read(),vec[b[i]].pb(i);

	// cout<<"shabi"<<endl;
	for(int i=1;i<=n;i++) {
		int x=a[i];
		a[i]=vec[x].back(); vec[x].pop_back();
	}

	// for(int i=1;i<=n;i++) cout<<a[i]<<" "; cout<<endl;


	int rt=0,lst=0;
	for(int i=1;i<=n;i++) {
		if(i>1 && jump(lst,val[lst])==a[i]) addsize(lst,1);
		else{
			rt=merge(rt,lst=a[i]);
			// cout<<"insert "<<lst<<endl;
		}
	}
	// cout<<"done"<<endl;
	vector<tuple<int,int,int>>ans;

	print(rt);
	while(val[rt]!=n){
		int x=rt;while(rc[x])x=rc[x];
		int nxt=jump(x,val[x]);
		// cout<<"nxt = "<<nxt<<endl;

		int sz1=kth(nxt), sz2=n-val[x]-sz1;
		// cout<<"sz1 = "<<sz1<<" sz2 = "<<sz2<<endl;

		int a=0,b=0,c=0,d=0,e=0,f=0;
		split(rt,sz1,a,b);

		// cout<<"tree a"<<endl;
		// print(a);
		// cout<<"tree b"<<endl;
		// print(b);
		split(b,sz2,c,d);
		split(c,val[nxt],e,f);

		ans.pb(sz1,sz2,n-sz1-sz2);
		// cout<<"#op "<<sz1<<" "<<sz2<<" "<<n-sz1-sz2<<endl;
		// if(ans.size()>100)exit(0);
		val[x]+=val[nxt],sz[x]+=sz[nxt];
		lc[x]=rc[x]=fa[x]=0;

		// cout<<"tree a: "<<a<<" sz="<<sz[a]<<endl;

		int f1 = merge(x,f);
		rt=merge(f1,a);

		// print(rt);
	}

	// cout<<"rt = "<<rt<<endl;
	ans.pb(0, n-rt+1, rt-1);
	printf("%d\n",ans.size());
	for(auto [x,y,z]: ans){
		printf("%d %d %d\n",x,y,z);
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