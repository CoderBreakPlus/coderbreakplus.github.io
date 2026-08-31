// created time: 2026-08-31 13:49:52
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
const int M=2e5;
#define mid ((l+r)>>1)
int n,a[100005],b[100005],c[100005],d[100005];

struct DS{
	set<pair<int,int>>sa,sb,sc,sd;
	struct bit{
		int c[M+5];
		void upd(int x,int w){ while(x<=M) c[x]+=w,x+=(x&-x); }
		int qry(int x){ int ret=0; while(x) ret+=c[x],x-=(x&-x); return ret; }
	}bX,bY;
	struct sgt{
		int tag[M<<2];
		pair<int,int> t[M<<2];
		void upd(int p,int w){ t[p].fi+=w, tag[p]+=w; }
		void pushdown(int p){
			if(tag[p])
				upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=0;
		}
		void pushup(int p){
			t[p]=min(t[p<<1],t[p<<1|1]);
		}
		pair<int,int> query(int p,int l,int r,int ql,int qr){
			if(r<ql||qr<l) return {1e9,0};
			if(ql<=l&&r<=qr) return t[p];
			pushdown(p);
			return min(query(p<<1,l,mid,ql,qr),query(p<<1|1,mid+1,r,ql,qr));
		}
		void update(int p,int l,int r,int ql,int qr,int v){
			if(r<ql||qr<l) return;
			if(ql<=l&&r<=qr){ upd(p,v); return; }
			pushdown(p);
			update(p<<1,l,mid,ql,qr,v),update(p<<1|1,mid+1,r,ql,qr,v);
			pushup(p);
		}
		void build(int p,int l,int r){
			if(l==r){ t[p]={0,l}; return; }
			build(p<<1,l,mid),build(p<<1|1,mid+1,r);
			pushup(p);
		}
	}X,Y;
	void init(){ X.build(1,1,M);Y.build(1,1,M); }
	void ins(int i){
		X.update(1,1,M,a[i]+1,c[i]-1,1),bX.upd(c[i],1);
		Y.update(1,1,M,b[i]+1,d[i]-1,1),bY.upd(d[i],1);
		sa.emplace(a[i],i),sb.emplace(b[i],i);
		sc.emplace(c[i],i),sd.emplace(d[i],i);
	}
	void del(int i){
		X.update(1,1,M,a[i]+1,c[i]-1,-1),bX.upd(c[i],-1);
		Y.update(1,1,M,b[i]+1,d[i]-1,-1),bY.upd(d[i],-1);
		sa.erase({a[i],i}),sb.erase({b[i],i});
		sc.erase({c[i],i}),sd.erase({d[i],i});
	}
	void clear(){
		while(!sa.empty()) del(sa.begin()->se);
	}
}s[20];
struct lsh{
	int tmp[200005],cnt;
	void ins(int x){ tmp[++cnt]=x; }
	void init(){ sort(tmp+1,tmp+cnt+1); cnt=unique(tmp+1,tmp+cnt+1)-(tmp+1); }
	int find(int x){
		return lower_bound(tmp+1,tmp+cnt+1,x)-tmp;
	}
}X,Y;

bool solve(int dep){
	int sz=s[dep].sa.size();
	if(sz==1) return 1;
	assert(sz>1);

	int L=s[dep].sa.begin()->fi,R=s[dep].sc.rbegin()->fi;
	int U=s[dep].sb.begin()->fi,D=s[dep].sd.rbegin()->fi;
	auto [mn,cut]=s[dep].X.query(1,1,M,L+1,R-1);
	s[dep+1].clear();

	if(mn==0){
		if(s[dep].bX.qry(cut)*2>=sz){
			while(s[dep].sc.rbegin()->fi>cut){
				int x=s[dep].sc.rbegin()->se;
				s[dep].del(x),s[dep+1].ins(x);
			}
		}else{
			while(s[dep].sa.begin()->fi<cut){
				int x=s[dep].sa.begin()->se;
				s[dep].del(x),s[dep+1].ins(x);
			}
		}
		if(!solve(dep+1)) return 0;
		return solve(dep);
	}else{
		auto [mn,cut]=s[dep].Y.query(1,1,M,U+1,D-1);
		if(mn==0){
			if(s[dep].bY.qry(cut)*2>=sz){
				while(s[dep].sd.rbegin()->fi>cut){
					int x=s[dep].sd.rbegin()->se;
					s[dep].del(x),s[dep+1].ins(x);
				}
			}else{
				while(s[dep].sb.begin()->fi<cut){
					int x=s[dep].sb.begin()->se;
					s[dep].del(x),s[dep+1].ins(x);
				}
			}
			if(!solve(dep+1)) return 0;
			return solve(dep);
		}else return 0;
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		a[i]=read(),b[i]=read(),c[i]=read(),d[i]=read();
		X.ins(a[i]),X.ins(c[i]); Y.ins(b[i]),Y.ins(d[i]);
	}

	X.init(),Y.init();
	for(int i=1;i<=n;i++)
		a[i]=X.find(a[i]),b[i]=Y.find(b[i]),
		c[i]=X.find(c[i]),d[i]=Y.find(d[i]);

	for(int i=0;i<20;i++)s[i].init();
	for(int i=1;i<=n;i++)s[0].ins(i);

	puts(solve(0)?"YES":"NO");
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