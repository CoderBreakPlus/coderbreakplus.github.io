// created time: 2026-10-08 10:22:05
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

int n,a[1000005],b[1000005],c[1000005],d[1000005];
int seq[1000005],tl,vis[1000005],ans[1000005];
void procedure(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),vis[i]=0;
	for(int i=1;i<=n;i++) b[read()]=i;
	for(int i=1;i<=n;i++) c[i]=read(),d[c[i]]=b[a[i]];

	// for(int i=1;i<=n;i++) cout<<d[i]<<" "; cout<<endl;

	int cnt=0;
	tl=0;
	for(int i=1;i<=n;i++){
		if(d[i]==i) {cnt++;continue;}
		if(vis[i])continue;
		int len=0;
		while(!vis[i]){
			vis[i]=1,len++;
			i=d[i];
		}
		seq[++tl]=len;
	}
	sort(seq+1,seq+tl+1);

	// for(int i=1;i<=tl;i++) cout<<seq[i]<<" "; cout<<endl;

	int all=0,hd=0;
	for(int i=cnt+1;i<=n;i++){
		all++;
		if(hd<tl && all>=seq[hd+1]) all-=seq[++hd];
		ans[i]=i-cnt-hd;
		if(all==1&&seq[tl]==2)ans[i]++;
	}
	ans[cnt]=0;
	for(int i=cnt-1;i>=0;i--){
		ans[i]=(cnt-i+1)/2;
	}
	ans[n-1]=-1;
	for(int i=n;i>=0;i--) printf("%d ",ans[i]); puts("");
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