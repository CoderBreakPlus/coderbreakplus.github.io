// created time: 2026-04-01 09:03:28
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

int n,m,lcp[1005][1005];
ll k;
char str[1005];
pair<int,int> s[600005];

bool cmp(pair<int,int> A,pair<int,int> B){
	auto [l,r]=A; auto [s,t]=B;
	int la=r-l+1, lb=t-s+1;
	int x=lcp[l][s];
	if(x<min(la,lb)) return str[l+x]<str[s+x];
	else return la<lb;
}
ll dp[1005][1005],g[1005][1005];
int pt[1005];

inline ll add(ll &a,ll b){ return a = min(k, a+b); }

void print(int l,int r){
	for(int i=l;i<=r;i++) putchar(str[i]);
	puts("");
}
ll solve(int l,int r){
	// print(l,r);
	for(int i=1;i<=n;i++){
		pt[i]=-1;
		for(int j=i;j<=n;j++){
			if(!cmp({i,j},{l,r})){
				pt[i]=j;
				break;
			}
		}
		// cout<<i<<" pt="<<pt[i]<<endl;
	}
	memset(dp,0,sizeof(dp));
	memset(g,0,sizeof(g));
	dp[0][0]=1;

	for(int i=1;i<=n;i++){
		if(~pt[i])
			for(int j=0;j<m;j++) add(g[pt[i]][j+1], dp[i-1][j]);
		for(int j=0;j<=m;j++) dp[i][j] = add(g[i][j], g[i-1][j]);

		// for(int j=0;j<=m;j++) cout<<dp[i][j]<<" ";cout<<endl;
	}
	// cout<<"ans="<<dp[n][m]<<endl;
	return dp[n][m];
}
void procedure(){
	n=read(),m=read(),k=read();
	scanf("%s",str+1);
	for(int i=n;i>=1;i--)
		for(int j=n;j>=1;j--)
			if(str[i]==str[j]) lcp[i][j]=1+lcp[i+1][j+1];

	int t=0;
	for(int l=1;l<=n;l++)
		for(int r=l;r<=n;r++) s[++t]={l,r};

	sort(s+1,s+t+1,cmp);
	
	int l=1,r=t,ans=t;
	while(l<=r){
		int mid=(l+r)>>1;
		if(solve(s[mid].fi,s[mid].se)>=k){
			ans=mid;
			l=mid+1;
		}else r=mid-1;
	}
	print(s[ans].fi,s[ans].se);
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