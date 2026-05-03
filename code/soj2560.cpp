// created time: 2026-04-30 08:59:47
#include"tree.h"
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll

const int N = 150005, M = 6e6, D = 19;

int n,p[N+5];
struct Node{
	double h;
	int lc,rc,v;
}t[M];
int stk[M], tp;
int rt[N<<2],id[N],ds[N<<2],cnt;
vector<int>lst[N<<2];

double F = tree_hash(0,0);

void pushup(int x){
	t[x].h=tree_hash(t[t[x].lc].h,t[t[x].rc].h);
}
int newid(){
	int ret = (tp ? stk[tp--] : ++cnt);
	t[ret] = (Node){0,0,0,0};
	return ret;
}
int merge(int x,int y,int dep,vector<int>& vc){
	if(dep>=D) return 0;
	if(!x||!y) return x^y;
	int z=newid();
	if(t[x].v>t[y].v){
		t[z]=t[x];
		t[z].rc=merge(t[z].rc,y,dep+1,vc);
	}else{
		t[z]=t[y];
		t[z].lc=merge(x,t[z].lc,dep+1,vc);
	}
	vc.pb(z), pushup(z);
	return z;
}
int newnode(int v){
	int z=++cnt; t[z]=(Node){F,0,0,v};
	return z;
}
void modify(int p){
	for(auto x: lst[p]) stk[++tp]=x; lst[p].clear();
	rt[p]=merge(rt[p<<1],rt[p<<1|1],0,lst[p]);
}
void build(int l,int r,int p){
	if(l==r){
		rt[p]=newnode(::p[l]);
		id[l]=p;
		return;
	}
	int mid=(l+r)>>1;
	ds[p<<1]=ds[p<<1|1]=ds[p]+1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	modify(p);
}
vector<int>bin;
int query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr) return rt[p];
	int mid=(l+r)>>1;
	return merge(query(l,mid,ql,qr,p<<1),query(mid+1,r,ql,qr,p<<1|1),0,bin);
}
void init(vector<int>p){
	n = p.size();
	for(int i=0;i<n;i++) ::p[i]=p[i]; 
	build(0,n-1,1);
}

double solve(int x,int y,int l,int r){
	swap(p[x],p[y]);
	swap(rt[id[x]],rt[id[y]]);

	int u=id[x]>>1,v=id[y]>>1;
	if(ds[u]<ds[v])swap(u,v);
	while(ds[u]>ds[v]) modify(u),u>>=1;
	while(u&&v){
		modify(u);
		if(u^v)modify(v);
		u>>=1,v>>=1;
	}
	double ret=0;
	int ok=query(0,n-1,l,r,1);
	ret=t[ok].h;
	for(auto x: bin) stk[++tp]=x;
	bin.clear();
	return ret;
}