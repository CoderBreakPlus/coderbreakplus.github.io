// created time: 2026-09-07 07:56:20
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

int n,f[100005],seq[100005],tl;

char s[100005];
void procedure(){
	n=read();
	scanf("%s",s+1);
	int c0=0;
	tl=0;

	memset(f,0,sizeof(f));
	for(int i=1;i<=n;i++){
		if(s[i]=='1'){
			if(c0)
				seq[++tl]=c0;
		}
		else c0++;
	}
	f[c0]=1;
	int ans=1;
	for(int i=tl;i>=1;i--){
		for(int j=c0-1;j>=0;j--)addmod(f[j]+=f[j+1]);
		for(int j=seq[i]+1;j<=c0;j++)f[j]=0;

		for(int j=0;j<=c0;j++)
		addmod(ans+=f[j]);
	}
	printf("%d\n",ans);
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