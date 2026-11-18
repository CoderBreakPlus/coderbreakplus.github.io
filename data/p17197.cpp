// created time: 2026-11-18 19:28:51
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

int n,q,a[200005],nxt[200005],prv[200005],f[20][200005];
int l[200005],r[200005],tt[200005];

int stk[200005],tp;

int get(int x,int y){
	return a[x]>a[y]?x:y;
}
int query(int l,int r){
	int p=lg2(r-l+1);
	return get(f[p][l],f[p][r-(1<<p)+1]);
}

int t[200005];

namespace Link{
	struct Node{
		int pr,nx;
	}e[200005];
	bool active(int x){
		return a[e[x].pr]>a[x]&&a[x]<a[e[x].nx];
	}
	void main(){
		vector<int>pset;
		for(int i=1;i<=n;i++){
			e[i].pr=i-1,e[i].nx=i+1,t[i]=n+1;
			if(active(i)) pset.pb(i);
		}
		for(int i=1;!pset.empty();i++){
			vector<int>qset;
			for(int x:pset){
				t[x]=i;
				int l=e[x].pr,r=e[x].nx;
				e[l].nx=r,e[r].pr=l;
				if(active(l)) qset.pb(l);
				if(active(r)) qset.pb(r);
			}
			swap(pset,qset);
		}
	}
}

#define mid ((l+r)>>1)
namespace Love{
	const int M=3e7;
	int sum[M],lc[M],rc[M],id;
	void modify(int b,int &p,int l,int r,int x){
		p=++id;
		sum[p]=sum[b]+1;
		// cout<<"here "<<p<<" have "<<l<<" "<<r<<" "<<x<<" sum="<<sum[p]<<endl;
		if(l==r)return;
		lc[p]=lc[b],rc[p]=rc[b];
		if(x<=mid) modify(lc[b],lc[p],l,mid,x);
		else modify(rc[b],rc[p],mid+1,r,x);
	}
	int query(int p,int l,int r,int ql,int qr){
		if(r<ql||qr<l||!p)return 0;
		if(ql<=l&&r<=qr)return sum[p];
		return query(lc[p],l,mid,ql,qr)+query(rc[p],mid+1,r,ql,qr);
	}
}
int qz[200005],tl[200005],tr[200005];
void procedure(){
	n=read(),q=read();
	// assert(n<=5000);
	for(int i=1;i<=n;i++)a[i]=read(),f[0][i]=i;

	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
	for(int i=1;i<=n+1;i++)nxt[i]=n+1;
	for(int i=1;i<=n;i++){
		while(tp&&a[stk[tp]]<a[i])nxt[stk[tp--]]=i;
		prv[i]=stk[tp];
		stk[++tp]=i;
	}

	for(int i=1;(1<<i)<=n;i++)
		for(int j=1;j<=n-(1<<i)+1;j++)
			f[i][j]=get(f[i-1][j],f[i-1][j+(1<<i-1)]);
	Link::main();

	// for(int i=1;i<=n;i++) cout<<t[i]<<" "; cout<<endl;
	for(int i=1;i<=n;i++){
		Love::modify(qz[i-1],qz[i],1,n+1,t[i]);
		// cout<<"here "<<qz[i]<<endl;
		Love::modify(tl[prv[i]],tl[i],1,n+1,t[i]);
	}
	for(int i=n;i>=1;i--){
		Love::modify(tr[nxt[i]],tr[i],1,n+1,t[i]);
	}
	// for(int i=1;i<=n;i++) cout<<t[i]<<" "; cout<<endl;
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read(),tt[i]=read();
		int p=query(l[i],r[i]),ans=(t[p]<=tt[i]);
		// for(int j=l[i];j<=r[i];j++)ans+=(t[j]>tt[i]);

		int R0=Love::query(qz[r[i]],1,n+1,tt[i]+1,n+1);
		int L0=Love::query(qz[l[i]-1],1,n+1,tt[i]+1,n+1);
		ans+=R0-L0;

		ans+=Love::query(tr[l[i]],1,n+1,1,tt[i])-
			Love::query(tr[p],1,n+1,1,tt[i]);
		ans+=Love::query(tl[r[i]],1,n+1,1,tt[i])-
			Love::query(tl[p],1,n+1,1,tt[i]);
		// {
		// 	int x=l[i];
		// 	while(x!=p){
		// 		ans+=(t[x]<=tt[i]);
		// 		x=nxt[x];
		// 	}
		// }
		// {
		// 	int x=r[i];
		// 	while(x!=p){
		// 		ans+=(t[x]<=tt[i]);
		// 		x=prv[x];
		// 	}
		// }
		printf("%d\n",ans);
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