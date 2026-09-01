// created time: 2026-09-01 19:59:50
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

int n,m,q;
char s[505];
int t[505][505][2][2];

void procedure(){
	n=read(),m=read(),q=read();
	bool v[2];
	for(int i=1;i<=n;i++){
		scanf("%s",s+1);
		if(m==1) v[s[1]-'0']=1;
		for(int j=1;j<=m;j++)
			for(int k=j+1;k<=m;k++)t[j][k][s[j]-'0'][s[k]-'0']=1;
	}

	while(q--){
		scanf("%s",s+1);
		if(m==1){
			puts(v[s[1]-'0']?"Yes":"No");
			continue;
		}
		bool flg=1;
		for(int j=1;j<=m;j++)
			for(int k=j+1;k<=m;k++)
				flg&=t[j][k][s[j]-'0'][s[k]-'0'];
		puts(flg?"Yes":"No");
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