// created time: 2026-11-19 10:05:46
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
const int M=1.3e6+5;
int n,q,fa[M],sz[M],cnt[M],vis[M],pt[M];
bool mk[M];

int find(int x){
	if(x!=fa[x])fa[x]=find(fa[x]);
	return fa[x];
}
void procedure(){
	n=read(),q=read();
	int id=n;
	for(int i=1;i<=n;i++)fa[i]=i,pt[i]=i,sz[i]=1;

	while(q--){
		char s[5];
		scanf("%s",s);
		if(s[0]=='+'){
			int a=read(),b=read();
			int fx=find(pt[a]),fy=find(pt[b]);
			if(fx!=fy){
				sz[fx]+=sz[fy];
				cnt[fx]+=cnt[fy];
				fa[fy]=fx;
				vis[fx]|=vis[fy];
			}else{
				vis[fx]=1;
			}
		}else if(s[0]=='-'){
			int a=read();
			int fx=find(pt[a]);
			mk[pt[a]]=1;

			cnt[fx]++;
			pt[a]=++id;
			sz[id]=1,fa[id]=id;
		}else{
			int a=read();
			int fx=find(pt[a]);

			if(vis[fx])putchar('1');
			else{
				if(cnt[fx]==sz[fx]-1)putchar('0');
				else putchar('?');
			}
		}
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