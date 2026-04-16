// created time: 2026-04-16 10:21:51
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
inline void addmod(int &x){ if(x >= mod) x -= mod; }
inline void addmod(ll &x){ if(x >= mod) x -= mod; }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
inline ll INV(ll x){ return qpow(x, mod-2); }

int n,c,a[3005],f[3005][3005],pw[3005];
int dp[3005][3005],dp2[3005][3005],buc[3005],go[3005];

struct Seg{
	int val[12005];
	void pushup(int p){
		val[p]=(ull)val[p<<1]*val[p<<1|1]%mod;
	}
	void build(int l,int r,int p){
		val[p]=0;if(l==r) return;
		int mid=(l+r)>>1;
		build(l,mid,p<<1),build(mid+1,r,p<<1|1);
	}
	void update(int l,int r,int x,int v,int p){
		if(l==r){
			val[p]=pw[v]-1;
			return;
		}
		int mid=(l+r)>>1;
		if(x<=mid) update(l,mid,x,v,p<<1);
		else update(mid+1,r,x,v,p<<1|1);
		pushup(p);
	}
}S;
void procedure(){
	n=read(),c=read();
	for(int i=1;i<=n;i++)a[i]=read();
	pw[0]=1;
	for(int i=1;i<=n;i++)addmod(pw[i]=2*pw[i-1]);
	go[n+1]=1;
	for(int l=1;l<=n;l++){
		memset(buc,0,sizeof(buc));
		S.build(1,c,1);
		for(int r=l;r<=n;r++){
			S.update(1,c,a[r],1,1);
			f[l][r]=S.val[1];
			S.update(1,c,a[r],++buc[a[r]],1);
		}
		int sb=1;
		for(int i=1;i<=c;i++) sb=(ull)sb*(pw[buc[i]]-1)%mod;
		addmod(go[l]=pw[n-l+1]+mod-sb);
	}

	if(c >= 12){
		dp[0][0]=1;
		for(int i=0;i<n;i++)
			for(int j=0;j<=i/c;j++)
				for(int k=i+1;k<=n;k++)
					dp[k][j+1]=(dp[k][j+1]+(ull)dp[i][j]*f[i+1][k])%mod;
		for(int i=0;i<=n;i++){
			int ans=0;
			if(!i) ans=mod-1;
			for(int j=0;j<=n;j++)ans=(ans+(ull)go[j+1]*dp[j][i])%mod;
			printf("%d ",ans);
		}
		puts("");
	}else{
		dp[0][0]=1;
		for(int i=0;i<n;i++){
			for(int j=0;j<=(i+1)/c;j++)
				for(int k=0;k+1<(1<<c);k++)dp2[j][k]=0;
			for(int j=0;j<=i/c;j++)
				for(int k=0;k+1<(1<<c);k++){
					addmod(dp2[j][k]+=dp[j][k]);
					int kk=(k|(1<<a[i+1]-1));
					if(kk==(1<<c)-1) addmod(dp2[j+1][0]+=dp[j][k]);
					else addmod(dp2[j][kk]+=dp[j][k]);
				}
			for(int j=0;j<=(i+1)/c;j++)
				for(int k=0;k+1<(1<<c);k++)dp[j][k]=dp2[j][k];
		}
		for(int j=0;j<=n;j++){
			int ans=0;
			if(!j) ans=mod-1;
			for(int k=0;k+1<(1<<c);k++) addmod(ans+=dp[j][k]);
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