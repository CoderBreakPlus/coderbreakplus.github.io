// created time: 2026-10-12 19:53:02
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
#define mid ((l+r)>>1)
int n,q,l[200005],r[200005];
ll ans[200005];
vector<int>e[200005];

int tag[800005],tag2[800005],mn[800005],cnt[800005]; ll val[800005];

void upd(int p,int v){ mn[p]+=v,tag[p]+=v; }
void upd2(int p,int v){ val[p]+=(ll)v*cnt[p],tag2[p]+=v; }

void pushdown(int p){
	if(tag[p]) upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=0;
	if(tag2[p]){
		if(mn[p<<1]==mn[p]) upd2(p<<1,tag2[p]);
		if(mn[p<<1|1]==mn[p]) upd2(p<<1|1,tag2[p]);
		tag2[p]=0;
	}
}
void pushup(int p){
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
	cnt[p]=(mn[p<<1]==mn[p])*cnt[p<<1]+(mn[p<<1|1]==mn[p])*cnt[p<<1|1];
	val[p]=val[p<<1]+val[p<<1|1];
}
void build(int l,int r,int p){
	cnt[p]=r-l+1; if(l==r) return;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
}
void modify(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr)return upd(p,v);
	pushdown(p);
	modify(l,mid,ql,qr,v,p<<1),modify(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
void update(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){
		if(mn[p]==1) upd2(p,1);
		return;
	}
	pushdown(p);
	update(l,mid,ql,qr,p<<1),update(mid+1,r,ql,qr,p<<1|1);
	pushup(p);
}
ll query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return 0;
	if(ql<=l&&r<=qr)return val[p];
	pushdown(p);
	return query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1);
}
vector<int>vec[200005];

void procedure(){
	n=read(),q=read();
	for(int i=1;i<n;i++){
		int u=read(),v=read();
		e[v].pb(u);
	}
	build(1,n,1);
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read();
		vec[r[i]].pb(i);
	}
	for(int i=1;i<=n;i++){
		modify(1,n,1,i,1,1);
		for(int j:e[i]) modify(1,n,1,j,-1,1);
		update(1,n,1,i,1);
		for(int x:vec[i]) ans[x]=query(1,n,l[x],r[x],1);
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",ans[i]);
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