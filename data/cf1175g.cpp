// created time: 2026-08-25 15:15:34
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
const int M = 2e4;
int n,k,a[20005];
ll f[20005],g[20005];

struct Line{
	ll k,b;
	ll val(ll x){ return k*x+b; }
}s[40005]; int id,cnt;
int t[10000005],lc[10000005],rc[10000005];
int newline(ll k,ll b){
	s[++id]=(Line){k,b};
	return id;
}
void update(int l,int r,int x,int &p){
	if(l>r) return;
	if(!p){ t[p=++cnt]=x; return; }
	int mid=(l+r)>>1;
	if(s[x].val(mid)<s[t[p]].val(mid))swap(t[p],x);

	if(s[x].k>s[t[p]].k) update(l,mid-1,x,lc[p]);
	if(s[x].k<s[t[p]].k) update(mid+1,r,x,rc[p]);
}
void lovef(int l,int r,int x,int bef,int &p){
	if(l>r) return;
	if(!bef){ t[p=++cnt]=x; return; }
	t[p=++cnt]=t[bef], lc[p]=lc[bef], rc[p]=rc[bef];

	int mid=(l+r)>>1;
	if(s[x].val(mid)<s[t[p]].val(mid))swap(t[p],x);

	if(s[x].k>s[t[p]].k) lovef(l,mid-1,x,lc[bef],lc[p]);
	if(s[x].k<s[t[p]].k) lovef(mid+1,r,x,rc[bef],rc[p]);
}
int merge(int x,int y,int l,int r){
	if(!x||!y)return x+y;

	int mid=(l+r)>>1;
	if(s[t[y]].val(mid)<s[t[x]].val(mid)) swap(t[x],t[y]);
	lc[x]=merge(lc[x],lc[y],l,mid-1);
	rc[x]=merge(rc[x],rc[y],mid+1,r);

	update(l,r,t[y],x);
	return x;
}
ll query(int l,int r,int x,int p){
	if(!p) return 1e18;
	int mid=(l+r)>>1;
	if(x==mid) return s[t[p]].val(x);
	return min(s[t[p]].val(x),
		(x<mid)?query(l,mid-1,x,lc[p]):query(mid+1,r,x,rc[p]));
}
int stk[20005],rt[20005],info[20005],tp;
void procedure(){
	n=read(),k=read();
	for(int i=1;i<=n;i++)a[i]=read();
	memset(f,0x3f,sizeof(f));
	f[0]=0;

	for(int w=1;w<=k;w++){
		memset(g,0x3f,sizeof(g));

		id=tp=0;
		for(int i=1;i<=n;i++){
			int now=0;
			update(0,M,newline(-(i-1),f[i-1]),now);
			while(tp && a[stk[tp]]<=a[i]){
				now=merge(now,rt[tp--],0,M);
			}

			stk[++tp]=i,rt[tp]=now;
			lovef(0,M,newline(a[i],query(0,M,a[i],now)),info[tp-1],info[tp]);

			g[i]=query(0,M,i,info[tp]);
		}
		memcpy(f,g,sizeof(f));
		for(int i=1;i<=cnt;i++)t[i]=lc[i]=rc[i]=0;
		cnt=0;
	}
	printf("%lld\n",f[n]);
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