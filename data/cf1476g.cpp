// created time: 2026-11-13
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };
const int B=2154,B2=45;
int n,m,a[100005],bl[100005],bl2[100005],p[100005],x[100005],bf[100005],tim;
int lf[100005],rh[100005];

int cnt[100005],cnt2[100005],sum[100005],ans[100005];

struct Node{
	int l,r,t,k,id;
}que[100005]; int q;

int L,R,T;
void upd2(int x,int w){ cnt2[x]+=w; sum[bl2[x]]+=w; }
void upd(int x,int w){ upd2(cnt[x],-1); cnt[x]+=w; upd2(cnt[x],1); }

int seq[100005],sz;
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++) a[i]=read();
	for(int i=1;i<=n;i++) bl[i]=(i-1)/B+1,bl2[i]=(i-1)/B2+1,rh[bl2[i]]=i;
	for(int i=n;i>=1;i--) lf[bl2[i]]=i;

	while(m--){
		int op=read();
		if(op==1){
			++q;
			que[q].id=q, que[q].t=tim;
			que[q].l=read(),que[q].r=read(),que[q].k=read();
		}else{
			++tim;
			p[tim]=read(),x[tim]=read();
			bf[tim]=a[p[tim]]; a[p[tim]]=x[tim];
		}
	}
	L=1,R=0,T=tim;

	sort(que+1,que+q+1,[](Node x,Node y){
		if(bl[x.l]!=bl[y.l]) return x.l<y.l;
		else if(bl[x.r]!=bl[y.r]) return x.r<y.r;
		else return x.t<y.t;
	});

	for(int i=1;i<=q;i++){
		while(L>que[i].l) upd(a[--L],1);
		while(R<que[i].r) upd(a[++R],1);
		while(L<que[i].l) upd(a[L++],-1);
		while(R>que[i].r) upd(a[R--],-1);
		
		while(T>que[i].t){
			bool flg=(L<=p[T] && p[T]<=R);
			if(flg) upd(a[p[T]],-1);
			a[p[T]]=bf[T];
			if(flg) upd(a[p[T]],1);
			T--;
		}
		while(T<que[i].t){
			++T;
			bool flg=(L<=p[T] && p[T]<=R);
			if(flg) upd(a[p[T]],-1);
			a[p[T]]=x[T];
			if(flg) upd(a[p[T]],1);
		}
		sz=0;
		for(int x=1;x<=bl2[n];x++)
			if(sum[x]){
				for(int y=lf[x];y<=rh[x];y++){
					int z=cnt2[y];
					while(z--) seq[++sz]=y;
				}
			}

		int k=que[i].k;
		if(sz<k){ans[que[i].id]=-1; continue;}
		ans[que[i].id]=n;

		for(int x=k;x<=sz;x++)
			ans[que[i].id]=min(ans[que[i].id], seq[x]-seq[x-k+1]);
	}
	for(int i=1;i<=q;i++) printf("%d\n",ans[i]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}