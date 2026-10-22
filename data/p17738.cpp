// created time: 2026-10-22 20:25:51
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

int n,q,a[200005],m;

struct zkw{
	int t[800005];
	int get(int x,int y){
		if(!x||!y)return x^y;
		return a[x]<a[y]?x:y;
	}
	void pushup(int p){ t[p]=get(t[p<<1],t[p<<1|1]); }
	void upd(int x,int v){
		for(t[x+=m]=v;x>1;) pushup(x>>=1);
	}
	int qry(int l,int r){
		int ret=0;
		for(l+=m-1,r+=m+1;l+1<r;l>>=1,r>>=1){
			if(~l&1) ret=get(ret,t[l^1]);
			if( r&1) ret=get(ret,t[r^1]);
		}
		return ret;
	}
}v0[18];
struct zkw2{
	ll t[800005];
	ll get(ll x,ll y){ return x+y; }
	void pushup(ll p){ t[p]=get(t[p<<1],t[p<<1|1]); }
	void upd(ll x,ll v){
		for(t[x+=m]=v;x>1;) pushup(x>>=1);
	}
	ll qry(ll l,ll r){
		ll ret=0;
		for(l+=m-1,r+=m+1;l+1<r;l>>=1,r>>=1){
			if(~l&1) ret=get(ret,t[l^1]);
			if( r&1) ret=get(ret,t[r^1]);
		}
		return ret;
	}
}v1[18];
void ins(int i){
	v0[lg2(a[i])].upd(i,i);
	v1[lg2(a[i])].upd(i,a[i]);
}
void del(int i){
	v0[lg2(a[i])].upd(i,0);
	v1[lg2(a[i])].upd(i,0);
}
void procedure(){
	n=read(),q=read();
	m=1;
	while(m<=n+1)m<<=1;
	for(int i=1;i<=n;i++) a[i]=read(),ins(i);
	while(q--){
		int op=read();
		if(op==1){
			int x=read(),y=read();
			del(x);a[x]=y;ins(x);
		}else{
			int l=read(),r=read();
			ll sum=0,ans=-1;
			for(int i=0;i<=17;i++){
				int mn=v0[i].qry(l,r);
				if(mn){
					if(a[mn]>sum+1){
						ans=sum+1;
						break;
					}
					v0[i].upd(mn,0);
					int mn2=v0[i].qry(l,r);
					v0[i].upd(mn,mn);
					if(a[mn2]>sum+a[mn]+1){
						ans=sum+a[mn]+1;
						break;
					}
				}
				sum+=v1[i].qry(l,r);
			}

			if(!~ans) ans=sum+1;
			printf("%lld\n",ans);
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