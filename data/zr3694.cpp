// created time: 2026-11-10 07:38:43
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

int n,w;
char s[6005],t[6005],st[12005];
int dp[6005],pos[6005],bor[12005];

int hi[6005][6005];
void procedure(){
	n=read();
	scanf("%s",s+1);
	scanf("%s",t+1);

	memset(dp,0x3f,sizeof(dp));
	dp[0]=0;

	for(int i=n;i>=1;i--)
		for(int j=1;j<=n;j++)
			if(s[i]==t[j])hi[i][j]=hi[i+1][j-1]+1;
	for(int i=1;i<=n;i++){
		if(s[i]==t[i])chkmin(dp[i],dp[i-1]);
		w=0;
		for(int j=i;j<=n;j++)st[++w]=t[j];
		st[++w]='$';
		for(int j=i;j<=n;j++)st[++w]=s[j],pos[j]=w;

		for(int j=2;j<=w;j++){
			bor[j]=bor[j-1];
			while(bor[j]&&st[1+bor[j]]!=st[j])bor[j]=bor[bor[j]];
			if(st[1+bor[j]]==st[j])bor[j]++;
		}
		for(int j=i;j<=n;j++){
			int len=j-i+1-bor[pos[j]];
			// bool flg=1;
			// for(int k=1,l=i,r=j;k<=len;k++,l++,r--)
			// 	flg&=(s[l]==t[r]);
			if(hi[i][j]>=len) chkmin(dp[j],dp[i-1]+1);
		}
	}
	printf("%d\n",dp[n]<=n?dp[n]:-1);
}
int main(){
	assert(freopen("buffer.in","r",stdin));
	assert(freopen("buffer.out","w",stdout));
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}