// created time: 2026-08-13 14:24:03
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

int n,m,q,p[100005];
bool ok[100005], vis[100005];
vector<int>E[100005];

int que[100005],hd,tl;
bool check(int mid){
	for(int i=1;i<=n;i++)ok[i]=1,vis[i]=0;
	for(int i=1;i<=mid;i++) ok[p[i]]=0;

	que[hd=tl=1]=1;
	while(hd<=tl){
		int x=que[hd++];
		for(int y:E[x])
			if(!vis[y]&&ok[y]) que[++tl]=y,vis[y]=1;
	}
	return vis[n];
}
void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++)E[i].clear();
	for(int i=1;i<=m;i++){
		int u=read(),v=read();
		E[u].pb(v);
	}	
	for(int i=1;i<=q;i++)p[i]=read();

	int L=0,R=q,ans=-1;
	while(L<=R){
		int mid=(L+R)>>1;
		if(check(mid)) {
			ans=mid;
			L=mid+1;
		}else R=mid-1;
	}
	if(ans==-1) puts("NO");
	else if(ans==q) puts("YES");
	else printf("%d\n",ans);
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