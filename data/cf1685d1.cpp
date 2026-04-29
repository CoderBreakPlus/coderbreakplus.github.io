// created time: 2026-04-29 09:06:51
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

int n,p[405],q[405];
int w;

int fa[405];
int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]); return fa[x]; }
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)p[i]=read(),q[p[i]]=i,fa[i]=i;

	for(int i=1;i<=n;i++) fa[find(i)]=find(p[i]);
	for(int i=1;i<n;i++){
		if(find(i)!=find(i+1)){
			swap(q[i],q[i+1]);
			swap(p[q[i]],p[q[i+1]]);
			fa[find(q[i])]=find(q[i+1]);
		}
	}

	int x=1;
	do{
		printf("%d ",x);
		x=q[x];
	}while(x!=1);
	puts("");
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