// created time: 2026-05-06 14:01:17
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

int n,a[100005],b[100005],p[100005];
int fa[100005],ip[100005];
int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }

void link(int x,int y){
	p[x]=y,ip[y]=x;
	assert(y>=a[x]);
	fa[find(x)]=find(y);
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read(),fa[i]=i;
	for(int i=1;i<=n;i++)b[i]=i;
	sort(b+1,b+n+1,[](int x,int y){ return a[x]<a[y]; });

	for(int i=1;i<=n;i++){
		if(a[b[i]]>i){
			puts("No");
			return;
		}
		link(b[i],i);
	}

	int pt=n, node=n;
	while(1){
		while(pt>=1 && find(pt) == find(n)){
			if(a[pt]<a[node]) node=pt;
			pt--;
		}
		if(!pt) break;

		if(a[node]>pt){
			puts("No");
			return;
		}
		int x=ip[pt],y=p[node];
		link(node,pt), link(x,y);
	}
	puts("Yes");
	int x=1;
	do{
		printf("%d ",x);
		x=p[x];
	}while(x!=1);
	puts("");
	fflush(stdout);
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