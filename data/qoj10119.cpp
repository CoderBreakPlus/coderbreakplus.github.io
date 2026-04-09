// created time: 2026-04-09 08:55:27
// https://qoj.ac/contest/1924/problem/10119
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
const int M=2e5;

int n;
struct Node{
	ll l,r,h,y;
}s[200005];

struct Info{
	ll mx,lv,rv,cnt;
	Info(){ mx=-1, cnt=0; }
	Info(ll v){ mx=lv=rv=v, cnt=0; }
}t[800005];
Info operator+ (const Info &A, const Info &B){
	if(A.mx==-1)return B;
	if(B.mx==-1)return A;
	Info C; C.mx=max(A.mx,B.mx); C.lv=A.lv, C.rv=B.rv;
	if(A.mx==B.mx){
		C.cnt=A.cnt+B.cnt;
		if(A.rv!=A.mx || B.lv!=B.mx) C.cnt++;
	}else if(A.mx==C.mx) C.cnt=A.cnt;
	else C.cnt=B.cnt;
	return C;
}
ll tag[800005];
void pushup(int p){
	t[p]=t[p<<1]+t[p<<1|1];
}
void upd(int p,ll v){
	t[p]=Info(v), tag[p]=v;
}
void pushdown(int p){
	if(~tag[p]){
		upd(p<<1,tag[p]);
		upd(p<<1|1,tag[p]);
		tag[p]=-1;
	}
}
void build(int l,int r,int p){
	tag[p]=-1, t[p]=Info(0);
	if(l==r) return;
	int mid=(l+r)>>1;
	build(l,mid,p<<1),build(mid+1,r,p<<1|1);
}
void update(int l,int r,int ql,int qr,ll v,int p){
	if(r<ql || qr<l) return;
	if(ql<=l&&r<=qr) {
		upd(p,v);
		return;
	}
	int mid=(l+r)>>1; pushdown(p);
	update(l,mid,ql,qr,v,p<<1);
	update(mid+1,r,ql,qr,v,p<<1|1);
	pushup(p);
}
Info query(int l,int r,int ql,int qr,int p){
	if(r<ql || qr<l) return Info();
	if(ql<=l && r<=qr){
		return t[p];
	}
	int mid=(l+r)>>1; pushdown(p);
	return query(l,mid,ql,qr,p<<1)+query(mid+1,r,ql,qr,p<<1|1);
}
void procedure(){
	n=read();
	build(1,M,1);
	for(int i=1;i<=n;i++){
		int l=read()+1,r=read(),h=read();
		ll y=query(1,M,l,r,1).mx;
		s[i]={l,r,h,y};
		// cout<<"try to "<<y<<" + "<<h<<endl;
		update(1,M,l,r,y+h,1);
	}
	build(1,M,1);
	sort(s+1,s+n+1,[](const Node &A,const Node &B){ return A.y<B.y; });

	int ans=0;
	for(int i=1;i<=n;i++){
		auto [l,r,h,y]=s[i];
		// cout<<"put "<<l<<","<<r<<","<<h<<" on "<<y<<endl;
		Info L=Info(min(query(1,M,l-1,l-1,1).mx,y));
		Info Mid=query(1,M,l,r,1);
		Info R=Info(min(query(1,M,r+1,r+1,1).mx,y));

		// cout<<"L: "<<L.mx<<endl;
		// cout<<"Mid: "<<Mid.mx<<" "<<Mid.cnt<<endl;
		// cout<<"R: "<<R.mx<<endl;
		
		Info sum=L+Mid+R;
		ans += sum.cnt;
		update(1,M,l,r,y+h,1);
	}
	printf("%d\n",ans);
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