// created time: 2026-08-13 14:13:37
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

int n,a[400005],vis[400005],ok[400005];

void procedure(){
	n=read();
	for(int i=1;i<=2*n;i++)vis[i]=ok[i]=0;
	for(int i=1;i<=2*n;i++)a[i]=read();

	int cnt=n;
	int ans=0,mor=0;
	for(int i=1;i<=2*n;i+=2){
		if(a[i]&&a[i+1]){
			ok[a[i]]=ok[a[i+1]]=1;
			cnt--;
		}else{
			if(a[i])vis[a[i]]=1;
			if(a[i+1])vis[a[i+1]]=1;
			if(!a[i]&&!a[i+1])mor++;
		}
	}
	ans=qpow(2,mor);
	for(int i=1;i<=mor;i++)ans=(ull)ans*i%mod;
	
	int s1=cnt,t1=0,s2=cnt,t2=0;
	for(int i=1,c=0;i<=2*n;i++){
		if(ok[i])continue;
		c++;
		if(c>cnt) t2+=vis[i];
		else t1+=vis[i];
	}

	s1-=t1,s2-=t2;
	while(t1--) ans=(ull)ans*(s2--)%mod;

	t2+=s2;
	while(s1--) ans=(ull)ans*(t2--)%mod;
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