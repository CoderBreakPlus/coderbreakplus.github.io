// created time: 2026-04-01 15:36:58
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

int n,p,q,r,b[500005],c[500005];
vector<tuple<int,int,int>> s;

int mx[2000005],mn[2000005],tag[2000005]; ll sum[2000005];

void upd(int p,int l,int r,int v){
	mn[p]=mx[p]=tag[p]=v;
	sum[p]=1ll*(r-l+1)*v;
}
void pushup(int p){
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
	sum[p]=sum[p<<1]+sum[p<<1|1];
}
void pushdown(int p,int l,int r){
	int mid=(l+r)>>1;
	if(~tag[p]){
		upd(p<<1,l,mid,tag[p]);
		upd(p<<1|1,mid+1,r,tag[p]);
		tag[p]=-1;
	}
}
void build(int l,int r,int p){
	if(l==r){
		mx[p]=mn[p]=sum[p]=::r;
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
}
void update(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l||mx[p]<v) return;
	if(ql<=l&&r<=qr&&mn[p]>=v){
		upd(p,l,r,v);
		return;
	}
	int mid=(l+r)>>1; pushdown(p,l,r);
	update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}

ll query(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr){
		if(mx[p]<=v) return sum[p];
		if(mn[p]>=v) return 1ll*(r-l+1)*v;
	}
	int mid=(l+r)>>1; pushdown(p,l,r);
	return query(l,mid,ql,qr,v,p<<1)+query(mid+1,r,ql,qr,v,p<<1|1);
}
void procedure(){
	n=read(),p=read(),q=read(),r=read();
	for(int i=1;i<=n;i++){
		int a=read(),b=read(),c=read();
		s.pb(a,b,c);
	}
	memset(tag,-1,sizeof(tag));
	sort(s.begin(),s.end());
	
	for(int i=n-1;i>=0;i--){
		b[i]=max(b[i+1],get<1>(s[i]));
		c[i]=max(c[i+1],get<2>(s[i]));
	}
	build(1,q,1);

	int pt=0;
	ll ans=0;
	for(int i=1;i<=p;i++){
		while(pt<s.size()&&get<0>(s[pt])<i){
			auto [a,b,c] = s[pt++];
			update(1,q,1,b,r-c,1);
		}
		ll val=query(1,q,b[pt]+1,q,r-c[pt],1);
		ans+=val;
	}
	printf("%lld\n",ans);
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