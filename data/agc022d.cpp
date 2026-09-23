// created time: 2026-09-23 16:28:17
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

const int N=3e5+5;
int n,st[N],tp;
ll a[N],t[N],L,ans;
bool l[N],r[N],vis[N];

void procedure(){
	n=read(),L=read(),ans=n+1;
	for(int i=1;i<=n;++i) a[i]=read();
	for(int i=1;i<=n;++i) {
		t[i]=read(),ans+=t[i]/(2*L),t[i]%=2*L;
		l[i]=(2*a[i]>=t[i]),r[i]=(2*(L-a[i])>=t[i]);
	}
	if(r[n]) --ans;
	for(int i=1;i<n;++i) if(!t[i]) --ans,vis[i]=1;
	for(int i=1,hd=1,tl=0;i<n;++i) {
		if(l[i]&&r[i]&&!vis[i]) st[++tl]=i;
		if(!l[i]&&r[i]&&hd<=tl) --ans,vis[st[hd++]]=1;
	}
	tp=0;
	for(int i=n-1,hd=1,tl=0;i;--i) {
		if(l[i]&&r[i]&&!vis[i]) st[++tl]=i;
		if(l[i]&&!r[i]&&hd<=tl) --ans,vis[st[hd++]]=1;
	}
	int c=0;
	for(int i=1;i<n;++i) c+=l[i]&&r[i]&&!vis[i];
	ans-=c/2;
	printf("%lld\n",2*L*ans);
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