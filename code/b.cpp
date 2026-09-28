// created time: 2026-09-28 19:42:56
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
const ll inf=1e12,INF=2e18;
int n,q,a[100005],l[100005],r[100005],k[100005];

vector<pair<ll,ll>>t[400005][2][2];

#define mid ((l+r)>>1)

template<class A, class B> pair<A, B> operator+(const pair<A, B>& x,const pair<A, B>& y) {
    return {x.fi + y.fi, x.se + y.se};
}
pair<ll,int> get(int p,int a,int b,ll v){
	auto &vec=t[p][a][b];
	int sz=lower_bound(vec.begin(),vec.end(),mkp(v,-INF))-vec.begin();
	return {vec[sz].se,sz};
}
void build(int l,int r,int p){
	if(l==r){
		t[p][0][0]={{2*a[l],0},{INF,-a[l]}};
		t[p][1][1]={{-2*a[l],0},{INF,a[l]}};
		t[p][0][1]=t[p][1][0]={{INF,0}};
		return;
	}
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);

	int len=r-l+1;
	for(int a:{0,1})for(int b:{0,1}){
		int sz=len-((len^a^b^1)&1);
		t[p][a][b].resize(sz+1);
		for(int i=0;i<=sz;i++){
			ll L=-inf,R=inf;
			while(L<=R){
				ll M=(L+R)>>1;
				auto [val,cnt]=max(get(p<<1,a,0,M)+get(p<<1|1,1,b,M),
					get(p<<1,a,1,M)+get(p<<1|1,0,b,M));
				if(cnt<=i){
					t[p][a][b][i]={M,val+(cnt-i)*M};
					L=M+1;
				}else
					R=M-1;
			}
		}
	}
}

pair<ll,ll> ans[2][2],A[2][2],B[2][2]; ll V;
void query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){
		memcpy(A,ans,sizeof(A));
		for(int a:{0,1})for(int b:{0,1})B[a][b]=get(p,a,b,V);
		for(int a:{0,1})for(int b:{0,1})for(int c:{0,1})
			chkmax(ans[a][c],A[a][b]+B[b^1][c]);
		return;
	}
	query(l,mid,ql,qr,p<<1);
	query(mid+1,r,ql,qr,p<<1|1);
}
pair<ll,int> solve(int l,int r){
	ans[1][0]=ans[0][1]={0,0},ans[0][0]=ans[1][1]={-INF,0};
	query(1,n,l,r,1);
	return max(ans[1][0],ans[0][1]);
}
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read();
	build(1,n,1);

	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read(),k[i]=read();

		ll L=-inf,R=inf,ans;
		while(L<=R){
			V=(L+R)>>1;
			auto [val,cnt]=solve(l[i],r[i]);
			if(cnt<=k[i]) ans=val-V*k[i],L=V+1;
			else R=V-1;
		}

		printf("%lld\n",ans);
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