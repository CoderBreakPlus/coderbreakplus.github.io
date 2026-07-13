// created time: 2026-07-13 14:25:13
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

int n,m;
int s[200005],t[200005];

int lst[200005];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)s[i]=read();
	for(int i=1;i<=m;i++)t[i]=read();
	if(((n^m)&1) || s[1]!=t[1] || s[n]!=t[m]){ puts("No"); return; }
	for(int i=m;i>=1;i--){
		if(i<m && t[i]!=t[i+1])lst[i]=lst[i+1];
		else lst[i]=i;
	}
	int l=1,r=1;
	for(int i=2;i<=n;i++){
		if(s[i]!=s[i-1]){
			r=lst[l],l++;
			if((l^r)&1) r--;
		}else{
			int x=lst[l];
			if(x==m) { puts("No"); return; }
			if(x==l&&l==r){
				l=r=l+1;
				continue;
			}else{
				bool fuck=(r==x);
				int y=lst[x+1];
				l=x+1,r=y;
				if(!fuck&&t[l]==s[i])l++;
				if(t[l]!=s[i])l++;
				if((l^r)&1) r--;
			}
		}
		if(l>r){ puts("No"); return; }
	}
	puts(r==m?"Yes":"No");
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