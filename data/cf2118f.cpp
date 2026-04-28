// created time: 2026-04-28 19:45:53
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
string tmp="docker";

char s[500005];
int n,l[500005],r[500005],qz[500005];
pair<ll,ll> dp[500005];

pair<ll,ll> check(ll mid){
	for(ll i=0;i<=n;i++)dp[i]={-1e18,0};dp[0]={0,0};
	for(ll i=1;i<=n;i++){
		dp[i]=dp[i-1];
		if(i>=6) dp[i]=max(dp[i],{dp[i-6].fi-qz[i]+mid,dp[i-6].se+1});
	}
	return dp[n];
}
int sum[500005];

void procedure(){
	scanf("%s",s+1);n=strlen(s+1);
	int ok=0;
	for(int i=6;i<=n;i++){
		int cnt=0;
		for(ll j=i-5,k=0;j<=i;j++,k++)cnt+=(s[j]==tmp[k]);
		qz[i]=6-cnt;
		if(!qz[i])ok++;
	}

	int m=read();
	for(int i=0;i<=n/6+1;i++)sum[i]=0;
	for(int i=1;i<=m;i++){
		l[i]=read(),r[i]=min(read(),(ll)n/6);
		if(l[i]<=r[i])sum[l[i]]++,sum[r[i]+1]--;
	}
	for(int i=1;i<=n/6;i++)sum[i]+=sum[i-1];
	int mx=0;
	for(int i=ok;i<=n/6;i++){
		if(sum[i]>sum[mx]){
			mx=i;
		}
	}

	// cout<<"mx = "<<mx<<endl;
	int L=0,R=n;
	while(L<=R){
		int mid=(L+R)>>1;
		if(check(mid).se >= mx){
			R=mid-1;
		} else L=mid+1;
	}
	auto [x,y]=check(L);
	// cout<<mx<<" "<<L<<" "<<x<<" "<<y<<endl;
	int ans=-(x-(ll)mx*L);
	// cout<<"ans="<<ans<<endl;
	for(int i=0;i<ok;i++){
		if(sum[i]>sum[mx]){
			mx=i;
			ans=ok-i;
		}else if(sum[i]==sum[mx]) ans=min(ans,ok-i);
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