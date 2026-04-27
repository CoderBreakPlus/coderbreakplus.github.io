// created time: 2026-04-27 14:11:40
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
char s[1000005];
int n,c[10];

bool check(int mid){
	for(int i=0;2*i<=c[1];i++){
		// mid-i 个 0，mid 个 0~5，2*mid-i 个 0~9
		// 2i 个 c[1]
		c[1]-=2*i;

		bool flg=1;
		int cnt=c[0]-(mid-i); flg&=(cnt>=0);
		for(int i=1;i<=5;i++) cnt+=c[i];
		cnt-=mid;
		flg&=(cnt>=0);

		c[1]+=2*i;
		if(flg){
			// cout<<"at "<<mid<<" i="<<i<<" success"<<endl;
			return 1;
		}
	}
	return 0;
}
void procedure(){
	n=read();
	scanf("%s",s+1);
	memset(c,0,sizeof(c));
	for(int i=1;i<=n;i++)c[s[i]-'0']++;

	int L=0,R=n/4,ans=0;
	while(L<=R){
		int mid=(L+R)>>1;
		if(check(mid)){
			ans=mid;
			L=mid+1;
		}else R=mid-1;
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