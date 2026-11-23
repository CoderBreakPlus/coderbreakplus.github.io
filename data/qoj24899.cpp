// created time: 2026-11-23 07:22:41
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

int n,h[300005],w[300005];
int prv0[300005],nxt0[300005];
int prv1[300005],nxt1[300005];

int stk[300005],tp;

ll suml[300005],sumr[300005],ans[300005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)h[i]=read();
	for(int i=1;i<=n;i++)w[i]=read();

	for(int i=1;i<=n;i++)prv0[i]=prv1[i]=0;
	for(int i=1;i<=n;i++)nxt0[i]=nxt1[i]=n+1;

	for(int i=1;i<=n;i++){
		while(tp&&h[stk[tp]]<h[i])
			nxt1[stk[tp--]]=i;
		if(tp)prv0[i]=stk[tp];
		stk[++tp]=i;
	}
	tp=0;
	for(int i=1;i<=n;i++){
		while(tp&&h[stk[tp]]<=h[i])
			nxt0[stk[tp--]]=i;
		if(tp)prv1[i]=stk[tp];
		stk[++tp]=i;
	}
	// for(int i=1;i<=n;i++)cout<<prv1[i]<<" "<<nxt1[i]<<endl;
	for(int i=1;i<=n;i++)
		suml[i]=suml[prv1[i]]+w[i];
	for(int i=n;i>=1;i--)
		sumr[i]=sumr[nxt1[i]]+w[i];

	for(int i=1;i<=n;i++){
		if(h[nxt0[i]]==h[i]){
			int val=min(w[i],w[nxt0[i]]);
			ans[i+1]-=val;
			ans[nxt0[i]]+=val;
		}
	}
	for(int i=1;i<=n;i++)ans[i]+=ans[i-1];

	for(int i=1;i<=n;i++)
		printf("%lld ",suml[i]+sumr[i]-w[i]+ans[i]);
	puts("");
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