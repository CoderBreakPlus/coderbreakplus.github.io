// created time: 2026-05-14 07:23:15
// https://qoj.ac/contest/2559/problem/14425
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
#define pii pair<int,int>
int n,a[100005],ans[100005];

pii c[100005],dp[100005];

void upd(int x,pii w){
	while(x<=n){
		chkmax(c[x],w);
		x+=(x&-x);
	}
}
pii qry(int x){
	pii res={0,0};
	while(x){
		chkmax(res,c[x]);
		x-=(x&-x);
	}
	return res;
}
pii calc(int v){
	for(int i=1;i<=n;i++)c[i]={0,0};

	pii tmp={0,0};
	for(int i=1;i<=n;i++){
		pii cur=qry(a[i]-1);
		dp[i]=(pii){cur.fi+1,cur.se};
		if(i>1) chkmax(dp[i], (pii){tmp.fi-v+1,tmp.se+1});
		upd(a[i],dp[i]), chkmax(tmp,dp[i]);
	}
	return {tmp.fi-v,tmp.se+1};
}
void solve(int l,int r,int cl,int cr){
	if(l+1>=r)return;
	if(cl==cr){
		for(int i=l;i<=r;i++)ans[i]=cl;
		return;
	}
	int mid=(l+r)>>1;
	ans[mid]=calc(mid).se;
	solve(l,mid,cl,ans[mid]);
	solve(mid,r,ans[mid],cr);
}

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	solve(0,n,ans[0]=calc(0).se,ans[n]=calc(n).se);

	// for(int i=0;i<=n;i++)cout<<ans[i]<<" ";cout<<endl;
	int pt=n, val=calc(n).fi;
	for(int i=1;i<=n;i++){
		if(pt && ans[pt]<i){
			while(pt && ans[pt]<i) pt--;
			val=calc(pt).fi;
		}
		printf("%d ",val+pt*i);
	}
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