// created time: 2026-06-19 09:23:02
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
ll n,h;
struct Node{
	ll x,y,s,e;
}a[200005];
const ll M = 1e5;

namespace sol1{
	ll dp[200005];

	ll lc[400005],rc[400005],cnt;
	ll val[400005];

	vector<tuple<ll,ll,ll>>vec[200005];

	void modify(ll l,ll r,ll ql,ll qr,ll v,ll &p){
		if(r<ql||qr<l)return;
		if(!p)p=++cnt;
		if(ql<=l&&r<=qr){
			chkmax(val[p],v);
			return;
		}
		ll mid=(l+r)>>1;
		modify(l,mid,ql,qr,v,lc[p]),modify(mid+1,r,ql,qr,v,rc[p]);
	}
	ll query(ll l,ll r,ll x,ll p){
		if(!p) return -4e18;
		if(l==r) return val[p];
		ll mid=(l+r)>>1;
		if(x<=mid) return max(val[p],query(l,mid,x,lc[p]));
		else return max(val[p],query(mid+1,r,x,rc[p]));
	}
	void solve(ll l,ll r){
		if(l==r)return;
		ll mid=(l+r)>>1;
		solve(l,mid);
		for(ll i=l;i<=mid;i++){
			ll L=mid+1,R=r,ans=-1;
			while(L<=R){
				ll Mid=(L+R)>>1;
				if(a[Mid].y-a[i].y<=a[i].e){
					ans=Mid;
					L=Mid+1;
				}else R=Mid-1;
			}
			if(~ans){
				vec[ans].pb(dp[i],max(-M,a[i].x-a[i].e),min(M,a[i].x+a[i].e));
			}
		}
		ll rt=0;
		for(ll i=r;i>mid;i--){
			for(auto [val,l,r]: vec[i])
				modify(-M,M,l,r,val,rt);
			chkmax(dp[i], a[i].s+query(-M,M,a[i].x,rt));
		}
		for(ll i=1;i<=cnt;i++)val[i]=-4e18,lc[i]=rc[i]=0; cnt=0;
		for(ll i=mid+1;i<=r;i++)vec[i].clear();
		solve(mid+1,r);
	}

	void main(){
		memset(val,0xc0,sizeof(val));
		for(ll i=1;i<=n;i++)dp[i]=a[i].s;
		solve(1,n);
		ll ans=0;
		for(ll i=1;i<=n;i++) chkmax(ans,dp[i]);
		printf("%lld\n",ans);
	}
}
namespace sol2{
	ll dp[200005];

	ll lc[400005],rc[400005],cnt;
	ll val[400005];

	vector<tuple<ll,ll,ll>>vec[200005];

	void modify(ll l,ll r,ll ql,ll qr,ll v,ll &p){
		if(r<ql||qr<l)return;
		if(!p)p=++cnt;
		if(ql<=l&&r<=qr){
			chkmax(val[p],v);
			return;
		}
		ll mid=(l+r)>>1;
		modify(l,mid,ql,qr,v,lc[p]),modify(mid+1,r,ql,qr,v,rc[p]);
	}
	ll query(ll l,ll r,ll x,ll p){
		if(!p) return -4e18;
		if(l==r) return val[p];
		ll mid=(l+r)>>1;
		if(x<=mid) return max(val[p],query(l,mid,x,lc[p]));
		else return max(val[p],query(mid+1,r,x,rc[p]));
	}
	int fa[200005],E;
	ll sb[200005];
	int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]); return fa[x]; }
	void solve(ll l,ll r){
		if(l>=r||find(l)==find(r))return;
		ll mid=(l+r)>>1;
		while(mid<r && find(mid)==find(mid+1)) mid++;
		if(mid==r){
			while(mid>l && find(mid-1)==find(mid)) mid--;
			mid--;
		}
		solve(l,mid);
		for(ll i=l;i<=mid;i++){
			ll L=mid+1,R=r,ans=-1;
			while(L<=R){
				ll Mid=(L+R)>>1;
				if(a[Mid].y-a[i].y<=a[i].e){
					ans=Mid;
					L=Mid+1;
				}else R=Mid-1;
			}
			if(~ans){
				vec[ans].pb(dp[find(i)],max(-M,a[i].x-a[i].e),min(M,a[i].x+a[i].e));
			}
		}
		ll rt=0;
		for(ll i=r;i>mid;i--){
			for(auto [val,l,r]: vec[i])
				modify(-M,M,l,r,val,rt);
			chkmax(dp[find(i)], sb[find(i)]+query(-M,M,a[i].x,rt));
		}
		for(ll i=1;i<=cnt;i++)val[i]=-4e18,lc[i]=rc[i]=0; cnt=0;
		for(ll i=mid+1;i<=r;i++)vec[i].clear();
		solve(mid+1,r);
	}

	void main(){
		memset(val,0xc0,sizeof(val));
		for(ll i=1;i<=n;i++) fa[i]=i;
		E=a[1].e;
		for(ll i=2;i<=n;i++)
			if(a[i].y==a[i-1].y){
				if(a[i-1].x+E>=a[i].x) fa[find(i)]=find(i-1);
			}
		for(ll i=1;i<=n;i++)sb[find(i)]+=a[i].s;
		for(ll i=1;i<=n;i++)dp[i]=sb[find(i)];
		solve(1,n);
		ll ans=0;
		for(ll i=1;i<=n;i++) chkmax(ans,dp[i]);
		printf("%lld\n",ans);
	}
}
void procedure(){
	n=read(),h=read();
	bool f=1;
	for(int i=1;i<=n;i++){
		a[i].x=read(),a[i].y=read(),a[i].s=read(),a[i].e=read();
		a[i].y=h-a[i].y+1;
	}
	sort(a+1,a+n+1,[](Node A,Node B){return A.y!=B.y?A.y<B.y:A.x<B.x;});
	for(int i=2;i<=n;i++)
		f&=(a[i].y!=a[i-1].y);

	if(f)
		sol1::main();
	else{
		sol2::main();
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