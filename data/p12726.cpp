// created time: 2026-11-23 15:02:32
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

ll n;
int q;

struct Info{
	vector<ll>ls,rs;
	ll len,cnt,ans;
	Info(int n=0){
		if(n){
			len=ans=1,cnt=0;
			ls=rs={1};
		}else{
			len=ans=cnt=0;
			ls=rs={0};
		}
	}
};

Info solve(int d,ll n,ll l,ll r,ll k){
	if(l>r) return Info(0);
	if(n==1) return Info(1);

	ll mid=(1ull<<d),len=((1ull<<d+1)-1);

	if(mid<l)return solve(d-1,n>>1,l-mid,r-mid,k);
	if(r<mid)return solve(d-1,n>>1,l,r,k);

	Info L,R;
	if(l==1&&r==len){
		L=R=solve(d-1,n>>1,1,mid-1,k);
	}else{
		L=solve(d-1,n>>1,l,mid-1,k);
		R=solve(d-1,n>>1,1,r-mid,k);
	}

	int lsz=L.rs.size(),rsz=R.ls.size(),o=(~n&1);
	Info W;
	W.len=1+L.len+R.len;
	W.cnt=o+L.cnt+R.cnt;
	W.ans=max(L.ans,R.ans);
	for(int i=0;i<lsz&&i+o<=k;i++)
		chkmax(W.ans,1+L.rs[i]+R.ls[min((ll)rsz-1,k-i-o)]);

	W.ls=L.ls, W.rs=R.rs;
	W.ls.resize(min(W.cnt,k)+1,0), W.rs.resize(min(W.cnt,k)+1,0);

	for(int i=0;i<lsz&&i+R.cnt+o<W.rs.size();i++)chkmax(W.rs[i+R.cnt+o],1+R.len+L.rs[i]);
	for(int i=0;i<rsz&&i+L.cnt+o<W.ls.size();i++)chkmax(W.ls[i+L.cnt+o],1+L.len+R.ls[i]);
	return W;
}
void procedure(){	
	n=read(),q=read();
	int p=lg2(n);
	while(q--){
		ll l=read(),r=read(),k=read();
		Info tmp=solve(p,n,l,r,k);
		printf("%lld\n",tmp.ans);
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