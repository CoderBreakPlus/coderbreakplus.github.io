// created time: 2026-05-03 14:17:07
// https://www.luogu.com.cn/problem/P16414
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,p[100005],ans[100005];
void procedure(){
	n=read();
	if(n!=1 && lg2(n)!=lg2(n+1)){
		puts("-1");
		fflush(stdout);
		return;
	}
	for(int i=1;i<=n;i++) p[i]=i;
	sort(p+1,p+n+1,[](int x,int y){ return popcnt(x)==popcnt(y)?x<y:popcnt(x)<popcnt(y); });
	
	int t = n;

	int ok=0;
	for(int i=1;i<n;i++){
		if(p[i]==t)continue;
		printf("%d ",p[i]);
		ans[++ok]=p[i];
	}
	if(p[n]!=n){
		printf("%d %d\n",t,p[n]);ans[++ok]=t,ans[++ok]=p[n];
	}else{
		printf("%d\n",p[n]);ans[++ok]=p[n];
	}
	fflush(stdout);

	for(int i=1;i<n;i++){
		// cout<<"checking "<<i<<endl;
		assert((ans[i]&ans[i+1])!=ans[i]);
		assert((ans[i]&ans[i+1])!=ans[i+1]);
	}
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