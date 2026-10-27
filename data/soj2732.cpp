// created time: 2026-10-27 07:36:43
#include<bits/extc++.h>
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

int n;
struct Node{
	int x,y,w;
}a[2005];
bool operator< (const Node &A,const Node &B){
	return A.x!=B.x?A.x<B.x:A.y<B.y;
}
const ll V=3e9;
__gnu_pbds::gp_hash_table<ll,int>mp;
pair<ll,ll> imp[2000005];
vector<pair<int,int>>vec[2000005];

int id;
int pos[2005],ord[2000005];

namespace sgt{
	ll ls[8005],rs[8005],sum[8005],mx[8005];
	void pushup(int p){
		ls[p]=max(ls[p<<1],sum[p<<1]+ls[p<<1|1]);
		rs[p]=max(rs[p<<1|1],sum[p<<1|1]+rs[p<<1]);
		sum[p]=sum[p<<1]+sum[p<<1|1];
		mx[p]=max({mx[p<<1],mx[p<<1|1],rs[p<<1]+ls[p<<1|1]});
	}
	void update(int l,int r,int x,int w,int p){
		if(l==r){ ls[p]=rs[p]=sum[p]=mx[p]=w; return; }
		int mid=(l+r)>>1;
		if(x<=mid)update(l,mid,x,w,p<<1);
		if(x>mid) update(mid+1,r,x,w,p<<1|1);
		pushup(p);
	}
	void build(int l,int r,int p){
		if(l==r){ ls[p]=rs[p]=sum[p]=mx[p]=a[l].w; return; }
		int mid=(l+r)>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		pushup(p);
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i].x=read(),a[i].y=read(),a[i].w=read();
	sort(a+1,a+n+1);
	
	for(int i=1;i<=n;i++)pos[i]=i;
	ll ans=0;
	for(int i=1;i<=n;i++){
		for(int j=i+1;j<=n;j++){
			if(a[i].x==a[j].x) continue;
			ll A=a[j].y-a[i].y,B=a[j].x-a[i].x;
			ll D=__gcd(max(A,-A),B); A/=D,B/=D;
			ll hsh=(A+V)*V+B;
			if(!mp[hsh]) imp[mp[hsh]=++id]={A,B};
			vec[mp[hsh]].pb(i,j);
		}
	}


	sgt::build(1,n,1);
	chkmax(ans,sgt::mx[1]);
	for(int i=1;i<=id;i++) ord[i]=i;
	sort(ord+1,ord+id+1,[&](int x,int y){
		return imp[x].fi*imp[y].se<imp[y].fi*imp[x].se;
	});
	
	for(int o=1;o<=id;o++){
		int i=ord[o];
		for(auto [x,y]:vec[i]){
			if(pos[x]<pos[y]){
				swap(pos[x],pos[y]);
				sgt::update(1,n,pos[x],a[x].w,1);
				sgt::update(1,n,pos[y],a[y].w,1);
			}
		}
		chkmax(ans,sgt::mx[1]);
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