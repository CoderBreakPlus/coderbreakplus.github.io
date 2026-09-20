// created time: 2026-09-20 14:27:17
#include<vector>
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
#define fi first
#define se second
#define pb emplace_back
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
template<typename T>inline void chkmax(T &a,T b){ a=max(a,b); }
template<typename T>inline void chkmin(T &a,T b){ a=min(a,b); }
#define mid ((l+r)>>1)
typedef pair<double,int> P;

int n,q,a[100005],rt[100005];
double la[100005];
vector<tuple<int,int,double>>v[100005];

const int M=3e7+5;
int lc[M],rc[M],idx; P t[M];
double tag[M];

void pushup(int p){
	t[p]=min(t[lc[p]],t[rc[p]]);
	t[p].fi+=tag[p];
}
void build(int l,int r,int &p){
	p=++idx;
	if(l==r){
		t[p]={la[l],l};
		return;
	}
	build(l,mid,lc[p]),build(mid+1,r,rc[p]);
	pushup(p);
}
void update(int l,int r,int ql,int qr,double v,int b,int &p){
	if(r<ql||qr<l) return;
	p=++idx;
	lc[p]=lc[b],rc[p]=rc[b],tag[p]=tag[b],t[p]=t[b];
	if(ql<=l&&r<=qr){
		t[p].fi+=v,tag[p]+=v;
		return;
	}
	update(l,mid,ql,qr,v,lc[b],lc[p]);
	update(mid+1,r,ql,qr,v,rc[b],rc[p]);
	pushup(p);
}
P query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l) return {1e18,-1};
	if(ql<=l&&r<=qr) return t[p];
	P ret=min(query(l,mid,ql,qr,lc[p]),query(mid+1,r,ql,qr,rc[p])); ret.fi+=tag[p];
	return ret;
}

int fa[100005];
vector<int>node[100005];
int find(int x){ if(x!=fa[x]) fa[x]=find(fa[x]); return fa[x]; }

void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++)a[i]=read(),la[i]=log(a[i]);

	for(int i=1;i<=q;i++){
		int l1=read(),r1=read(),l2=read(),r2=read(),val=read(); double lv=log(val);
		v[l1].pb(l2,r2,lv),v[r1+1].pb(l2,r2,-lv);
		v[l2].pb(l1,r1,lv),v[r2+1].pb(l1,r1,-lv);

		int lx=max(l1,l2),rx=min(r1,r2);
		if(lx<=rx) v[lx].pb(lx,rx,-lv),v[rx+1].pb(lx,rx,lv);
	}
	for(int i=1;i<=n;i++) v[i].pb(i,i,-2*la[i]);
	build(1,n,rt[0]);
	for(int i=1;i<=n;i++){
		rt[i]=rt[i-1];
		for(auto [l,r,v]: v[i]) update(1,n,l,r,v,rt[i],rt[i]);
	}

	for(int i=1;i<=n;i++)fa[i]=i;
	int cnt=n-1;
	
	double sum=0;
	while(cnt){
		for(int i=1;i<=n;i++)node[i].clear();
		for(int i=1;i<=n;i++)node[find(i)].pb(i);

		vector<tuple<int,int,double>>add;

		for(int i=1;i<=n;i++)if(!node[i].empty()){
			int lst=0;
			vector<pair<int,int>>vc;
			for(int x:node[i]){
				if(lst+1<x) vc.pb(lst+1,x-1);
				lst=x;
			}
			if(lst<n)vc.pb(lst+1,n);

			P ret={1e18,-1};
			for(int x:node[i]){
				for(auto [l,r]: vc){
					P tmp=query(1,n,l,r,rt[x]);
					tmp.fi+=(r<x?la[x]:-la[x]);
					chkmin(ret,tmp);
				}
			}
			add.pb(i,find(ret.se),ret.fi);
		}

		for(auto [x,y,v]: add){
			if(find(x)==find(y))continue;
			fa[find(x)]=find(y),cnt--;
			if(v>22 || (sum+=exp(v))>1e9+1) sum=1e9+1;
		}
	}
	printf("%.10lf\n",min(1e9,sum));
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