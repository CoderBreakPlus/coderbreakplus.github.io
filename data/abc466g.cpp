// created time: 2026-11-16 14:50:37
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

int n,m,fa[10];
bool cov[10];
vector<int>vec[10];
int find(int x){
	if(x!=fa[x])fa[x]=find(fa[x]);
	return fa[x];
}
ll f[10][10];

tuple<int,int,int>lim[10];
int c;

const int M=30;
int dp[M][10005];
int get_hash(const vector<int>& s){
	int now=0;
	for(int i=0;i<c;i++){
		auto [l,r,w]=lim[i];
		now=now*(r-l+1)+s[i];
	}
	return now;
}
int dfs(int x,vector<int> seq){
	if(x==M) return *max_element(seq.begin(),seq.end())==0;
	int hsh=get_hash(seq);
	if(~dp[x][hsh])return dp[x][hsh];
	dp[x][hsh]=0;

	for(int s=0;s<(1<<n);s++){
		vector<int>seq2=seq;
		bool flg=1;
		for(int i=0;i<c;i++){
			auto [l,r,w]=lim[i];
			seq2[i]=seq[i]+__builtin_popcount(s&((1<<r+1)-(1<<l)));
			if((seq2[i]&1)!=((w>>x)&1)){
				flg=0;
				break;
			}
			seq2[i]>>=1;
		}
		if(flg)addmod(dp[x][hsh]+=dfs(x+1,seq2));
	}
	return dp[x][hsh];
}
void procedure(){
	n=read(),m=read();
	for(int i=0;i<=n;i++)fa[i]=i;
	memset(f,0x3f,sizeof(f));
	for(int i=0;i<=n;i++)f[i][i]=0;
	for(int i=0;i<m;i++){
		int l=read()-1,r=read(),s=read()-(r-l);
		fa[find(l)]=find(r);
		f[l][r]=s,f[r][l]=-s;
		for(int j=l;j<r;j++)cov[j]=1;
	}	
	for(int i=0;i<n;i++)chkmin(f[i+1][i],0ll);
	for(int i=0;i<=n;i++)vec[find(i)].pb(i);
	for(int k=0;k<=n;k++)
		for(int i=0;i<=n;i++)
		for(int j=0;j<=n;j++)
			chkmin(f[i][j],f[i][k]+f[k][j]);

	for(int i=0;i<=n;i++)if(f[i][i]<0){
		puts("0");
		return;
	}
	for(int i=0;i<n;i++)if(!cov[i]){
		puts("Infinity");
		return;
	}
	for(int i=0;i<=n;i++)if(find(i)==i){
		for(int j=1;j<vec[i].size();j++){
			lim[c++]={vec[i][j-1],vec[i][j]-1,f[vec[i][j-1]][vec[i][j]]};
		}
	}
	memset(dp,-1,sizeof(dp));
	printf("%d\n",dfs(0,vector<int>(c,0)));
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