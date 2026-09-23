// created time: 2026-09-23 11:24:31
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

int n,v,a[200005],b[200005];
int st[20][200005];
int get(int x,int y){ return a[x]>a[y]?x:y; }
int query(int l,int r){
	int p=lg2(r-l+1);
	return get(st[p][l],st[p][r-(1<<p)+1]);
}
struct zkw1{
	int t[800005],m;
	void pushup(int p){ t[p]=(t[p<<1]|t[p<<1|1]); }
	void init(){
		m=1;
		while(m<=n+1)m<<=1;
		for(int i=1;i<=2*m;i++)t[i]=0;

		for(int i=1;i<=n;i++) t[m+i]=b[i];
		for(int i=m-1;i>=1;i-) pushup(i);
	}
	void upd(int x,int w){
		t[x+=m]=w;
		for(x>>=1;x;x>>=1)pushup(x);
	}
	int qry(int l,int r){
		int ret=0; if(l>r) return ret;
		for(l+=m-1,r+=m+1;l^r^1;l>>=1,r>>=1){
			if(~l&1) ret|=t[l^1];
			if( r&1) ret|=t[r^1];
		}
		return ret;
	}
}T1;
struct zkw2{
	int t[800005],m;
	void pushup(int p){ t[p]=min(t[p<<1],t[p<<1|1]); }
	void init(){
		m=1;
		while(m<=n+1)m<<=1;
		for(int i=1;i<=2*m;i++)t[i]=0x3f3f3f3f;
	}
	void upd(int x,int w){
		t[x+=m]=w;
		for(x>>=1;x;x>>=1)pushup(x);
	}
	int qry(int l,int r){
		int ret=0x3f3f3f3f; if(l>r)return ret;
		for(l+=m-1,r+=m+1;l^r^1;l>>=1,r>>=1){
			if(~l&1) chkmin(ret,t[l^1]);
			if( r&1) chkmin(ret,t[r^1]);
		}
		return ret;
	}
}T2;
int lc[200005],rc[200005],ls[200005],rs[200005],fa[200005],jp[20][200005];
set<pair<int,int>>S;

bool check(int p){ return p && T1.qry(ls[p],rs[p])>=v; }
bool judge(int p){ return check(p)&&!check(lc[p])&&!check(rc[p]); }
void ins(int p){
	S.emplace(ls[p],rs[p]),T2.upd(ls[p],a[p]);
}
void del(int l,int r){ S.erase({l,r}),T2.upd(l,0x3f3f3f3f); }

int build(int l,int r){
	if(l>r)return 0;
	int p=query(l,r); ls[p]=l,rs[p]=r;
	lc[p]=build(l,p-1),rc[p]=build(p+1,r);
	fa[lc[p]]=fa[rc[p]]=p;
	if(judge(p)) ins(p);
	return p;
}

void procedure(){
	n=read(),v=read();
	for(int i=1;i<=n;i++)a[i]=read();
	for(int i=1;i<=n;i++)b[i]=read();

	T1.init(),T2.init();

	for(int i=1;i<=n;i++) st[0][i]=i;
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			st[i][j]=get(st[i-1][j],st[i-1][j+(1<<i-1)]);

	S={{n+1,n+1}};
	build(1,n);

	for(int i=1;i<=n;i++) jp[0][i]=fa[i];
	for(int i=1;i<=19;i++)
		for(int j=1;j<=n;j++) jp[i][j]=jp[i-1][jp[i-1][j]];

	int q=read();

	while(q--){
		int op=read();
		if(op==1){
			int i=read(),x=read();
			auto it=S.lower_bound({i+1,0});
			if(it!=S.begin()){
				auto [l,r]=*prev(it);
				if(l<=i&&i<=r) del(l,r);
			}

			T1.upd(i,x);
			int w=i;
			if(!check(w)){
				for(int o=19;o>=0;o--)
					if(jp[o][w] && !check(jp[o][w])) w=jp[o][w];
				w=fa[w];
			}
			if(judge(w)){
				ins(w);
			}
		}else{
			int l=read(),r=read(),br=r;
			auto it=S.lower_bound({r+1,0});
			if(it!=S.begin() && prev(it)->se>r) br=prev(it)->fi-1;

			int ans=T2.qry(l,br);
			{
				int L=l,R=r+1;
				while(L<R){
					int Mid=(L+R)>>1;
					if(T1.qry(l,Mid)>=v) R=Mid;
					else L=Mid+1;
				}
				if(R<=r) chkmin(ans,a[query(l,R)]);
			}
			{
				int L=l-1,R=r;
				while(L<R){
					int Mid=(L+R+1)>>1;
					if(T1.qry(Mid,r)>=v) L=Mid;
					else R=Mid-1;
				}
				if(L>=l) chkmin(ans,a[query(L,r)]);
			}
			if(ans>1e9) printf("-1 ");
			else printf("%d ",ans);
		}
	}
	puts("");
	for(int i=1;i<=n;i++) lc[i]=rc[i]=ls[i]=rs[i]=fa[i]=0;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}