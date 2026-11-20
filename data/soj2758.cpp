// created time: 2026-11-19 08:01:48
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 1e9+7;
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
const int M=600;
int n,m;
char s[605][605];
int nxt[605][2];
int f[605][605][2],dp[605][605];

void solve(int op,int x,char *s){
	memset(dp,0,sizeof(dp));
	nxt[m+1][0]=nxt[m+1][1]=m+1;
	for(int i=m;i>=1;i--){
		nxt[i][0]=nxt[i+1][0];
		nxt[i][1]=nxt[i+1][1];
		if(s[i]=='(')nxt[i][0]=i;
		else nxt[i][1]=i;
	}
	dp[0][0]=1;
	for(int i=0;i<m;i++){
		for(int j=0;j<=i;j++){
			if(nxt[i+1][0]<=m)
				addmod(dp[nxt[i+1][0]][j+1]+=dp[i][j]);
			if(j&&nxt[i+1][1]<=m)
				addmod(dp[nxt[i+1][1]][j-1]+=dp[i][j]);
		}
	}
	if(op){
		for(int i=1;i<=m;i++)
			for(int j=0;j<=i;j++){
				addmod(f[x][j][s[i]=='(']+=dp[i][j]);
			}
	}
}
int buc[605][2];

void procedure(){
	n=read();
	for(int o=0;o<n;o++){
		scanf("%s",s[o]+1);
		m=strlen(s[o]+1);
		reverse(s[o]+1,s[o]+m+1);
		for(int i=1;i<=m;i++)
			if(s[o][i]=='(')s[o][i]=')';else s[o][i]='(';
		solve(1,o,s[o]);
		reverse(s[o]+1,s[o]+m+1);
		for(int i=1;i<=m;i++)
			if(s[o][i]=='(')s[o][i]=')';else s[o][i]='(';

		// cout<<"o="<<o<<endl;
		// for(int j=0;j<=m;j++){
		// 	cout<<f[o][j][0]<<" "<<f[o][j][1]<<endl;
		// }
	}
	for(int i=0;i<n;i++){
		m=strlen(s[i]+1);
		solve(0,i,s[i]);
		int bas=0;

		memset(buc,0,sizeof(buc));
		for(int j=0;j<=m;j++){
			if(j)addmod(bas+=dp[j][0]);
			bool h[2]={1,1};
			for(int k=j+1;k<=m;k++){
				h[0]&=(s[i][k]==')');
				h[1]&=(s[i][k]=='(');
			}
			if(h[0]){
				for(int k=0;k<=j;k++)
					addmod(buc[k][0]+=dp[j][k]);
			}
			if(h[1]){
				for(int k=0;k<=j;k++)
					addmod(buc[k][1]+=dp[j][k]);
			}
		}
		// cout<<"bas="<<bas<<endl;
		// for(int j=0;j<=m;j++){
		// 	cout<<buc[j][0]<<" "<<buc[j][1]<<endl;
		// }
		for(int j=0;j<n;j++){
			int ans=bas;
			for(int k=0;k<=m;k++)
				ans=(ans+(ull)buc[k][0]*f[j][k][0]
					+(ull)buc[k][1]*f[j][k][1])%mod;
			printf("%d ",ans);
		}
		puts("");
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