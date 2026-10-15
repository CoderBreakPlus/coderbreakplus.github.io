// created time: 2026-10-14 10:15:53
#pragma GCC optimize(3,"inline")
#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx,avx2")
#include<bits/stdc++.h>
#include<gmpxx.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353;
#define u128 __uint128_t

inline u128 read(){
	u128 x=0, f=1; int ch=getchar();
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
const int N = 10000, B = 625;
int n,m,bl[10005],lf[10005],rh[10005],vis[10000005];
u128 a[N+5];
mpz_class sum[N/B+5];

int buc1[205],pw1[205],buc2[205],pw2[205],c[10000005];

inline mpz_class tompz(__uint128_t x){
	mpz_class res=(unsigned long)(x>>64);
	res<<=64;
	res+=(unsigned long)(uint64_t)x;
	return res;
}

int seq[1000005],tl;
void procedure(){
	n=read(),m=read();
	for(int i=2;i<=m;i++)if(!vis[i])
		for(int j=2*i;j<=m;j+=i) vis[j]=1;

	for(int i=1;i<=n;i++)a[i]=read(),bl[i]=(i-1)/B+1,rh[bl[i]]=i;
	for(int i=n;i>=1;i--)lf[bl[i]]=i;
	for(int i=1;i<=bl[n];i++) sum[i]=1;

	for(int i=1;i<=n;i++)sum[bl[i]]*=tompz(a[i]);

	for(int i=2;i<=m;i++) if(!vis[i])seq[++tl]=i;

	ull ans=0;
	for(int x=1;x<=tl;x+=2){
		int i=seq[x],j=1;
		pw1[1]=i,buc1[1]=0;
		int to1=1,to2;
		for(int k=2;;k++){
			if((ll)pw1[k-1]*i>m) break;
			pw1[k]=pw1[k-1]*i,to1=k;
			buc1[k]=0;
		}
		if(x<tl){
			j=seq[x+1];
			pw2[1]=j,buc2[1]=0;
			to2=1;
			for(int k=2;;k++){
				if((ll)pw2[k-1]*j>m) break;
				pw2[k]=pw2[k-1]*j,to2=k;
				buc2[k]=0;
			}
		}
		ll v=(ll)i*j;
		for(int w=1;w<=bl[n];w++){
			ll fuck=mpz_fdiv_ui(sum[w].get_mpz_t(),(unsigned long)v);
			if(fuck%i==0){
				for(int k=lf[w];k<=rh[w];k++){
					int cnt=0;
					while(a[k]%i==0)cnt++,a[k]/=i;
					buc1[min(to1,cnt)]++;
				}
			}
			if(j>1&&fuck%j==0){
				for(int k=lf[w];k<=rh[w];k++){
					int cnt=0;
					while(a[k]%j==0)cnt++,a[k]/=j;
					buc2[min(to2,cnt)]++;
				}
			}
		}
		for(int k=to1-1;k>=1;k--)buc1[k]+=buc1[k+1];
		for(int k=1;k<=to1;k++)
			c[pw1[k]]+=buc1[k];

		if(j>1){
			for(int k=to2-1;k>=1;k--)buc2[k]+=buc2[k+1];
			for(int k=1;k<=to2;k++)
				c[pw2[k]]+=buc2[k];
		}
	}
	for(int i=1;i<=m;i++)ans=ans*1000000007+(c[i]+1);
	printf("%llu\n",ans);
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