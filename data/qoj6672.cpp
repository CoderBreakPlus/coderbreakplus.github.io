// created time: 2026-05-05 10:05:48
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

int n;
struct Node{
	int l,r,c;
}s[100005];
int tmp[200005],t,dp[2][200005],dv;

struct Seg{
	int val[800005],tag[800005];
	void build(int l,int r,int p){
		val[p]=0,tag[p]=1;
		if(l==r) return;
		int mid=(l+r)>>1;build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	}
	void upd(int p,int w){
		val[p]=(ull)val[p]*w%mod;
		tag[p]=(ull)tag[p]*w%mod;
	}
	void pushup(int p){ addmod(val[p]=val[p<<1]+val[p<<1|1]); }
	void pushdown(int p){
		if(tag[p]>1)upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=1;
	}
	void update(int l,int r,int ql,int qr,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr){upd(p,2);return;}
		int mid=(l+r)>>1;pushdown(p);
		update(l,mid,ql,qr,p<<1),update(mid+1,r,ql,qr,p<<1|1);
		pushup(p);
	}
	void modify(int l,int r,int x,int v,int p){
		if(l==r){ addmod(val[p]+=v);return; }
		int mid=(l+r)>>1;pushdown(p);
		if(x<=mid)modify(l,mid,x,v,p<<1);
		else modify(mid+1,r,x,v,p<<1|1);
		pushup(p);
	}
	int query(int l,int r,int ql,int qr,int p){
		if(r<ql||qr<l)return 0;
		if(ql<=l&&r<=qr)return val[p];
		int mid=(l+r)>>1;pushdown(p);
		addmod(dv=query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1));
		return dv;
	}
}S[2];
void procedure(){
	n=read();
	t=0;
	for(int i=1;i<=n;i++)
		s[i].l=read(),s[i].r=read(),s[i].c=read(),tmp[++t]=s[i].l,tmp[++t]=s[i].r;
	sort(tmp+1,tmp+t+1);
	t=unique(tmp+1,tmp+t+1)-(tmp+1);
	S[0].build(0,t,1),S[1].build(0,t,1);

	memset(dp,0,sizeof(dp));

	for(int i=1;i<=n;i++)
		s[i].l=lower_bound(tmp+1,tmp+t+1,s[i].l)-tmp,
		s[i].r=lower_bound(tmp+1,tmp+t+1,s[i].r)-tmp;

	S[0].modify(0,t,0,1,1);
	sort(s+1,s+n+1,[](const Node& x,const Node& y){ return x.l<y.l; });

	for(int i=1;i<=n;i++){
		int o=s[i].c;
		addmod(dv=S[o^1].query(0,t,0,s[i].l-1,1)+S[o].query(0,t,0,s[i].r-1,1));
		S[o].update(0,t,s[i].r,t,1);
		S[o].modify(0,t,s[i].r,dv,1);
	}
	addmod(dv=S[0].val[1]+S[1].val[1]);
	printf("%d\n",dv);
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