// created time: 2026-11-13 07:31:19
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
const int M=1e6;
int n,m,c[500005];
vector<tuple<int,int,int>>v[500005];

int val[4000005],cnt[4000005];
ll ans[500005];
void pushup(int p,int l,int r){
	if(l<r)val[p]=val[p<<1]+val[p<<1|1];
	else val[p]=0;
	if(cnt[p]>0)val[p]=r-l+1;
}
void update(int p,int l,int r,int ql,int qr,int v){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){
		cnt[p]+=v;
		pushup(p,l,r);
		return;
	}
	int mid=(l+r)>>1;
	update(p<<1,l,mid,ql,qr,v);
	update(p<<1|1,mid+1,r,ql,qr,v);
	pushup(p,l,r);
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++)c[i]=read();
	for(int i=1;i<=n;i++){
		int l=read(),r=read(),k=read();
		while(k--)v[read()].pb(i,l,r);
	}	
	ll all=0;
	for(int x=1;x<=m;x++){
		for(auto [i,l,r]: v[x]) update(1,1,M,l,r,1);
		int tmp;
		all+=(ll)c[x]*(tmp=val[1]);
		for(auto [i,l,r]: v[x]){
			update(1,1,M,l,r,-1);
			ans[i]+=(ll)c[x]*(tmp-val[1]);
			update(1,1,M,l,r,1);
		}
		for(auto [i,l,r]: v[x]) update(1,1,M,l,r,-1);
	}
	for(int i=1;i<=n;i++)
		printf("%lld ",all-ans[i]);
	puts("");
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