// created time: 2026-06-22 13:33:49
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
const int v=1e7;
int n,m,x[300005],c[300005],t[300005];
ll dp[300005];
ll F[20000005],*f=F+v;

void solve(int l,int r){
	if(l>=r)return;
	int mid=(l+r)>>1;
	solve(l,mid);

	vector<pair<int,int>>seq,ord;
	for(int i=l;i<=mid;i++)seq.pb(x[i],i);
	for(int i=mid+1;i<=r;i++)ord.pb(x[i],i);
	sort(seq.begin(),seq.end()),sort(ord.begin(),ord.end());
	
	std::function<void(int,int,int,int)> divide = [&](int l,int r,int ql,int qr){
		if(l>r)return;
		int x=(l+r)>>1,jc=0; ll val=-1e18;
		for(int i=ql;i<=qr;i++){
			if(dp[seq[i].se]+f[ord[x].fi-seq[i].fi]>val){
				val=dp[seq[i].se]+f[ord[x].fi-seq[i].fi];
				jc=i;
			}
		}
		chkmax(dp[ord[x].se], val-c[ord[x].se]);
		divide(l,x-1,jc,qr),divide(x+1,r,ql,jc);
	};
	divide(0,ord.size()-1,0,seq.size()-1);
	solve(mid+1,r);
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) x[i]=read();
	for(int i=1;i<=n;i++) c[i]=read();

	ll sum=0;
	for(int i=1;i<=m;i++) t[i]=read(),sum+=t[i];
	sort(t+1,t+m+1);
	
	int pt=0; ll cur=0;
	for(int i=-v;i<=v;i++){
		while(pt<m && t[pt+1]<=i) cur+=t[++pt];
		f[i]=(ll)i*pt-cur+(sum-cur)-(ll)i*(m-pt);
	}

	memset(dp,0xc0,sizeof(dp));
	dp[1]=-c[1];

	solve(1,n);
	printf("%lld\n",dp[n]);
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