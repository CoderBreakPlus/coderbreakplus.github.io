// created time: 2026-04-23 19:39:57
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
int h,w,n; ll X;

int u[200005],d[200005],l[200005],r[200005],c[200005];
int ans[4][200005];
struct lsh{
	int seq[400005],n;
	void add(int x){seq[++n]=x;}
	void init(){ sort(seq+1,seq+n+1);n=unique(seq+1,seq+n+1)-(seq+1); }
	int qry(int x){ return lower_bound(seq+1,seq+n+1,x)-seq; }	
}cx,cy;

struct Seg{
	ll val[1600005],tag[1600005];
	void pushup(int p){
		val[p]=max(val[p<<1],val[p<<1|1]);
	}
	void upd(int p,ll v){
		tag[p]+=v, val[p]+=v;
	}
	void pushdown(int p){
		if(tag[p]){
			upd(p<<1, tag[p]);
			upd(p<<1|1, tag[p]);
			tag[p]=0;
		}
	}
	void build(int l,int r,int p){
		val[p]=tag[p]=0;if(l==r)return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	}
	void update(int l,int r,int ql,int qr,ll v,int p){
		if(r<ql || qr<l)return;
		if(ql<=l && r<=qr){
			upd(p, v);
			return;
		}
		int mid=(l+r)>>1;pushdown(p);
		update(l,mid,ql,qr,v,p<<1), update(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
}S;
vector<int>vec[400005];
int vis[400005];

void procedure(){
	h=read(),w=read(),n=read(),X=read();
	for(int i=1;i<=n;i++){
		u[i]=read(),d[i]=read(),l[i]=read(),r[i]=read(),c[i]=read();
		cx.add(u[i]),cx.add(d[i]+1);
		cy.add(l[i]),cy.add(r[i]+1);
	}
	cx.init(),cy.init();
	for(int i=1;i<=n;i++){
		u[i]=cx.qry(u[i]),d[i]=cx.qry(d[i]+1)-1;
		l[i]=cy.qry(l[i]),r[i]=cy.qry(r[i]+1)-1;
		// cout<<"add "<<u[i]<<" "<<d[i]<<" "<<l[i]<<" "<<r[i]<<endl;
	}
	int m=max(cx.n,cy.n);

	memset(ans[0], 0x3f, sizeof(ans[0]));
	memset(ans[2], 0x3f, sizeof(ans[2]));

	int pt;

	auto init = [&](){
		S.build(1,m,1);
		for(int i=1;i<=m;i++)vec[i].clear();
		for(int i=1;i<=n+1;i++)vis[i]=0;
		pt=n+1;
	};
	auto upd = [&](int i,int o){
		auto mdf = [&](int x,int cf){
			if(o<=1) S.update(1,m,l[x],r[x],c[x]*cf,1);
			else S.update(1,m,u[x],d[x],c[x]*cf,1);
		};
		for(auto x: vec[i]){
			if(x>0) {
				if(x<=pt) mdf(x,1);
				vis[x]=1;
			}else{ x=-x;
				if(x<=pt) mdf(x,-1);
				vis[x]=0;				
			}
		}
		while(pt>=1){
			if(vis[pt]) mdf(pt,-1);
			if(S.val[1]<X){
				if(vis[pt]) mdf(pt,1);
				break;
			}
			--pt;
			ans[o][pt]=i;
		}
		// cout<<"at line "<<i<<" find pt = "<<pt<<endl;
	};

	for(int o:{0}){
		#ifdef LOCAL
			cout<<"o="<<o<<endl;
		#endif
		init();
		for(int i=1;i<=n;i++) vec[u[i]].pb(i), vec[d[i]+1].pb(-i);
		for(int i=1;i<=cx.n;i++) upd(i,o);
		ans[o][0]=cx.n;
		for(int i=1;i<=n;i++) ans[o][i]=min(ans[o][i],ans[o][i-1]);
		for(int i=1;i<=n;i++) ans[o][i]=cx.seq[ans[o][i]];
	}
	for(int o:{1}){
		#ifdef LOCAL
			cout<<"o="<<o<<endl;
		#endif
		init();
		for(int i=1;i<=n;i++) vec[d[i]].pb(i),vec[u[i]-1].pb(-i);
		for(int i=cx.n;i>=1;i--) upd(i,o);
		for(int i=1;i<=n;i++) ans[o][i]=max(ans[o][i],ans[o][i-1]);
		for(int i=1;i<=n;i++) ans[o][i]=cx.seq[ans[o][i]+1];
	}
	for(int o:{2}){
		#ifdef LOCAL
			cout<<"o="<<o<<endl;
		#endif
		init();
		for(int i=1;i<=n;i++) vec[l[i]].pb(i), vec[r[i]+1].pb(-i);
		for(int i=1;i<=cy.n;i++) upd(i,o);
		ans[o][0]=cy.n;
		for(int i=1;i<=n;i++) ans[o][i]=min(ans[o][i],ans[o][i-1]);
		for(int i=1;i<=n;i++) ans[o][i]=cy.seq[ans[o][i]];
	}
	for(int o:{3}){
		#ifdef LOCAL
			cout<<"o="<<o<<endl;
		#endif
		init();
		for(int i=1;i<=n;i++) vec[r[i]].pb(i),vec[l[i]-1].pb(-i);
		for(int i=cy.n;i>=1;i--) upd(i,o);
		// for(int i=1;i<=n;i++) cout<<ans[o][i]<<" ";cout<<endl;

		for(int i=1;i<=n;i++) ans[o][i]=max(ans[o][i],ans[o][i-1]);
		for(int i=1;i<=n;i++) ans[o][i]=cy.seq[ans[o][i]+1];
	}
	for(int i=1;i<=n;i++){
		// printf("%lld %lld %lld %lld\n",ans[0][i],ans[1][i]-1,ans[2][i],ans[3][i]-1);
		if(ans[0][i]>=ans[1][i] || ans[2][i]>=ans[3][i]){
			assert(ans[0][i]>=ans[1][i] && ans[2][i]>=ans[3][i]);
			puts("0");
		}else{
			printf("%lld\n",(ll)(ans[1][i]-ans[0][i])*(ans[3][i]-ans[2][i]));
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