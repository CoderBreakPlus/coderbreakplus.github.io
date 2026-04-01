// created time: 2026-04-01 19:00:20
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

int m;
ll a[200005],tmp[200005];
struct BIT{
	ll c[200005];
	void upd(ll x,ll w){
		while(x<=m){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	ll qry(ll x){
		ll ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
	ll findkth(ll k){
		ll l=1,r=m,ans=0;
		while(l<=r){
			ll mid=(l+r)>>1;
			if(qry(mid)>=k) ans=mid,r=mid-1;
			else l=mid+1;
		}
		return ans;
	}
}b1,b2;
void procedure(){
	m=read();
	for(ll i=1;i<=m;i++)a[i]=tmp[i]=read();
	sort(tmp+1,tmp+m+1); int cnt=unique(tmp+1,tmp+m+1)-(tmp+1);
	
	for(ll i=1;i<=m;i++)a[i]=lower_bound(tmp+1,tmp+m+1,a[i])-tmp;

	for(ll i=1;i<=m;i++){
		b1.upd(a[i],1);
		b2.upd(a[i],tmp[a[i]]);

		auto getL = [&](ll mid){
			if(mid==1) return 0ll;
			ll lpos=b1.findkth(mid-1);
			return tmp[lpos]*(mid-2)-b2.qry(lpos-1);
		};
		auto getR = [&](ll mid){
			if(mid==i) return 0ll;
			ll rpos=b1.findkth(mid+1);
			return b2.qry(m)-b2.qry(rpos)-tmp[rpos]*(i-mid-1);
		};
		auto getans = [&](ll mid){
			if(mid<1 || mid>i) return (ll)1e18;
			return max(getL(mid),getR(mid));
		};
		if(i>=3){
			ll l=1,r=i,ans=0;
			while(l<=r){
				ll mid=(l+r)>>1;
				ll pos=b1.findkth(mid);
				if(getL(mid)<getR(mid)){
					ans=mid;
					l=mid+1;
				}else r=mid-1;
			}
			ll val=min(getans(ans),getans(ans+1))%mod*INV(i-2)%mod;
			printf("%lld\n", val);
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