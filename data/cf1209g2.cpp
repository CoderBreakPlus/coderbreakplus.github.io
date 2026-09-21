// created time: 2026-09-21 10:41:48
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

int n,q,a[200005];
set<int>s[200005];
struct Node{
	int mn,lv,rv,mv,sum;
}t[800005];
int tag[800005];

void pushup(int p){
	if(t[p<<1].mn==t[p<<1|1].mn){
		t[p].lv=t[p<<1].lv;
		t[p].rv=t[p<<1|1].rv;
		int val=max(t[p<<1].rv,t[p<<1|1].lv);
		t[p].sum=t[p<<1].sum+t[p<<1|1].sum
				-t[p<<1].rv-t[p<<1|1].lv+val;
	}else if(t[p<<1].mn<t[p<<1|1].mn){
		t[p]=t[p<<1];
		t[p].sum-=t[p].rv;
		chkmax(t[p].rv,t[p<<1|1].mv);
		t[p].sum+=t[p].rv;
	}else{
		t[p]=t[p<<1|1];
		t[p].sum-=t[p].lv;
		chkmax(t[p].lv,t[p<<1].mv);
		t[p].sum+=t[p].lv;
	}
	t[p].mn=min(t[p<<1].mn,t[p<<1|1].mn);
	t[p].mv=max(t[p<<1].mv,t[p<<1|1].mv);
}
void upd(int p,int v){ t[p].mn+=v; tag[p]+=v; }
void pushdown(int p){ upd(p<<1,tag[p]),upd(p<<1|1,tag[p]),tag[p]=0; }

void modify(int l,int r,int ql,int qr,int v,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){ upd(p,v); return; }
	pushdown(p);
	modify(l,mid,ql,qr,v,p<<1);modify(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
void update(int l,int r,int x,int v,bool f,int p){
	if(l==r){
		if(f) t[p].lv=v; else t[p].rv=v;
		t[p].mv=max(t[p].lv,t[p].rv);
		t[p].sum=t[p].lv+t[p].rv;
		return;
	}
	pushdown(p);
	if(x<=mid)update(l,mid,x,v,f,p<<1);
	else update(mid+1,r,x,v,f,p<<1|1);
	pushup(p);
}

void ins(int c){
	if(s[c].empty())return;
	int L=*s[c].begin(),R=*s[c].rbegin();
	modify(1,n-1,L,R-1,1,1);
	update(1,n-1,L,s[c].size(),1,1);
	if(L>1)update(1,n-1,L-1,s[c].size(),0,1);
}
void del(int c){
	if(s[c].empty())return;
	int L=*s[c].begin(),R=*s[c].rbegin();
	modify(1,n-1,L,R-1,-1,1);
	update(1,n-1,L,0,1,1);
	if(L>1)update(1,n-1,L-1,0,0,1);
}

void procedure(){
	n=read(),q=read();
	if(n==1){
		q++;while(q--)puts("0");
		return;	
	}
	for(int i=1;i<=n;i++)s[a[i]=read()].emplace(i);
	for(int i=1;i<=M;i++)ins(i);
	printf("%d\n", n-(t[1].mn?t[1].mv:t[1].sum));
	while(q--){
		int x=read(),v=read();
		if(a[x]!=v){
			del(a[x]),del(v);
			s[a[x]].erase(x); s[v].emplace(x);
			ins(a[x]),ins(v);
			a[x]=v;
		}
		printf("%d\n", n-(t[1].mn?t[1].mv:t[1].sum));
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