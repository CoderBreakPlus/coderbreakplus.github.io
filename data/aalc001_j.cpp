// created time: 2026-10-12 14:08:18
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
const int M=4e7;
const ll L=1e18;
int c,lc[M+5],rc[M+5];
ll len[M+5],sum[M+5]; 
bool tag[M+5];

void pushup(int p){
	sum[p]=sum[lc[p]]+sum[rc[p]];
	if(tag[p])sum[p]=len[p]-sum[p];
}
void upd(int p){
	tag[p]^=1;
	sum[p]=len[p]-sum[p];
}
int rt;
void update(ll l,ll r,ll ql,ll qr,int &p){
	if(r<ql||qr<l) return;
	if(!p) p=++c,len[p]=(r-l+1);
	if(ql<=l&&r<=qr) return upd(p);
	ll mid=(l+r)>>1;
	update(l,mid,ql,qr,lc[p]),update(mid+1,r,ql,qr,rc[p]);
	pushup(p);
}
ll query(ll l,ll r,ll ql,ll qr,int p){
	if(r<ql||qr<l||!p)return 0;
	if(ql<=l&&r<=qr){
		// cout<<"here "<<l<<"->"<<r<<" sum="<<sum[p]<<endl;
		return sum[p];
	}
	ll mid=(l+r)>>1,len=min(r,qr)-max(l,ql)+1;
	ll ret=query(l,mid,ql,qr,lc[p])+query(mid+1,r,ql,qr,rc[p]);
	if(tag[p]) ret=len-ret;
	// cout<<"here "<<max(l,ql)<<"->"<<min(r,qr)<<" ret="<<ret<<endl;
	return ret;
}
void procedure(){
	int q=read();
	while(q--){
		int op=read();
		ll l=read(),r=read();
		if(op==1){
			update(1,L,l,r,rt);
		}else{
			printf("%lld\n",query(1,L,l,r,rt));
		}
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