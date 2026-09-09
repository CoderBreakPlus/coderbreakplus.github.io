// created time: 2026-09-09 19:32:10
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
const int M = 1e6;
#define mid ((l+r)>>1)
int n,a[200005];

int mn[4000005],tag[4000005],id[4000005];
void upd(int p,int w){
	mn[p]+=w, tag[p]+=w;
}
void pushup(int p){
	mn[p]=min(mn[p<<1],mn[p<<1|1]);
	id[p]=id[p<<1|(mn[p]!=mn[p<<1])];
}
void pushdown(int p){
	if(tag[p])
		upd(p<<1,tag[p]),upd(p<<1|1,tag[p]);
	tag[p]=0;
}
void update(int p,int l,int r,int ql,int qr,int v){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){ upd(p,v); return; }
	pushdown(p);
	update(p<<1,l,mid,ql,qr,v),update(p<<1|1,mid+1,r,ql,qr,v);
	pushup(p);
}
int query(int p,int l,int r,int x){
	if(l==r) return mn[p];
	pushdown(p);
	if(x<=mid) return query(p<<1,l,mid,x);
	else return query(p<<1|1,mid+1,r,x);
}
int find(int p,int l,int r,int ql,int qr,int v){
	if(r<ql||qr<l) return -1;
	if(l==r) return mn[p]<=v?l:-1;
	pushdown(p);
	if(ql<=l && r<=qr){
		if(mn[p<<1]<=v) return find(p<<1,l,mid,ql,qr,v);
		else if(mn[p<<1|1]<=v) return find(p<<1|1,mid+1,r,ql,qr,v);
		else return -1;
	}
	int ret=find(p<<1,l,mid,ql,qr,v);
	if(!~ret) ret=find(p<<1|1,mid+1,r,ql,qr,v);
	return ret;
}
void build(int p,int l,int r){
	if(l==r){
		mn[p]=-l,id[p]=l;
		return;
	}
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	pushup(p);
}
set<pair<int,int>>S;

void procedure(){
	n=read();
	build(1,0,M);
	for(int i=1;i<=n;i++){
		int x=read();
		vector<pair<int,int>>D,I;
		auto ins = [&](int l,int r){ if(l>r)return; I.pb(l,r),S.emplace(l,r); };
		auto del = [&](int l,int r){ if(l>r)return; D.pb(l,r),S.erase({l,r}); };
		if(!a[x]){
			int l=x,r=x,flg=0;
			auto pos=S.lower_bound({x+1,0});
			if(pos!=S.begin()&&(--pos)->se>=x) l=pos->fi,r=pos->se,del(l,r),flg=1;

			{
				auto it=S.lower_bound({r+1,0});
				if(it!=S.end()&&it->fi==r+1) r=it->se,del(it->fi,it->se);
			}
			{
				auto it=S.lower_bound({l,0});
				if(it!=S.begin()&&(--it)->se==l-1) l=it->fi,del(it->fi,it->se);
			}
			++r;

			{
				auto it=S.lower_bound({r+1,0});
				if(it!=S.end()&&it->fi==r+1) r=it->se,del(it->fi,it->se);
			}
			if(flg){
				++r;
				{
					auto it=S.lower_bound({r+1,0});
					if(it!=S.end()&&it->fi==r+1) r=it->se,del(it->fi,it->se);
				}	
			}
			ins(l,r);
			a[x]=1; update(1,0,M,x,M,2);
		}else{
			a[x]=0; update(1,0,M,x,M,-2);
			auto [l,r]=*prev(S.lower_bound({x+1,0}));
			del(l,r);
			int qz=query(1,0,M,l-1);
			int pos1=find(1,0,M,l,r,qz-1);
			int pos2=find(1,0,M,l,r,qz-2);
			ins(l,pos1-1),ins(pos1+1,pos2-1),ins(pos2+1,r);
		}

		printf("%d\n",(int)D.size());
		for(auto [l,r]: D) printf("%d %d\n",l,r);
		printf("%d\n",(int)I.size());
		for(auto [l,r]: I) printf("%d %d\n",l,r);
		puts("");
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