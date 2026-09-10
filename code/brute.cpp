// created time: 2026-09-10 09:51:25
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

int n,q;
int d[300005],x[300005],tp;

void procedure(){
	n=read(),q=read();
	while(q--){
		int op=read();
		if(op==1){
			d[++tp]=read(); x[tp]=read();
		}else{
			int l=read(),r=read();
			int ans=0;
			for(int w=l;w<=r;w++){
				int mn=1e9;
				for(int i=1;i<=tp;i++){
					if(d[i]==0){
						if(x[i]<w) continue;
						chkmin(mn,x[i]-w);
					}else{
						if(x[i]>w) continue;
						chkmin(mn,w-x[i]);
					}
				}
				chkmax(ans,mn);
			}
			printf("%d\n",ans<=n?ans:-1);
		}
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}