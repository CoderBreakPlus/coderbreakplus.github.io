// created time: 2026-10-21 19:27:32
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

int n1,n2,n,m,c,ans;
int pw[400005],fa[400005],bel[400005],tag[400005],sum[400005][2];

int find(int x){
	if(!fa[x]) return x; if(!fa[fa[x]]) return fa[x];
	int f=find(fa[x]); tag[x]^=tag[fa[x]];
	return fa[x]=f;
}
int qry(int x){if(!fa[x]) return tag[x]; int f=find(x); return tag[x]^tag[f]; }

void rev(int x){
	x=find(x);
	addmod(ans+=mod-sum[x][tag[x]]);
	tag[x]^=1;
	addmod(ans+=sum[x][tag[x]]);
}
void merge(int y,int x){
	x=find(x),y=find(y);if(x==y)return;
	addmod(ans+=mod-sum[x][tag[x]]),addmod(ans+=mod-sum[y][tag[y]]);
	fa[y]=x;
	addmod(sum[x][tag[x]]+=sum[y][tag[y]]);
	addmod(sum[x][tag[x]^1]+=sum[y][tag[y]^1]);
	tag[y]^=tag[x];
	addmod(ans+=sum[x][tag[x]]);
}
void add(int u,int v){
	// cout<<"add "<<u<<","<<v<<endl;
	int i=++c;
	sum[i][0]=pw[i]; addmod(ans+=pw[i]);
	if(!bel[u]&&!bel[v]){
		bel[u]=bel[v]=i;
		return;
	}
	if(!bel[u])swap(u,v);
	if(!bel[v]){
		if(!qry(bel[u])) rev(i);
		merge(i,bel[u]); bel[u]=0,bel[v]=i;
	}else{
		if(qry(bel[u])!=qry(bel[v])) rev(bel[v]);
		if(!qry(bel[u])) rev(i);
		merge(i,bel[u]),merge(i,bel[v]);
		bel[u]=bel[v]=0;
	}
}
void procedure(){
	pw[0]=1;
	for(int i=1;i<=4e5;i++) addmod(pw[i]=2*pw[i-1]);
	n1=read(),n2=read(),m=read(); n=n1+n2;

	// cout<<"FUCK1"<<endl;
	for(int i=1;i<=m;i++){
		int x=read(),y=n1+read();
		add(x,y);
	}
	int q=read();
	while(q--){
		int op=read();
		if(op==1){
			int x=read(),y=n1+read();
			add(x,y);
			printf("%d\n",ans);
		}else{
			int out=0;
			for(int i=1;i<=c;i++)if(!qry(i)) ++out;
			printf("%d ",out);
			for(int i=1;i<=c;i++)
				if(!qry(i)) printf("%d ",i);
			puts("");
		}
		fflush(stdout);
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