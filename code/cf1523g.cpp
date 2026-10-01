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
int n,m,l[100005],r[100005];
struct Node{
	int x,y,i;
};
struct KDT{
	Node a[100005];
	int lx[200005],rx[200005],ly[200005],ry[200005];
	int cnt,lc[200005],rc[200005],mn[200005],fa[200005];
	void pushup(int p){ mn[p]=min(mn[lc[p]],mn[rc[p]]); }

	int build(int l,int r,int o){
		// cout<<"fuck "<<l<<" "<<r<<" "<<o<<endl;
		if(l==r){
			int p=a[l].i;
			lx[p]=rx[p]=::l[p];
			ly[p]=ry[p]=::r[p];
			return p;
		}
		int p=++cnt;
		int mid=(l+r)>>1;
		if(o) nth_element(a+l,a+mid,a+r+1,[&](const Node &A,const Node &B){ return A.x<B.x; });
		else nth_element(a+l,a+mid,a+r+1,[&](const Node &A,const Node &B){ return A.y<B.y; });

		lc[p]=build(l,mid,o^1),rc[p]=build(mid+1,r,o^1);
		fa[lc[p]]=fa[rc[p]]=p;

		// cout<<"link "<<p<<"->"<<lc[p]<<" and "<<p<<"->"<<rc[p]<<endl;
		pushup(p);
		lx[p]=min(lx[lc[p]],lx[rc[p]]); rx[p]=max(rx[lc[p]],rx[rc[p]]);
		ly[p]=min(ly[lc[p]],ly[rc[p]]); ry[p]=max(ry[lc[p]],ry[rc[p]]);
		// cout<<"at "<<p<<" here "<<lx[p]<<" "<<rx[p]<<" "<<ly[p]<<" "<<ry[p]<<endl;
		return p;
	}

	void upd(int x){
		// cout<<"start"<<endl;
		int t=x;
		while(t)chkmin(mn[t],x),t=fa[t];
		// cout<<"done upd"<<endl;
	}

	int query(int p,int a,int b,int c,int d){
		if(b<lx[p]||rx[p]<a||d<ly[p]||ry[p]<c) return 1e9;
		if(a<=lx[p]&&rx[p]<=b&&c<=ly[p]&&ry[p]<=d) return mn[p];
		return min(query(lc[p],a,b,c,d),query(rc[p],a,b,c,d));
	}
}kdt;
vector<int>vec[100005];
int ans[100005],rt;

int solve(int L,int R){
	if(L>R)return 0;
	int id=kdt.query(rt,L,R,L,R);
	// cout<<"solve "<<L<<" "<<R<<" id="<<id<<endl; 
	if(id>m)return 0;
	return solve(L,l[id]-1)+solve(r[id]+1,R)+r[id]-l[id]+1;
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		l[i]=read(),r[i]=read();
		kdt.a[i]=(Node){l[i],r[i],i}; kdt.mn[i]=1e9;
		vec[r[i]-l[i]+1].pb(i);
	}
	kdt.cnt=m;
	rt=kdt.build(1,m,0);

	for(int x=n;x>=1;x--){
		for(int i:vec[x]){
			kdt.upd(i);
		}
		ans[x]=solve(1,n);
	}
	for(int x=1;x<=n;x++)
		printf("%d\n",ans[x]);
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