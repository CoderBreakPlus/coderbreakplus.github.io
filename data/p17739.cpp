// created time: 2026-11-20 16:14:57
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
inline ll read(){
	ll x=0, f=1; int ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
int n;
struct Node{
	int a,b,i;
}s[300005];

int stk[300005],tp,prv[300005],nxt[300005];
int val[300005],ans[300005];

pair<int,int> p[600005];
#define mid ((l+r)>>1)
namespace ds{
	const int M=1e7;
	int sum[M],lc[M],rc[M],cnt;
	void update(int b,int &p,int l,int r,int x){
		sum[p=++cnt]=sum[b]+1;
		if(l==r)return;
		lc[p]=lc[b],rc[p]=rc[b];
		if(x<=mid)update(lc[b],lc[p],l,mid,x);
		else update(rc[b],rc[p],mid+1,r,x);
	}
	int query(int p,int l,int r,int k){
		if(l==r) return l;
		if(sum[lc[p]]>=k) return query(lc[p],l,mid,k);
		else return query(rc[p],mid+1,r,k-sum[lc[p]]);
	}
}
int rt[300005];
int calc(int o,int k){
	auto [i,j]=p[o];
	if(i-1<k)return 2.1e9;
	int sb=ds::query(rt[i-1],0,n,k);
	int ret=max(s[j].a-s[i].b,max(s[i].a,val[sb])-s[j].b);
	return ret;
}
void solve(int l,int r,int ql,int qr){
	if(l>r)return;
	ans[mid]=2.1e9;
	int jc=-1;
	for(int i=ql;i<=qr;i++){
		int tmp=calc(i,mid);
		if(tmp<=ans[mid]){
			ans[mid]=tmp;
			jc=i;
		}
	}
	solve(l,mid-1,ql,jc);
	solve(mid+1,r,jc,qr);
}
int main(){
	n=read();
	for(int i=1;i<=n;i++){
		int a=read(),b=read();
		s[i]={a,b};
	}
	sort(s+1,s+n+1,[](Node A,Node B){ return A.a<B.a; });
	for(int i=1;i<=n;i++)s[i].i=i,val[i]=s[i].a;
	sort(s+1,s+n+1,[](Node A,Node B){ return A.b<B.b; });

	for(int i=1;i<=n;i++)
		ds::update(rt[i-1],rt[i],0,n,s[i].i);
		
	for(int i=1;i<=n;i++){
		#define v(x) s[x].i
		while(tp&&v(stk[tp])>v(i)) nxt[stk[tp--]]=i;
		if(tp)prv[i]=stk[tp];
		stk[++tp]=i;
		#undef v
	}

	int m=0;
	for(int i=1;i<=n;i++){
		if(nxt[i])p[++m]={i,nxt[i]};
		if(prv[i])p[++m]={prv[i],i};
	}
	sort(p+1,p+m+1);
	solve(0,n-2,1,m);
	for(int i=0;i<=n-2;i++)
		printf("%d\n",ans[n-2-i]);
}