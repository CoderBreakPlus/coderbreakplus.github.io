// created time: 2026-04-09 15:19:51
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

int n,m,k,prv[300005],nxt[300005];
int a[300005],fa[300005],b[300005],ban[300005],sz[300005];

int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }

void merge(int x,int y){
	x=find(x),y=find(y);if(x==y){ ban[x]=1;return; }
	fa[x]=y, ban[y]|=ban[x], sz[y]+=sz[x];
}
int buc[300005],sl[300005],t,dp[300005];
void procedure(){
	n=read(),m=read(),k=read();
	iota(fa+1,fa+k+1,1);
	fill(sz+1,sz+k+1,1);
	for(int i=1;i<=n;i++){
		int len=read();
		bool f=1;
		for(int x=1;x<=len;x++) b[x]=read(),buc[b[x]]++,f&=(buc[b[x]]<=1);
		for(int x=2;x<=len;x++){
			if(prv[b[x]]==b[x-1] && nxt[b[x-1]]==b[x]) continue;

			if(!prv[b[x]] && !nxt[b[x-1]]){
				prv[b[x]]=b[x-1];
				nxt[b[x-1]]=b[x];
				merge(b[x-1],b[x]);
			}else{
				merge(b[x-1],b[x]);
				ban[find(b[x])]=1;
			}
		}
		for(int x=1;x<=len;x++) buc[b[x]]--;
		if(!f) ban[find(b[1])]=1;
	}

	for(int i=1;i<=k;i++){
		if(find(i)==i && !ban[i]) buc[sz[i]]++;
	}
	for(int i=1;i<=k;i++)if(buc[i]) sl[++t]=i;

	dp[0]=1;
	for(int i=1;i<=m;i++){
		for(int j=1;j<=t;j++)
			if(i>=sl[j]) dp[i]=(dp[i]+1ull*dp[i-sl[j]]*buc[sl[j]])%mod;
	}
	printf("%d\n",dp[m]);
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