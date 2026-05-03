// created time: 2026-05-03 14:29:41
// https://www.luogu.com.cn/problem/P16415
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

const int K=5;
int n;char st[200005];
int dp[200005][1<<K];

bool check(int l,int r,int o){
	if(l>r)return 0;
	if(l==r) return st[l]==o;
	else if(l+1==r) return (!(st[l]|st[r]))==o;
	else{
		if(l+2==r){
			if(!o){
				if(!st[l] && st[l+1] && !st[l+2]) return 0;
			}else{
				if(!st[l] && !st[l+1] && !st[l+2]) return 0;
				if(st[l] && !st[l+1] && st[l+2]) return 0;
				if(st[l] && st[l+1] && st[l+2]) return 0;
			}
		}
		return 1;
	}
}
void procedure(){
	n=read();
	scanf("%s",st+1);for(int i=1;i<=n;i++)st[i]-='0';
	for(int i=0;i<=n+1;i++)memset(dp[i],0,sizeof(dp[i]));

	dp[0][1]=1;
	int ans=0;

	// cout<<check(1,n,0)<<endl;
	// cout<<check(1,n,1)<<endl;

	for(int i=0;i<n;i++){
		for(int s=0;s<(1<<K);s++){
			if(!dp[i][s])continue;
			// cout<<"at "<<i<<" "<<s<<endl;
			for(int o:{0,1}){
				bool f=0;
				int news=0,sta=0;
				for(int t=0;t<K&&i+t+1<=n;t++)if((s>>t)&1){
					if(check(i+t+1,n,o))f=1;
					for(int j=0;j<K&&i+j+1<=n;j++)
						if(check(i+t+1,i+j+1,o))news|=(1<<j);
				}
				if(f){
					// cout<<"go "<<o<<" to end"<<endl;
					addmod(ans+=dp[i][s]);
				}
				if(!news) continue;
				int add=__builtin_ctz(news);
				addmod(dp[i+add+1][news>>add]+=dp[i][s]);
			}
		}
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