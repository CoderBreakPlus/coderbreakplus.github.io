// created time: 2026-08-26 09:17:17
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
ll mx[4000005],tag1[4000005];
ll cnt[4000005],tag2[4000005];
ll val[4000005];

void upd1(ll p,ll v){ mx[p]+=v, tag1[p]+=v; }

void pushd1(ll p){
	upd1(p<<1,tag1[p]),upd1(p<<1|1,tag1[p]),tag1[p]=0;
}
ll upd2(ll p,ll l,ll r,ll v,ll c){
	if(l==r){
		val[p]+=(v<mx[p])*c;
		return (v<mx[p])*c;
	}
	pushd1(p);
	ll ret=0;
	if(v<=mx[p<<1]){
		tag2[p]+=c;
		ret=(ll)cnt[p]*c+upd2(p<<1,l,mid,v,c);
	}else
		ret=upd2(p<<1|1,mid+1,r,v,c);
	val[p]+=ret; return ret;
}
void pushdown(ll p,ll l,ll r){
	pushd1(p);
	if(tag2[p]){
		upd2(p<<1|1,mid+1,r,mx[p<<1],tag2[p]);
		tag2[p]=0;
	}
}

ll qry(ll p,ll l,ll r,ll v){
	if(l==r) return mx[p]>v; 
	pushd1(p);
	if(v<=mx[p<<1]) return qry(p<<1,l,mid,v)+cnt[p];
	else return qry(p<<1|1,mid+1,r,v);
}
ll get(ll p,ll l,ll r,ll x){
	if(l==r) return mx[p];
	pushd1(p);
	if(x<=mid) return get(p<<1,l,mid,x);
	else return get(p<<1|1,mid+1,r,x);
}
void pushup(ll p,ll l,ll r){
	mx[p]=max(mx[p<<1],mx[p<<1|1]);
	val[p]=val[p<<1]+val[p<<1|1];
	cnt[p]=qry(p<<1|1,mid+1,r,mx[p<<1]);
}

ll query(ll p,ll l,ll r,ll ql,ll qr){
	if(r<ql||qr<l) return 0;
	if(ql<=l&&r<=qr){
		return val[p];
	}
	pushdown(p,l,r);
	return query(p<<1,l,mid,ql,qr)+query(p<<1|1,mid+1,r,ql,qr);
}
void modify(ll p,ll l,ll r,ll ql,ll qr,ll v){
	if(r<ql||qr<l) return;
	if(ql<=l&&r<=qr){ upd1(p,v); return; }
	pushdown(p,l,r);
	modify(p<<1,l,mid,ql,qr,v),modify(p<<1|1,mid+1,r,ql,qr,v);
	pushup(p,l,r);
}

ll update(ll p,ll l,ll r,ll ql,ll qr,ll v){
	if(r<ql||qr<l) return v;
	if(ql<=l&&r<=qr){
		upd2(p,l,r,v,1);
		return max(v,mx[p]);
	}
	pushdown(p,l,r);
	v=update(p<<1,l,mid,ql,qr,v);
	v=update(p<<1|1,mid+1,r,ql,qr,v);
	pushup(p,l,r); return v;
}
ll N,a[1000005];
void build(ll p,ll l,ll r){
	if(l==r){ mx[p]=a[l]; return; }
	build(p<<1,l,mid),build(p<<1|1,mid+1,r);
	pushup(p,l,r);
}
vector<ll> tower_events(vector<int> H, vector<vector<int>>E){
	N=H.size();
	for(int i=0;i<N;i++)a[i]=H[i];
	build(1,0,N-1);

	vector<ll>ret;
	for(auto Q: E){
		if(Q.size()==1) update(1,0,N-1,Q[0]+1,N-1,get(1,0,N-1,Q[0]));
		if(Q.size()==2) ret.pb(query(1,0,N-1,Q[0],Q[1]));
		if(Q.size()==3) modify(1,0,N-1,Q[0],Q[1],Q[2]);
	}
	return ret;
}