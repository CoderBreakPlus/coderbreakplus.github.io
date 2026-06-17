// created time: 2026-06-17 09:28:13
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

int n,m,d,N,ib[400005],b[400005],a[400005];

ll va[1600005],vb[1600005],vc[1600005],tag[1600005],sz[1600005];
void pushup(int p){
	sz[p]=sz[p<<1]+sz[p<<1|1];
	if(!sz[p<<1] && !sz[p<<1|1]) return;
	if(!sz[p<<1|1]) {
		va[p]=va[p<<1],vb[p]=vb[p<<1],vc[p]=vc[p<<1];
	}else if(!sz[p<<1]){
		va[p]=va[p<<1|1],vb[p]=vb[p<<1|1],vc[p]=vc[p<<1|1];
	}else{
		va[p]=min(va[p<<1],va[p<<1|1]);
		vb[p]=max(vb[p<<1],vb[p<<1|1]);
		vc[p]=max({vc[p<<1],vc[p<<1|1],vb[p<<1|1]-va[p<<1]});
	}
}
void upd(int p,ll v){
	va[p]+=v,vb[p]+=v,tag[p]+=v;
}
void pushdown(int p){
	if(tag[p])
		upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=0;
}
void update(int l,int r,int x,ll v,int p){
	if(l==r){
		va[p]+=v, vb[p]+=v, vc[p]=0, sz[p]=1;
		return;
	}
	int mid=(l+r)>>1; pushdown(p);
	if(x<=mid)update(l,mid,x,v,p<<1);
	else update(mid+1,r,x,v,p<<1|1);
	pushup(p);
}

void modify(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return;
	if(ql<=l && r<=qr){
		upd(p, d);
		return;
	}
	int mid=(l+r)>>1; pushdown(p);
	modify(l,mid,ql,qr,p<<1),modify(mid+1,r,ql,qr,p<<1|1);
	pushup(p);
}
void procedure(){
	n=read(),m=read(),d=read();
	N=n+m;
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=n+1;i<=N;i++) a[i]=read();

	for(int i=1;i<=N;i++)ib[i]=i;
	sort(ib+1,ib+N+1,[](int x,int y){ return a[x]<a[y]; });

	for(int i=1;i<=N;i++) b[ib[i]]=i;
	
	for(int i=1;i<=N;i++){
		modify(1,N,b[i],N,1);
		update(1,N,b[i],(ll)-a[i],1);
		if(i>n){
			// printf("%lld\n",vc[1]);
			if(vc[1]&1)printf("%lld.5 ", vc[1]/2);
			else printf("%lld ", vc[1]/2);
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