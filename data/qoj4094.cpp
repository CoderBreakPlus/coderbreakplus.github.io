// created time: 2026-07-08 15:39:32
#include "histogram.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back

inline int lg2(int x){ return 31^__builtin_clz(x); }
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }

const int M = 5e5;

int n,h[500005],f[20][500005],lc[500005],rc[500005],fa[500005];
ll qz2[500005],hz2[500005];

int get(int x,int y){ return h[x]<h[y]?x:y; }
int query(int l,int r){
	int p = lg2(r-l+1);
	return get(f[p][l], f[p][r-(1<<p)+1]);
}
struct Line{
	ll k,b;
	ll val(ll x){ return (ll)k*x+b; }
}s[1500005]; int id;

int rt1[500005],rt2[500005];
ll a0[500005],a1[500005],a2[500005],a3[500005],ans3;

int t[20000005],ls[20000005],rs[20000005],cid;

int new_line(ll k,ll b){
	s[++id] = (Line){k,b};
	return id;
}
void update(int l,int r,int x,int &p){
	if(l>r) return;
	if(!p){
		t[p=++cid]=x;
		return;
	}
	int mid=(l+r)>>1;
	if(s[t[p]].val(mid)<s[x].val(mid)) swap(t[p],x);

	if(s[x].k>s[t[p]].k) update(mid+1,r,x,rs[p]);
	if(s[x].k<s[t[p]].k) update(l,mid-1,x,ls[p]);
}
int merge(int x,int y,int l,int r){
	if(!x||!y) return x|y;
	int mid=(l+r)>>1;
	if(s[t[y]].val(mid)>s[t[x]].val(mid))swap(t[x],t[y]);
	ls[x]=merge(ls[x],ls[y],l,mid-1);
	rs[x]=merge(rs[x],rs[y],mid+1,r);

	if(s[t[y]].k>s[t[x]].k) update(mid+1,r,t[y],rs[x]);
	if(s[t[y]].k<s[t[x]].k) update(l,mid-1,t[y],ls[x]);
	return x;
}

ll query(int l,int r,int x,int p){
	if(!p) return -1e18;
	int mid=(l+r)>>1;

	ll ret=s[t[p]].val(x);
	if(x<mid) chkmax(ret,query(l,mid-1,x,ls[p]));
	if(x>mid) chkmax(ret,query(mid+1,r,x,rs[p]));
	return ret;
}
int build(int l,int r,int f){
	if(l>r) return 0;
	int p=query(l,r);
	fa[p]=f;
	ll area=(ll)h[p]*(r-l+1);
	a0[p]=area;
	lc[p]=build(l,p-1,p),rc[p]=build(p+1,r,p);

	a1[p]=max({a1[lc[p]],a1[rc[p]],area});
	a2[p]=max({a2[lc[p]],a2[rc[p]],a1[lc[p]]+a1[rc[p]]});
	a3[p]=max({a3[lc[p]],a3[rc[p]],a1[lc[p]]+a2[rc[p]],a2[lc[p]]+a1[rc[p]]});

	rt1[p]=merge(rt1[lc[p]],rt1[rc[p]],-M,0);
	rt2[p]=merge(rt2[lc[p]],rt2[rc[p]],-M,0);

	ll tmp;
	chkmax(a2[p], tmp=area+query(-M,0,-h[p],rt1[p]));
	chkmax(a3[p], area+query(-M,0,-h[p],rt2[p]));

	update(-M,0,new_line(r-l+1,area),rt1[p]);
	update(-M,0,new_line(r-l+1,tmp),rt2[p]);
	
	return p;
}
vector<ll> max_area(vector<int> H){
	n=H.size();
	for(int i=1;i<=n;i++)h[i]=H[i-1];
	for(int i=1;i<=n;i++)f[0][i]=i;
	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);

	int p=build(1,n,0);
	return {a1[p],max(a1[p],a2[p]),max({a1[p],a2[p],a3[p],ans3})};
}