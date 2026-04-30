// created time: 2026-04-30 07:19:42
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#include<bits/stdc++.h>
// #pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }
const int N = 1e6+5;
ll a[N];
int n,stk[N],tp;
int lf1[N],rh1[N],lf2[N],rh2[N];
int pos[64];
namespace DS{
	int val[N<<2],tag[N<<2],len[N<<2];
	bitset<N<<2>lf;
	int sx[N<<2],sy[N<<2],t,tx,ty;
	struct Node{
		int x1,x2,y1,y2;
	}a[N<<1];

	inline void ins(int p,int q,int r,int s){
		q++,s++;
		a[++t]={p,q,r,s};
		sx[++tx]=p,sx[++tx]=q;
		sy[++ty]=r,sy[++ty]=s;
	}
	inline void getx(int &x){ x=lower_bound(sx+1,sx+tx+1,x)-sx; }
	inline void gety(int &y){ y=lower_bound(sy+1,sy+ty+1,y)-sy; }

	vector<int>v[N]; int cnt[N];
	inline void build(int l,int r,int p){
		val[p]=tag[p]=lf[p]=0;
		if(l==r){ len[p]=sy[l+1]-sy[l],lf[p]=1; return; }
		int mid=(l+r)>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
		len[p]=len[p<<1]+len[p<<1|1];
	}
	inline void pushup(int p){
		val[p]=0;
		if(!lf[p])val[p]=val[p<<1]+val[p<<1|1];
		if(tag[p])val[p]=len[p];
	}
	inline void update(int l,int r,int ql,int qr,int v,int p){
		if(r<ql||qr<l)return;
		if(ql<=l&&r<=qr){
			tag[p]+=v, pushup(p);
			return;
		}
		int mid=(l+r)>>1;
		update(l,mid,ql,qr,v,p<<1),update(mid+1,r,ql,qr,v,p<<1|1);
		pushup(p);
	}
	inline ll solve(){
		sort(sx+1,sx+tx+1);tx=unique(sx+1,sx+tx+1)-(sx+2);
		sort(sy+1,sy+ty+1);ty=unique(sy+1,sy+ty+1)-(sy+2);
		build(1,ty,1);

		for(int i=1;i<=t;i++){
			getx(a[i].x1),getx(a[i].x2);
			gety(a[i].y1),gety(a[i].y2);
			cnt[a[i].x1]++,cnt[a[i].x2]++;
		}
		for(int i=1;i<=tx+1;i++) v[i].reserve(cnt[i]);
		for(int i=1;i<=t;i++){
			v[a[i].x1].pb(i);
			v[a[i].x2].pb(-i);
		}
		ll ret=0;
		for(int i=1;i<=tx;i++){
			for(auto id: v[i]){
				if(id>0)
					update(1,ty,a[id].y1,a[id].y2-1,1,1);
				else
					update(1,ty,a[-id].y1,a[-id].y2-1,-1,1);
			}
			ret+=(ll)(sx[i+1]-sx[i])*val[1];
		}
		for(int i=1;i<=tx+1;i++)vector<int>().swap(v[i]),cnt[i]=0;
		t=tx=ty=0;
		return ret;
	}
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)
		rh1[i]=rh2[i]=n+1,a[i]=read();
	tp=0;
	for(int i=1;i<=n;i++){
		while(tp && a[stk[tp]]<a[i]) rh1[stk[tp--]]=i;
		lf1[i]=stk[tp]; stk[++tp]=i;
	}
	tp=0;
	for(int i=1;i<=n;i++){
		while(tp && a[stk[tp]]>a[i]) rh2[stk[tp--]]=i;
		lf2[i]=stk[tp]; stk[++tp]=i;
	}

	for(int i=1;i<=n;i++)pos[__builtin_popcountll(a[i])]++;

	ll ans=(ll)n*(n+1);
	for(int o=0;o<64;o++){
		if(!pos[o].size())continue;
		for(auto i: pos[o]){
			DS::ins(lf1[i]+1,i,i,rh1[i]-1),DS::ins(lf2[i]+1,i,i,rh2[i]-1);
		}
		ll tmp=DS::solve();
		ans-=tmp;
	}
	printf("%lld\n",ans);
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
//shabi233