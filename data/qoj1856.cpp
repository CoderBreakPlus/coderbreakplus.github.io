// created time: 2026-08-11 19:14:11
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

int n,m,l[200005],r[200005],L[200005],R[200005],ans[200005];
set<tuple<int,int,int>>S;

int len[800005],t0[800005],t1[800005],tag0[800005],tag1[800005],tag2[800005];
void apply(int x,int s0,int s1,int s2){
	t1[x]=(t1[x]+(ull)s1*t0[x]+(ull)s2*len[x])%mod;
	t0[x]=(t0[x]+(ull)s0*len[x])%mod;

	tag2[x]=(tag2[x]+(ull)tag0[x]*s1+s2)%mod;
	addmod(tag1[x]+=s1);
	addmod(tag0[x]+=s0);
}
void pushdown(int p){
	apply(p<<1,tag0[p],tag1[p],tag2[p]);
	apply(p<<1|1,tag0[p],tag1[p],tag2[p]);
	tag0[p]=tag1[p]=tag2[p]=0;
}
void pushup(int p){
	addmod(t0[p]=t0[p<<1]+t0[p<<1|1]);
	addmod(t1[p]=t1[p<<1]+t1[p<<1|1]);
}
void update(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){
		apply(p,v,0,0);
		return;
	}
	int mid=(l+r)>>1; pushdown(p);
	update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
int query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr) return t1[p];
	int mid=(l+r)>>1,ret; pushdown(p);
	addmod(ret=query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1));
	return ret;
}
void build(int l,int r,int p){
	len[p]=r-l+1;
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
}

vector<int>qq[200005];

void procedure(){
	n=read(),m=read();	
	for(int i=1;i<=n;i++)l[i]=read(),r[i]=read();
	S.emplace(0,1e8,0);
	for(int i=1;i<=m;i++)L[i]=read(),R[i]=read(),qq[R[i]].pb(i);

	auto cut = [&](int x){
		auto it = prev(S.lower_bound({x+1,0,0}));
		auto [l,r,c] = *it;
		if(l==x) return;
		S.erase(it);
		S.emplace(l,x,c),S.emplace(x,r,c);
	};
	build(1,n,1);
	for(int i=1;i<=n;i++){
		cut(l[i]),cut(r[i]);
		auto it=S.lower_bound({l[i],0,0});
		while(it!=S.end()&&get<0>(*it)<r[i]){
			update(1,n,1,get<2>(*it),(get<0>(*it)-get<1>(*it)+mod)%mod,1);
			S.erase(it);
			it=S.lower_bound({l[i],0,0});
		}
		S.emplace(l[i],r[i],i);
		update(1,n,1,i,r[i]-l[i],1);
		apply(1,0,1,0);
		for(int id:qq[i]) ans[id]=query(1,n,L[id],R[id],1);
	}
	for(int i=1;i<=m;i++){
		ans[i]=(ull)ans[i]*INV((ll)(R[i]-L[i]+1)*(R[i]-L[i]+2)/2%mod)%mod;
		printf("%d\n",ans[i]);
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