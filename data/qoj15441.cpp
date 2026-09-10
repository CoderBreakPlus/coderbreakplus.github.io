// created time: 2026-09-10 08:31:56
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

int n,l[3];
vector<int>v[3];
void procedure(){
	n=read(),l[0]=read(),l[1]=read(),l[2]=read();
	for(int i:{0,1,2})v[i].clear();

	int tot=0;
	for(int i=1;i<=n;i++){
		int p=read()-1,c=read();
		v[p].pb(c); tot+=c;
	}
	for(int i:{0,1,2})sort(v[i].begin(),v[i].end());
	ll t=read();
	
	while(tot){
		t-=tot;
		int now=-1;
		for(int i:{0,1,2})if(!v[i].empty())
			if(tot<=l[i] && (now==-1 || v[i].back()>v[now].back()))now=i;
		if(now==-1){ puts("NO"); return; } 
		tot-=v[now].back(), v[now].pop_back();
	}

	puts(t>0?"YES":"NO");
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