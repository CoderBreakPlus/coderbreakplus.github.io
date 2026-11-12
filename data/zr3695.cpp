// created time: 2026-11-10 08:05:22
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
const int Z=26,i2=INV(2),i12=INV(12),i8=INV(8),i6=INV(6);
int n;
char t[200005];
int son[200005][Z],sz[200005],id[200005],ans[200005],cnt=1;

int c[Z][Z],deg1[Z],deg2[Z];

int calc(bool out=0){
	int e1=0,e2=0,sum=0;
	for(int i=0;i<Z;i++)deg1[i]=deg2[i]=0;
	for(int i=0;i<Z;i++)
		for(int j=0;j<Z;j++){
			e1+=c[i][j];
			deg1[i]+=c[i][j];
			deg2[j]+=c[i][j];
			e2=(e2+(ull)(c[i][j]-1)*c[i][j]/2)%mod;
		}
	sum=e1;
	e1=(ull)e1*i2%mod;
	e2=(ull)e2*i2%mod;

	int s=0;
	for(int i=0;i<Z;i++)
		for(int j=0;j<Z;j++)if(i!=j){
			int now=sum-deg1[i]-deg1[j]-deg2[i]-deg2[j]+c[i][j]+c[j][i];
			s=(s+(ull)c[i][j]*now)%mod;
		}
	e2=(e2+(ull)s*i8)%mod;
	s=0;
	for(int i=0;i<Z;i++){
		s=(s+((ull)deg1[i]*deg1[i]+(ull)deg2[i]*deg2[i]))%mod;
		for(int j=0;j<Z;j++)
			s=(s+((ull)(mod-c[i][j])*c[i][j]+(ull)(mod-c[j][i])*c[j][i]))%mod;
		s=(s+(ull)deg1[i]*deg2[i])%mod;
		for(int j=0;j<Z;j++)
			s=(s+(ull)(mod-c[i][j])*c[j][i])%mod;
	}
	e2=(e2+(ull)s*i6)%mod;
	e2=(2ull*e2+e1)%mod;
	return (e2+(ull)(mod-e1)*e1)%mod;
}
void dfs(int x){
	if(id[x]){
		ans[id[x]]=calc(id[x]==1);
	}
	for(int i=0;i<Z;i++)if(son[x][i]){
		for(int j=0;j<Z;j++)if(son[x][j]&&i!=j)c[j][i]+=sz[son[x][j]];
		dfs(son[x][i]);
		for(int j=0;j<Z;j++)if(son[x][j]&&i!=j)c[j][i]-=sz[son[x][j]];
	}3
}
void procedure(){
	n=read();
	for(int i=1;i<=n;i++){
		scanf("%s",t+1);
		int len=strlen(t+1),rt=1;
		for(int j=1;j<=len;j++){
			int o=t[j]-'a';
			if(!son[rt][o])son[rt][o]=++cnt;
			rt=son[rt][o],sz[rt]++;
		}
		id[rt]=i;
	}
	dfs(1);
	for(int i=1;i<=n;i++)printf("%d\n",ans[i]);
}
int main(){
	assert(freopen("alphabet.in","r",stdin));
	assert(freopen("alphabet.out","w",stdout));
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}