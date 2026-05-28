// created time: 2026-05-28 10:10:43
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

int n,w,id=1;
char s[505];

int son[505][10],sum[505];
int f[505][505][11],dep[505];
int tmp[11];
void ins(int x){
	int len=strlen(s),rt=1;
	for(int i=0;i<len;i++){
		int w=s[i]-'0';
		if(!son[rt][w])son[rt][w]=++id;
		rt=son[rt][w];
		sum[rt]+=x,dep[rt]=i+1;
	}
}

void dfs(int x){
	for(int o=0;o<10;o++)
		if(son[x][o])dfs(son[x][o]);
	for(int d=0;d<=dep[x];d++){
		memset(f[x][d],0xc0,sizeof(f[x][d]));
		f[x][d][x>1&&!d]=0;
		for(int o=0;o<10;o++){
			if(!son[x][o])continue;
			int y=son[x][o];

			memset(tmp,0xc0,sizeof(tmp));
			for(int j=0;j<=w;j++)
			for(int k=0;j+k<=w;k++)
				chkmax(tmp[j+k],f[x][d][j]+max(f[y][d+1][k],f[y][0][k]+(d+1)*sum[y]));
			memcpy(f[x][d],tmp,sizeof(tmp));
		}
		// for(int j=0;j<=w;j++)
		// 	if(f[x][d][j]>=0)cout<<x<<","<<d<<","<<j<<" f="<<f[x][d][j]<<endl;
	}
}
void procedure(){
	n=read(),w=read();
	int ans=0,red=0;
	for(int i=1,m;i<=n;i++){
		scanf("%s",s),m=read();
		ans+=strlen(s)*m,ins(m);
	}
	// cout<<"ans="<<ans<<endl;
	dfs(1);
	for(int i=0;i<=w;i++)chkmax(red,f[1][0][i]);
	printf("%d\n", ans-red);
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