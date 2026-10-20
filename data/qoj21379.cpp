// created time: 2026-09-29
#pragma GCC optimize("Ofast")
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
const ll inf=1e6,INF=2e18;
int n,q,a[100005],l[100005],r[100005],k[100005];
ll out[100005];

vector<pair<ll,ll>>t[400005][2][2];
ll L[100005],R[100005],M[100005]; 
ull big[10000005]; int tp,now;

int tl[1600005];
int tl2[400005][2][2];

ull encode(int a,int b,int c,int d){ return ((ull)a<<22)^(b<<2)^(c<<1)^d; }
void decode(ull w,int &b,int &c,int &d){ d=w&1, c=(w&2)>>1, b=(w&((1<<22)-4))>>2; }
#define mid ((l+r)>>1)

template<class A, class B> pair<A, B> operator+(const pair<A, B>& x,const pair<A, B>& y) {
	return {x.fi + y.fi, x.se + y.se};
}

pair<ll,int> get(int p,int a,int b,ll v){
	auto &vec=t[p][a][b];
	int sz=lower_bound(vec.begin(),vec.end(),mkp(v,-INF))-vec.begin();
	return {vec[sz].se+sz*v,sz}; 
}
pair<ll,int> fast_get(int p,int a,int b,ll v){
	auto &vec=t[p][a][b];
	int sz=tl[(p<<2)|(a<<1)|b];
	return {vec[sz].se+sz*v,sz};
}
pair<ll,int> point_get(int p,int a,int b,ll v){
	auto &vec=t[p][a][b]; int &sz=tl2[p][a][b];
	while(sz<vec.size()&&vec[sz].fi<v)sz++;
	while(sz>0&&vec[sz-1].fi>=v)sz--; 
	return {vec[sz].se+sz*v,sz};
}
void build(int l,int r,int p){
	if(l==r){
		t[p][0][0]={{inf,-a[l]}};
		t[p][1][1]={{inf,a[l]}};
		t[p][0][1]=t[p][1][0]={{inf,0}};
		return;
	}
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);

	int len=r-l+1;
	for(int a:{0,1})for(int b:{0,1}){
		int sz=(len-((len^a^b^1)&1))/2;
		t[p][a][b].resize(sz+1);
		auto solve=[&](auto &&self,int l,int r,ll L,ll R){
			if(l>r||L>R)return;
			ll M=(L+R)>>1;
			auto o1 = point_get(p<<1,a,0,M)+point_get(p<<1|1,1,b,M); if(a==0&&b==1) o1.fi+=M,o1.se++;
			auto o2 = point_get(p<<1,a,1,M)+point_get(p<<1|1,0,b,M); if(a==1&&b==0) o2.fi+=M,o2.se++;
			auto [val,cnt] = (o1.fi != o2.fi) ? max(o1, o2) : (o1.se < o2.se ? o1 : o2);
			
			for(int i=max(l,cnt);i<=r;i++)
				t[p][a][b][i]={M,val-i*M};

			self(self,max(l,cnt),r,M+1,R);
			self(self,l,min(r,cnt-1),L,M-1);
		};
		solve(solve,0,sz,-inf,inf);
		t[p][a][b][sz].fi=INF;
		for(int i=0;i<sz;i++)
			big[++tp]=encode(t[p][a][b][i].fi+inf,p,a,b);
	}
}

pair<ll,int> ans[2]; ll V;
inline void add_in(int p){
	auto b10=fast_get(p,1,0,V);
	auto b00=fast_get(p,0,0,V);
	auto b11=fast_get(p,1,1,V);
	auto b01=fast_get(p,0,1,V);

	auto x=ans[0], y=ans[1];

	auto o10=x+b10;
	auto o20=y+b00;

	if(o10.fi>o20.fi || (o10.fi==o20.fi&&o10.se<o20.se))
		ans[0]=o10;
	else
		ans[0]=o20;

	auto o11=x+b11;
	o11.fi+=V;
	++o11.se;

	auto o21=y+b01;

	if(o11.fi>o21.fi || (o11.fi==o21.fi&&o11.se<o21.se))
		ans[1]=o11;
	else
		ans[1]=o21;
}

const int MAXS=4000005;
int pool[MAXS],tot;
int qL[100005],qR[100005];
void query(int l,int r,int ql,int qr,int p){
	if(r<ql||qr<l)return;
	if(ql<=l&&r<=qr){pool[tot++]=p; return;}
	query(l,mid,ql,qr,p<<1);
	query(mid+1,r,ql,qr,p<<1|1);
}
pair<ll,int> solve(int i){
	ans[1]={0,0},ans[0]={-INF,0};
	for(int j=qL[i];j<qR[i];++j)
		add_in(pool[j]);
	return ans[1];
}

void clear(){ memset(tl,0,sizeof(tl)); now=1; }
void move_to(ll v){
	V=v;
	ull lim=(V+inf)<<22;
	while(now<=tp&&big[now]<lim){
		tl[big[now]&((1<<22)-1)]++;
		++now;
	}
	while(now>1 && big[now-1]>=lim){
        --now;
        --tl[big[now]&((1<<22)-1)];
    }
}
ull ord[100005];
void procedure(){
	n=read(),q=read();
	for(int i=1;i<=n;i++) a[i]=read(); 
	build(1,n,1);
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read(),k[i]=read();
		L[i]=-inf,R[i]=0;
		qL[i]=tot;
		query(1,n,l[i],r[i],1);
		qR[i]=tot;
	}
	sort(big+1,big+tp+1);
	ll T=20;
	while(T--){
		clear(); int Q=0;
		for(int i=1;i<=q;i++)if(L[i]<=R[i]){ord[++Q]=(((M[i]=(L[i]+R[i])>>1)+inf)<<20)^i;}
		sort(ord+1,ord+Q+1);
		for(int I=1;I<=Q;I++){
			int i=ord[I]&((1<<20)-1);
			move_to(M[i]);
			auto [val,cnt]=solve(i);
			if(cnt<=k[i]) out[i]=val-M[i]*k[i],L[i]=M[i]+1;
			else R[i]=M[i]-1;
		}
	}
	for(int i=1;i<=q;i++)
		printf("%lld\n",out[i]);
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