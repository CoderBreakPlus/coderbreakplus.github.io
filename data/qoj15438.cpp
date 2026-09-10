// created time: 2026-09-10 09:51:25
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
#define mid ((l+r)>>1)
int n,m,q;
int len[1200005],tag0[1200005],tag1[1200005],mx[1200005];
void build(int p,int l,int r){
	len[p]=r-l+1, mx[p]=1e9, tag0[p]=tag1[p]=-1;
	if(l==r) return;
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
}
void upd0(int p,int x){
	tag0[p]=x,tag1[p]=-1; mx[p]=x+len[p]-1;
}
void upd1(int p,int x){
	tag1[p]=x,tag0[p]=-1; mx[p]=x;
}
void pushdown(int p){
	if(~tag0[p]) upd0(p<<1,tag0[p]),upd0(p<<1|1,tag0[p]+len[p<<1]),tag0[p]=-1;
	if(~tag1[p]) upd1(p<<1,tag1[p]),upd1(p<<1|1,tag1[p]-len[p<<1]),tag1[p]=-1;
}
void pushup(int p){
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
}
int modify0(int p,int l,int r,int ql,int qr,int x){
	if(r<ql||qr<l) return 0;
	if(ql<=l && r<=qr){ upd0(p,x); return len[p]; }
	pushdown(p);
	int lf=modify0(p<<1,l,mid,ql,qr,x);
	lf+=modify0(p<<1|1,mid+1,r,ql,qr,x+lf);
	pushup(p); return lf;
}
int modify1(int p,int l,int r,int ql,int qr,int x){
	if(r<ql||qr<l) return 0;
	if(ql<=l && r<=qr){ upd1(p,x); return len[p]; }
	pushdown(p);
	int lf=modify1(p<<1,l,mid,ql,qr,x);
	lf+=modify1(p<<1|1,mid+1,r,ql,qr,x-lf);
	pushup(p); return lf;
}
int query(int p,int l,int r,int ql,int qr){
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr) return mx[p];
	pushdown(p);
	return max(query(p<<1,l,mid,ql,qr),query(p<<1|1,mid+1,r,ql,qr));
}
// 0: right 1: left
set<int>S[2];
set<pair<int,int>>w[2][300005];

int o[300005],a[300005],b[300005];

void push_seg(int d,int x,int l,int r){
	// cout<<"push_seg "<<d<<" "<<x<<" "<<l<<" "<<r<<endl;
	if(l>r)return;
	if(!d){
		modify0(1,1,n,l,r,l-x);
	}else{
		modify1(1,1,n,l,r,x-l);
	}
	auto it=w[d][x].lower_bound({l,0});
	if(it!=w[d][x].begin() && prev(it)->se==l-1) l=prev(it)->fi,it=w[d][x].erase(prev(it));
	if(it!=w[d][x].end() && it->fi==r+1) r=it->se,w[d][x].erase(it);
	w[d][x].emplace(l,r);
}
void solve(int l,int r){
	if(l>r)return;
	int L=-1e9, R=1e9;
	auto it=S[0].upper_bound(l);
	if(it!=S[0].begin())L=*prev(it);

	it=S[1].lower_bound(r);
	if(it!=S[1].end())R=*it;

	int pos=min(r,max(l-1,(L+R)>>1));

	// cout<<"belong "<<l<<" "<<r<<": "<<L<<" "<<R<<" pos="<<pos<<endl;

	if(L<0&&R>n){
		modify0(1,1,n,l,r,1e9);
	}else{
		if(l<=pos) push_seg(0,L,l,pos);
		if(pos<R) push_seg(1,R,pos+1,r); 
	}
}
void belong(int xx,int l,int r){
	if(xx==l) solve(l,l),solve(l+1,r);
	else if(xx==r) solve(l,r-1),solve(r,r);
	else solve(l,r);
}
void procedure(){
	n=read(),q=read();
	build(1,1,n);

	while(q--){
		int op=read();
		if(op==1){
			int d=read()^1,x=read();
			if(S[d].find(x)!=S[d].end())continue;
			o[++m]=op,a[m]=d,b[m]=x;
			S[d].emplace(x);
		}else{
			o[++m]=op,a[m]=read(),b[m]=read();
		}
	}
	for(int i=1;i<=n;i++)belong(-1,i,i);

	// for(int d:{0,1})
	// for(int i=1;i<=n;i++){
	// 	for(auto [l,r]: w[d][i]){
	// 		cout<<d<<","<<i<<" ["<<l<<","<<r<<"]\n";
	// 	}
	// }	

	vector<int>ans;
	for(int i=m;i>=1;i--){
		if(o[i]==2){
			// cout<<"querying "<<a[i]<<"->"<<b[i]<<endl;
			ans.pb(query(1,1,n,a[i],b[i]));
		}
		else{
			// cout<<"erasing"<<endl;
			S[a[i]].erase(b[i]);
			for(auto [l,r]: w[a[i]][b[i]]) 
				belong(b[i],l,r);
			w[a[i]][b[i]].clear();
		}
	}
	reverse(ans.begin(),ans.end());
	for(int x: ans){
		printf("%d\n", x<=n?x:-1);
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