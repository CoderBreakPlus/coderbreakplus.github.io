// created time: 2026-06-16 07:46:29
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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
const int N = 1000000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

int n,q,p[300005];

inline int calc(int n,int k){
	int sb= (binom(2*n+k,n) + mod - binom(2*n+k,n-1)) % mod;
	return sb;
}

struct seg{
	int val[1200005];
	void pushup(int p){
		val[p]=min(val[p<<1],val[p<<1|1]);
	}
	void update(int l,int r,int x,int v,int p){
		if(l==r){
			chkmin(val[p],v);
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) update(l,mid,x,v,p<<1);
		else update(mid+1,r,x,v,p<<1|1);
		pushup(p);
	}
	int query(int l,int r,int ql,int qr,int p){
		if(r<ql||qr<l) return n+1;
		if(ql<=l && r<=qr) return val[p];
		int mid=(l+r)>>1;
		return min(query(l,mid,ql,qr,p<<1),query(mid+1,r,ql,qr,p<<1|1));
	}
	void build(int l,int r,int p,int o){
		if(l==r){
			if(o) val[p]=::p[l];
			else val[p]=n+1;
			return;
		}
		int mid=(l+r)>>1;
		build(l,mid,p<<1,o),build(mid+1,r,p<<1|1,o);
		pushup(p);
	}
}S,T;

struct BIT{
	int c[300005];
	void upd(int x,int w){
		while(x<=n){
			c[x]+=w;
			x+=(x&-x);
		}
	}
	int qry(int x){
		x=min(x,n);
		int ret=0;
		while(x){
			ret+=c[x];
			x-=(x&-x);
		}
		return ret;
	}
}B;

vector<int>vec[300005],qry[300005];
vector<pair<int,int>>upd[300005];


int stk[300005],tp,prv[300005],nxt[300005],l[300005],r[300005];
int mxr[300005],ans[300005],a[300005],b[300005],ca[300005],cb[300005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)p[i]=n-read()+1,mxr[i]=n+1;

	for(int i=1;i<=n;i++){
		while(tp && p[stk[tp]]>p[i]) tp--;
		if(tp) vec[prv[i]=stk[tp]].pb(i);
		stk[++tp] = i;
	}

	tp=0;
	for(int i=1;i<=n;i++){
		while(tp && p[stk[tp]]<p[i]) nxt[stk[tp--]]=i;
		stk[++tp]=i;
	}

	for(int i=1;i<=n;i++) 
		if(prv[i] && nxt[i]) chkmin(mxr[prv[i]], nxt[i]);
	for(int i=n-1;i>=1;i--) chkmin(mxr[i], mxr[i+1]);

	S.build(1,n,1,1),T.build(1,n,1,0);
	q=read();
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read();
		if(r[i] < mxr[l[i]]) qry[l[i]].pb(i);
	}
	for(int i=n;i>=1;i--){
		for(int x: vec[i]) T.update(1,n,x,p[x],1);
		for(int x: qry[i]){
			a[x]=S.query(1,n,l[x],r[x],1),b[x]=T.query(1,n,l[x],r[x],1);
			upd[l[x]-1].pb(x,1), upd[r[x]].pb(x,-1), upd[n].pb(x,1);
			ans[x]=1;
		}
	}
	for(int i=1;i<=n;i++){
		B.upd(p[i],1);
		for(auto [x,y]: upd[i]){
			ca[x] += y * B.qry(a[x]);
			cb[x] += y * B.qry(b[x]);
		}
	}
	for(int i=1;i<=q;i++){
		if(ans[i]){
			cb[i] -= ca[i];
			if(ca[i] + cb[i] == n-(r[i]-l[i]+1))
				ans[i] = calc(ca[i], cb[i]);
			else
				ans[i] = 0;
		}
		printf("%d\n",ans[i]);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}