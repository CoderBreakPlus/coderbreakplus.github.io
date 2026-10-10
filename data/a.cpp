// created time: 2026-10-05 07:39:52
#include"stock.h"
#include<bits/stdc++.h>
#ifdef LOCAL
#include"_stock.cpp"
#endif

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
int n,k,a[2000005],w[2000005];
int get(int i,int j){
	if(!i||!j)return i^j;
	return a[i]>a[j]?i:j;
}
ll ans;
struct sgt{
	int mn[8000005],rs[8000005],tag[8000005];
	void pushup(int p){
		if(mn[p<<1]!=mn[p<<1|1]){
			int o=(p<<1)+(mn[p<<1|1]<mn[p<<1]);
			mn[p]=mn[o],rs[p]=rs[o];
		}else{
			mn[p]=mn[p<<1],rs[p]=rs[p<<1|1];
		}
	}
	void upd(int p,int w){ tag[p]+=w,mn[p]+=w; }
	void pushdown(int p){
		if(tag[p]){
			upd(p<<1,tag[p]);
			upd(p<<1|1,tag[p]);
			tag[p]=0;
		}
	}
	void update(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr){ upd(p,v); return; }
		pushdown(p); int mid=(l+r)>>1;
		update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
	void build(int l,int r,int p){
		if(l==r){ mn[p]=0, rs[p]=l; return; }
		int mid=(l+r)>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		pushup(p);
	}
}S;
void change(int i,int x){ w[i]+=x; }
int stk[2000005], tp;

ll stock(int N,int K,vector<int> a){
	n=N,k=K;
	a.pb(0); reverse(a.begin(), a.end());
	for(int i=1;i<=n;i++)::a[i]=a[i];
	S.build(1,n,1);

	for(int i=1;i<=n;i++){
		while(tp && a[stk[tp]]<a[i]) tp--;
		stk[++tp] = i;

		S.update(1,n,1,i,-1,1);
		int pos=S.mn[1]==-k-1?S.rs[1]:1;

		int L=1,R=tp,id=0;
		while(L<=R){
			int mid=(L+R)>>1;
			if(stk[mid]>=pos) id=stk[mid],R=mid-1;
			else L=mid+1; 
		}

		if(id && a[id]-a[i]>0){
			ans+=a[id]-a[i];
			change(id,1),change(i,-1);
			S.update(1,n,1,id,1,1);
		}else
			S.update(1,n,1,i,1,1);
	}
	return ans;
}