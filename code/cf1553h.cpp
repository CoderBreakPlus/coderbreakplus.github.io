// created time: 2026-06-13 16:29:21
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

int n,k,a[1<<19];

struct Node{
	int l,r,ans,len;
	Node(){ l=r=-1, ans=1e9, len=1; }
	Node(int L,int R,int Ans,int Len){ l=L,r=R,ans=Ans,len=Len; }
}t[(1<<20)+5];
int lc[(1<<20)+5],rc[(1<<20)+5],tag[(1<<20)+5],cnt;

void pushup(int p){
	if(~t[lc[p]].l) t[p].l=t[lc[p]].l;
	else if(~t[rc[p]].l) t[p].l=t[rc[p]].l+t[lc[p]].len;
	else t[p].l=-1;

	if(~t[rc[p]].r) t[p].r=t[rc[p]].r;
	else if(~t[lc[p]].r) t[p].r=t[lc[p]].r+t[rc[p]].len;
	else t[p].r=-1;

	t[p].ans=min(t[lc[p]].ans,t[rc[p]].ans);
	if((~t[lc[p]].r)&&(~t[rc[p]].l)) chkmin(t[p].ans,t[lc[p]].r+t[rc[p]].l);
}
void upd(int p){
	tag[p]^=1;
	swap(lc[p],rc[p]);
	swap(t[p].l,t[p].r);
}
void pushdown(int p){
	if(tag[p])
		upd(lc[p]),upd(rc[p]),tag[p]=0;
}
void build(int l,int r,int p){
	// cout<<l<<" "<<r<<" "<<p<<endl;
	t[p].len=r-l+1;
	if(l==r){
		if(a[l])t[p]=Node(0,0,1e9,1);
		return;
	}
	int mid=(l+r)>>1;
	build(l,mid,lc[p]=(p<<1)),build(mid+1,r,rc[p]=(p<<1|1));
	pushup(p);
	cout<<l<<"->"<<r<<" here "<<t[p].l<<" "<<t[p].r<<" "<<t[p].len<<" "<<t[p].ans<<endl;
}
void upd(int p,int d,int gl){
	if(d==gl){
		upd(p);
		return;
	}
	pushdown(p);
	upd(lc[p],d-1,gl),upd(rc[p],d-1,gl);
	pushup(p);
}
int ans[1<<19];

void procedure(){
	n=read(),k=read();
	while(n--)a[read()]=1;
	build(0,(1<<k)-1,1);
	for(int i=1,cur=0;i<=(1<<k);i++){
		ans[cur]=t[1].ans+1;
		// cout<<"cur="<<cur<<" ans="<<t[1].ans<<endl;
		int x=k-1-__builtin_ctz(i);
		upd(1,k-1,x);
		cur^=(1<<x);
	}
	for(int i=0;i<(1<<k);i++)
		printf("%d ",ans[i]);
	puts("");
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