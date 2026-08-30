// created time: 2026-08-30 18:59:15
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
int n,m,q,a[200005],c[200005],mx[800005];
ll qz[200005],val[800005],rval[800005];
set<int>S[200005];

ll getv(int p,int l,int r,int x){
	// cout<<"getv "<<p<<" "<<l<<" "<<r<<" "<<x<<endl;
	if(l==r)
		return qz[l]-qz[max(x,mx[p])];
	if(x>mx[p<<1]){
		// cout<<"goL "<<qz[mid]-qz[x]<<endl;
		return max(qz[mid]-qz[x], getv(p<<1|1,mid+1,r,x));
	}else{
		// cout<<"goR "<<rval[p]<<endl;
		return max(getv(p<<1,l,mid,x), rval[p]);
	}
}
void pushup(int p,int l,int r){
	val[p]=max(val[p<<1], rval[p]=getv(p<<1|1,mid+1,r,mx[p<<1]));
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
	// cout<<p<<": "<<l<<"->"<<r<<" val="<<val[p]<<" mx="<<mx[p]<<" rval="<<rval[p]<<endl;
}
void update(int p,int l,int r,int x,int v){
	if(l==r){
		mx[p]=v;
		return;
	}
	if(x<=mid)update(p<<1,l,mid,x,v);
	else update(p<<1|1,mid+1,r,x,v);
	pushup(p,l,r);
}
pair<int,ll> query(int p,int l,int r,int ql,int qr,int x){
	if(r<ql||qr<l)return {x,-1e18};
	if(ql<=l&&r<=qr){
		// cout<<"query at "<<l<<"->"<<r<<" x="<<x<<" return"<<endl;
		return {max(x,mx[p]),getv(p,l,r,x)};
	}
	auto [x1,v1]=query(p<<1,l,mid,ql,qr,x); x=x1;
	auto [x2,v2]=query(p<<1|1,mid+1,r,ql,qr,x); x=x2;
	return {x,max(v1,v2)};
}
void build(int p,int l,int r){
	if(l==r)return;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	pushup(p,l,r);
}

int find(int p,int l,int r,int v){
	if(l==r) return mx[p]>=v?l:n+1;
	if(mx[p<<1]>=v) return find(p<<1,l,mid,v);
	else return find(p<<1|1,mid+1,r,v);
}
int getmax(int p,int l,int r,int ql,int qr){
	if(r<ql||qr<l)return 0;
	if(ql<=l&&r<=qr)return mx[p];
	return max(getmax(p<<1,l,mid,ql,qr),getmax(p<<1|1,mid+1,r,ql,qr));
}
void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=m;i++) S[i]={0};
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) S[c[i]=read()].emplace(i);
	for(int i=1;i<=n;i++) qz[i]=qz[i-1]+a[i];

	build(1,1,n);
	for(int i=1;i<=m;i++)
		for(auto it=next(S[i].begin());it!=S[i].end();++it)
			if(it!=next(S[i].begin())&&*prev(it)){
				// cout<<"add "<<(*it)<<" "<<*prev(it)<<endl;
				update(1,1,n,*it,*prev(it));
			}

	while(q--){
		int op=read(),l=read(),r=read();
		if(op==1){
			int p=min(r+1,find(1,1,n,l));
			// cout<<"p="<<p<<endl;
			int fr=getmax(1,1,n,1,p-1);
			// cout<<"fr="<<fr<<endl;
			printf("%lld\n",max(qz[p-1]-qz[l-1], query(1,1,n,p,r,fr).se));
		}else{
			if(c[l]==r)continue;
			auto it = S[c[l]].find(l);
			if(it != prev(S[c[l]].end())) update(1,1,n,*next(it),*prev(it));
			S[c[l]].erase(it);

			it = S[c[l]=r].insert(l).fi;
			update(1,1,n,*it,*prev(it));
			if(it != prev(S[c[l]].end())) update(1,1,n,*next(it),*it);
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