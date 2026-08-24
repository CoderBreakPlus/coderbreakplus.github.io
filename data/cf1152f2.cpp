// created time: 2026-08-24 15:16:52
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
const int N = 500000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

int n,K,m,a[105],s[105];
int f[15][8][50],g[15][50],dp[15][15][50];

inline void upd(int &a,ull b){ a=(a+b)%mod; }

int mp[1<<21];
int S[30005][15],cnt[30005],tt;
void procedure(){
	n=read(),K=read(),m=read();

	for(int k=2;k<=K;k++)
	{
		for(int i=0;i<k;i++)a[i]=i;

		auto gethash = [&](int *seq){
			int ret=0;
			for(int i=1;i<k;i++)ret=ret*4+seq[i]-1;
			return ret;
		};
		do{
			bool flg=1;
			for(int i=1;i<k;i++)
				if(a[i-1]-a[i]>m){flg=0;break;}
			if(!flg)continue;

			for(int i=0;i<k;i++)s[i]=i;
			for(int i=1;i<k;i++)
				if(a[i]<a[i-1]) s[a[i-1]]=a[i];

			for(int i=k-2;i>=0;i--)chkmin(s[i],s[i+1]);

			for(int i=1;i<k;i++){
				s[i]=i-s[i];
				if(!s[i])flg=0;
			}
			if(!flg)continue;

			int tmp = gethash(s);
			if(!mp[tmp]){
				mp[tmp]=++tt,cnt[tt]=1;
				memcpy(S[tt],s,sizeof(s));
			}else cnt[mp[tmp]]++;

		}while(next_permutation(a,a+k));

		for(int p=1;p<=tt;p++){
			int *s=S[p];
			memset(f,0,sizeof(f));
			f[0][0][0]=cnt[p];
			for(int i=1;i<k;i++)
				for(int j=0;j<(1<<m-1);j++){
					int cur=j|(1<<m-1);
					for(int d=1;d<=m;d++){
						if(__builtin_popcount(cur>>d-1)>=s[i]){
							for(int w=0;w<=3*(i-1);w++)
								addmod(f[i][cur>>d][w+d-1]+=f[i-1][j][w]);
						}else break;
					}
				}
			for(int j=0;j<(1<<m-1);j++)
				for(int w=0;w<=3*(k-1);w++)
					addmod(g[k][w]+=f[k-1][j][w]);
		}

		for(int i=1;i<=tt;i++) cnt[i]=0;
		tt=0;
		memset(mp,0,sizeof(mp));
	}
	g[1][0]=1;
	for(int i=1;i<=K;i++)
		for(int j=0;j<=3*(i-1);j++){
			if(!g[i][j])continue;
		}

	dp[0][0][0]=1;
	for(int i=0;i<K;i++)
		for(int j=0;j<=i;j++)for(int w=0;w<=3*(i-j);w++)if(dp[i][j][w])
			for(int ii=1;i+ii<=K;ii++)
			for(int ww=0;ww<=3*(ii-1);ww++)
				upd(dp[i+ii][j+1][w+ww],(ull)dp[i][j][w]*g[ii][ww]);

	int ans=0;
	for(int j=1,res;j<=K;j++)for(int w=0;w<=3*(K-j);w++)if((res=n-K-w)>=0){
		int now=(ull)dp[K][j][w]*inv[j]%mod; // * C(res+j,j)
		for(int i=1;i<=j;i++) now=(ull)now*(res+i)%mod;
		addmod(ans+=now);
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	math_init();
	while(T--) procedure();
	return 0;
}