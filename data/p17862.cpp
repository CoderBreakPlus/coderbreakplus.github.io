// created time: 2026-11-09 13:51:20
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int n,m,k,mod;
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
struct Barrett {
	using u32 = uint32_t;
	using u64 = uint64_t;
	using u128 = __uint128_t;
	u32 mod; u64 inv;
	explicit Barrett(u32 p) : mod(p), inv(UINT64_MAX / p) {}
	inline u32 reduce(u64 x) const {
		u64 q = (u128)x * inv >> 64;
		u64 r = x - q * mod;
		return r >= mod ? r - mod : r;
	}
	inline u32 mul(u32 a, u32 b) const {
		return reduce((u64)a * b);
	}
}node(998244353);
const int N=805;
int inv[N],C[N][N];
pair<int,int> pairs[N];
inline void add(int &a,ull b){ a=node.reduce(a+b); }
void poly_exp(int *A,int *b,int n){
	int a[N];
	copy(A,A+n+1,a);
	b[0]=1;
	for(int i=1;i<=n;i++){
		__uint128_t now=0;
		for(int j=1;j<=i;j++)
			now+=(ull)node.mul(C[i-1][j-1],a[j])*b[i-j];
		b[i]=now%mod;
	}
}
void poly_ln(int *A,int *b,int n){
	int a[N];
	copy(A,A+n+1,a);
	b[0]=0;
	for(int i=1;i<=n;i++){
		__uint128_t now=a[i];
		for(int j=1;j<i;j++)
			now+=(ull)node.mul(mod-C[i-1][j-1],b[j])*a[i-j];
		b[i]=now%mod;
	}
}
void poly_mul(int *a,int *b,int *c,int n){
	for(int i=n;i>=0;i--){
		__uint128_t s=0;
		for(int j=0;j<=i;j++)
			s+=(ull)node.mul(C[i][j],a[j])*b[i-j];
		c[i]=s%mod;
	}
}
int c[N],cf[5][N],pcf[5][10][N],cur[N],fa[20],fac[N];
inline int find(int x){ if(x!=fa[x])fa[x]=find(fa[x]);return fa[x]; }

map<array<int,5>,int>mp;

int calc(array<int,5> a){
	if(mp.count(a))return mp[a];
	memset(cur,0,sizeof(cur));
	cur[0]=1;
	for(int j=0;j<=k;j++)
		poly_mul(cur,pcf[j][a[j]],cur,m);
	return mp[a]=cur[m];
}
int ff[1<<6][1<<4][4],fg[1<<4][20],cnt[1<<4];
void procedure(){
	n=read(),m=read(),mod=read();
	node=Barrett(mod);
	if(mod==1){puts("0");return;}
	for(int i=0;i<=m;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			addmod(C[i][j]=C[i-1][j-1]+C[i-1][j]);
	}
	c[0]=1;
	for(int i=1;i<=m;i++)
		c[i]=qpow(2,i-1)*c[i-1]%mod;
	poly_ln(c,c,m);

	k=n-m;
	int e=0;
	for(int x=0;x<k;x++)
		for(int y=x+1;y<k;y++)
			pairs[e++]={x,y};
	for(int i=0;i<=k;i++){
		for(int j=1;j<=m;j++)
			cf[i][j]=(ull)c[j]*qpow(qpow(2,j)+mod-1,i)%mod;
		poly_exp(cf[i],cf[i],m);
		cf[i][0]=0;

		pcf[i][0][0]=1;
		for(int t=1;t<=6;t++)
			poly_mul(pcf[i][t-1],cf[i],pcf[i][t],m);
	}
	int ans=0;
	int shabi=0;

	vector<int>ord;
	for(int t=1;t<(1<<k);t++)ord.pb(t);
	sort(ord.begin(),ord.end(),[](int x,int y){ return __builtin_popcount(x)<__builtin_popcount(y); });
	
	for(int s=0;s<(1<<e);s++){
		for(int t:ord){
			int now=0;
			for(int i=0;i<k;i++)fa[i]=i;
			for(int x=0;x<k;x++)
				for(int y=x+1;y<k;y++)if(s>>now++&(t>>x)&(t>>y)&1)
					fa[find(x)]=find(y);
			for(int i=0;i<k;i++)ff[s][t][i]=fa[i];
		}
	}
	for(int i=0;i<(1<<(1<<k));i+=2){
		array<int,5>buc={0,0,0,0,0};
		for(int j=0;j<(1<<k);j++)
			if((i>>j)&1)buc[__builtin_popcount(j)]++;
		int val=calc(buc);

		for(int t:ord){
			int cnt=k;
			for(int x=0;x<k;x++)fa[x]=x;
			int fuck=i;
			while(fuck){
				int j=__builtin_ctz(fuck);
				fa[cnt]=cnt;
				int damn=j&t;
				while(damn){
					int w=__builtin_ctz(damn);
					fa[find(w)]=find(cnt);
					damn^=(1<<w);
				}
				++cnt;
				fuck^=(1<<j);
			}
			for(int x=0;x<cnt;x++)fg[t][x]=fa[x];
			::cnt[t]=cnt;
		}
		for(int s=0;s<(1<<e);s++){
			int tmp=0;
			for(int t:ord){
				int cnt=::cnt[t];
				for(int x=0;x<cnt;x++)fa[x]=fg[t][x];
				for(int x=0;x<k;x++) fa[find(ff[s][t][x])]=find(x);
				bool flg=1;
				int tt=__builtin_ctz(t);
				for(int i=0;i<cnt;i++)
					if(i>=k||(t>>i&1))flg&=(find(i)==find(tt));
				if(flg){
					tmp=__builtin_popcount(t);
					break;
				}
			}
			if(tmp)add(ans,(ull)val*(m-1+tmp));
		}
	}
	int side1=(ull)c[m]*qpow(2,k*(k-1)/2)%mod;
	int side2=(mod+m-qpow(2,m*k))%mod;
	add(ans,(ull)side1*side2);

	printf("%d\n",ans);
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