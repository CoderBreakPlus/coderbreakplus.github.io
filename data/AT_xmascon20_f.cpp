// created time: 2026-05-21 18:14:31
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

int n,v,b[35];

int dp[2][35][35][35][1205],ans[35],pw[35];
void procedure(){
	n=read(),v=read();
	pw[0]=1;
	for(int i=1;i<=n;i++)pw[i]=(ull)pw[i-1]*v%mod;
	for(int i=1;i<=n;i++)b[i]=read();b[n+1]=1e5;
	dp[0][0][0][v+1][0]=1;
	sort(b+1,b+n+1);

	// 先写出 O(nlogn) 的单组算答案，对着它计数

	// 细节：相同的数，认为靠后的数字更大
	// 计数维护 pq 的 trick
	
	// f[i][j][l][r][s] 前 i 个数，一共钦定了 j 个数弹掉
	// l 是未弹掉的数中，钦定弹掉的最大的，r 是现在钦定不弹的最小数字，s 是当前答案
	// 当 s<=b[i]，必然是所有该弹的都弹了，不该弹的被砍，l->0, r->r-b[i]+s, s->b[i]
	// 当 s>b[i]，必然是有该弹的还没弹。
	//    如果动摇了 l，则把 l 砍到对应位置。否则 l 不动。

	for(int i=1,o=1;i<=n+1;i++,o^=1){
		for(int j=0;j<i;j++)
		for(int l=0;l<=v;l++)for(int r=0;r<=v+1;r++)
		for(int s=0;s<=1200;s++){
			int w=dp[o^1][j][l][r][s];
			if(!w)continue;dp[o^1][j][l][r][s]=0;

			int sp=max(s,b[i]),lp=min(l,sp-b[i]),rp=(r==v+1)?r:r-sp+s;
			if(s!=b[i-1]&&sp==b[i])
				ans[j]=(ans[j]+(ull)w*s%mod*pw[n-i+1])%mod;

			if(rp<=0)continue;
			for(int t=1;t<=v;t++){
				if(t>=lp){
					addmod(dp[o][j][lp][min(rp,t)][sp]+=w);
				}
				if(t<rp) addmod(dp[o][j+1][max(lp,t)][rp][sp+t]+=w);
			}
		}
	}
	for(int i=1;i<=n;i++)printf("%d ",ans[i]);
	puts("");
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