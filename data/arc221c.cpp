// created time: 2026-06-23 17:29:26
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

int n,a[300005];
int mx1[300005],mn1[300005];
int mx2[300005],mn2[300005],dp[300005];

bool check(int i,int j,int v){
	int L=min(mn1[i-1],mn2[j+1]),R=max(mx1[i-1],mx2[j+1]);
	return (a[v]<L)||(R<a[v]);
}

int smx[300005],smn[300005],tmx,tmn,cur,pmx[300005],pmn[300005],pd[300005];
int cnt[300005];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=mx1[i]=mx2[i]=mn1[i]=mn2[i]=read();
	mx1[0]=-1e9,mn1[0]=1e9;
	mx2[n+1]=-1e9,mn2[n+1]=1e9;
	for(int i=1;i<=n;i++)chkmax(mx1[i],mx1[i-1]),chkmin(mn1[i],mn1[i-1]);
	for(int i=n;i>=1;i--)chkmax(mx2[i],mx2[i+1]),chkmin(mn2[i],mn2[i+1]);

	cur=1; tmx=tmn=0;
	for(int i=0;i<=n+1;i++)pmx[i]=pmn[i]=dp[i]=pd[i]=cnt[i]=0;
	for(int i=1;i<=n;i++){
		while(tmx && a[smx[tmx]]<=a[i]){
			int v=smx[tmx--];
			if(!--cnt[v]) chkmax(cur,v+1);
		}
		while(tmn && a[smn[tmn]]>=a[i]){
			int v=smn[tmn--];
			if(!--cnt[v]) chkmax(cur,v+1);
		}
		pmx[i]=smx[tmx];
		pmn[i]=smn[tmn];

		smx[++tmx]=i; smn[++tmn]=i; cnt[i]=2;
		pd[i]=cur;
	}
	int ans=0;
	dp[0]=n;
	for(int i=1;i<=n;i++){
		int ok=-1;
		if(i==1)ok=n;
		else{
			int L=dp[i-1],R=n;
			while(L<=R){
				int j=(L+R)>>1;
				if(check(i-1,j,i-1)) ok=j,R=j-1;
				else L=j+1; 
			}
		}
		if(!(~ok))break;
		dp[i]=ok;


		int j=dp[i];
		int L=min(mn1[i-1],mn2[j+1]),R=max(mx1[i-1],mx2[j+1]);
		if(a[j]<L || R<a[j]){
			// int act=dp[i];
			// while(act>=i && check(i,act,act)) act--;

			dp[i]--;

			bool f1=(pmx[j] && a[j]<L && R<a[pmx[j]]);
			bool f2=(pmn[j] && a[pmn[j]]<L && R<a[j]);

			if(f1||f2) dp[i]=pd[j]-1;
			else{
				if(a[j]<L) dp[i]=max(pd[j]-1,pmx[j]);
				else dp[i]=max(pd[j]-1,pmn[j]);
			}

			// assert(dp[i]==act);
			// if(dp[i]!=act){
			// 	cout<<"at "<<i<<" from "<<j<<" to "<<dp[i]<<" or "<<act<<endl;
			// 	exit(0);
			// }
			// dp[i]=act;
		}
		chkmax(ans,i-1+n-dp[i]);
	}
	printf("%d\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}