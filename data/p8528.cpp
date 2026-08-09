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

int n,m,a[200005],f[200005],l[200005],r[200005];
ll ans[200005];
vector<int>E[200005];
vector<tuple<int,int,int>>vec[200005];
vector<int>qry[200005];

void upd(int l,int r,int s,int t){
	// cout<<"upd "<<l<<" "<<r<<" "<<s<<" "<<t<<endl;
	vec[s].pb(l,r,1);
	vec[t+1].pb(l,r,-1);
}
set<int>S[200005];
void dfs(int x){
	auto fjy = [&](int l,int r){
		// cout<<"at "<<x<<" merge "<<l<<" "<<r<<endl;
		if(l<a[x]&&a[x]<r) return;
		if(r<a[x]) upd(1,l,r,a[x]-1);
		else upd(a[x]+1,l,r,n); 
	};
	for(int y:E[x]){
		dfs(y);
		if(S[y].size()>S[x].size())swap(S[x],S[y]);
		for(int w: S[y]){
			auto it=S[x].lower_bound(w);
			if(it!=S[x].end()) fjy(w,*it);
			if(it!=S[x].begin()) fjy(*prev(it),w);
		}
		for(int w: S[y]) S[x].emplace(w); S[y].clear();
	}
	S[x].emplace(a[x]);
}

int mn[800005],cnt[800005],tag[800005],tag2[800005]; ll sum[800005];
void upd1(int p,int v){ tag[p]+=v,mn[p]+=v; }
void upd2(int p,int v){ tag2[p]+=v,sum[p]+=(ll)cnt[p]*v; }

void pushdown(int p){
	if(tag[p]){
		upd1(p<<1, tag[p]);
		upd1(p<<1|1, tag[p]);
		tag[p]=0;
	}
	if(tag2[p]){
		if(mn[p]==mn[p<<1]) upd2(p<<1, tag2[p]);
		if(mn[p]==mn[p<<1|1]) upd2(p<<1|1, tag2[p]);
		tag2[p]=0;
	}
}
void pushup(int p){
	sum[p]=sum[p<<1]+sum[p<<1|1];
	if(mn[p<<1]<mn[p<<1|1]){
		mn[p]=mn[p<<1];
		cnt[p]=cnt[p<<1];
	}else if(mn[p<<1]>mn[p<<1|1]){
		mn[p]=mn[p<<1|1];
		cnt[p]=cnt[p<<1|1];
	}else if(mn[p<<1]==mn[p<<1|1]){
		mn[p]=mn[p<<1];
		cnt[p]=cnt[p<<1]+cnt[p<<1|1];
	}
}
void build(int l,int r,int p){
	if(l==r){ cnt[p]=1; return; }
	int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	pushup(p);
}
void update(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l) return;
	if(ql<=l && r<=qr){
		// cout<<"upd on "<<l<<"->"<<r<<endl;
		upd1(p,v);
		return;
	}
	int mid=(l+r)>>1; pushdown(p);
	update(l,mid,ql,qr,v,p<<1);
	update(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
	// cout<<l<<"->"<<r<<" here "<<mn[p]<<" "<<cnt[p]<<endl;
}
void counts(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l||0<mn[p]) return;
	if(ql<=l && r<=qr){
		// cout<<"counts "<<l<<"->"<<r<<" with "<<v<<endl;
		upd2(p,v);
		return;
	}
	int mid=(l+r)>>1; pushdown(p);
	counts(l,mid,ql,qr,v,p<<1);
	counts(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
	// cout<<l<<"->"<<r<<" here sum = "<<sum[p]<<endl;
}
ll query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return 0;
	if(ql<=l&&r<=qr) return sum[p];
	int mid=(l+r)>>1; pushdown(p);
	return query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1);
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=2;i<=n;i++)
		f[i]=read(),E[f[i]].pb(i);
	
	dfs(1);
	for(int i=1;i<=m;i++){
		l[i]=read(),r[i]=read();
		qry[r[i]].pb(i);
	}
	build(1,n,1);
	for(int i=1;i<=n;i++){
		// cout<<"i="<<i<<endl;
		for(auto [l,r,v]: vec[i]) update(1,n,l,r,v,1);
		counts(1,n,1,i,1,1);
		for(int x: qry[i]) ans[x]=query(1,n,l[x],r[x],1);
	}
	
	for(int i=1;i<=m;i++)
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