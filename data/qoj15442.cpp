// created time: 2026-09-10 08:10:25
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

int n,a[1000005],nxt[1000005];
int stk[1000005],tp;

vector<int>res,res2;
void procedure(){
	n=read();
	vector<int>().swap(res);
	for(int i=1;i<=n;i++)a[i]=a[i+n]=read(),res.pb(i);	
	stk[tp=1]=2*n; a[2*n]=2e9;
	for(int i=2*n-1;i>=1;i--){
		while(a[i]>=a[stk[tp]]) tp--;
		nxt[i]=stk[tp];
		stk[++tp]=i;
	}
	int sz=0;
	while(sz<n){
		int ww=n-sz;
		int mn=2e9,len=0;
		for(int x: res){
			int exp=min(ww,nxt[x]-x);
			if(a[x]<mn) mn=a[x],len=exp;
			else if(a[x]==mn) chkmax(len,exp);
		}
		vector<int>().swap(res2);
		for(int x: res){
			if(a[x]==mn && min(ww,nxt[x]-x)==len) res2.pb(x+len);
		}
		swap(res,res2),sz+=len;
		while(len--)printf("%d ",mn);
	}
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}