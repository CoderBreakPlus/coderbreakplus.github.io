// created time: 2026-11-02 09:50:00
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

ll n,a[1005][1005],sum[1005],deg[1005],ans[1005][1005],tmp[1005],deg2[1005];

void procedure(){
	n=read();
	for(ll i=1;i<=n;i++)sum[i]=0;
	ll mx=0;
	for(ll i=1;i<=n;i++)
		for(ll j=1;j<=n;j++)	
			chkmax(mx,a[i][j]=read());

	if(n<=5){
		for(ll i=0;i<(1<<n*(n-1)/2);i++){
			ll k=0,m=0;
			memset(deg,0,sizeof(deg));
			for(ll x=1;x<=n;x++)
				for(ll y=x+1;y<=n;y++)if((i>>k++)&1){
					ans[x][y]=ans[y][x]=1;
					deg[x]++,deg[y]++,m++;
				}else
					ans[x][y]=ans[y][x]=0;
			bool flg=1;
			for(ll x=2;flg&&x<=n;x++)
				for(ll y=x+1;flg&&y<=n;y++)
					flg&=(a[x][y]==m-deg[x]-deg[y]+ans[x][y]);
			if(flg){
				for(ll i=1;i<=n;i++){
					for(ll j=1;j<=n;j++)printf("%d ",ans[i][j]);
					puts("");
				}
				return;
			}
		}
		assert(0);
	}
	for(ll i=2;i<=n;i++)
		for(ll j=2;j<=n;j++)if(i!=j)sum[i]+=a[i][j];
	for(ll m=mx;;m++){
		memset(deg,-1,sizeof(deg));
		memset(deg2,0,sizeof(deg2));
		auto add=[&](ll x,ll y,ll v){
			ans[x][y]=ans[y][x]=v;
			deg2[x]+=v,deg2[y]+=v;
		};
		ll love=0;
		for(ll i=2;i<=n;i++){
			love+=(tmp[i]=(ll)m*(n-4)-sum[i]);
		}

		ll sb=(ll)(n-4)*(2*m);
		if((sb-love)%(2*n-6))continue;

		deg[1]=(sb-love)/(2*n-6);
		bool flg=(0<=deg[1]&&deg[1]<n);
		for(ll i=2;flg&&i<=n;i++){
			tmp[i]+=deg[1];
			if(tmp[i]>=0&&tmp[i]%(n-4)<=1) add(1,i,tmp[i]%(n-4)),deg[i]=tmp[i]/(n-4);
			else flg=0;
			flg&=(0<=deg[i]&&deg[i]<n);
		}
		if(!flg)continue;
		for(ll i=2;flg&&i<=n;i++)
			for(ll j=i+1;flg&&j<=n;j++){
				ll dc=deg[i]+deg[j]-(m-a[i][j]);
				if(0<=dc&&dc<=1){
					add(i,j,dc);
				}else flg=0;
			}
		for(ll i=1;i<=n;i++)flg&=(deg2[i]==deg[i]);
		if(flg){
			for(ll i=1;i<=n;i++){
				for(ll j=1;j<=n;j++)printf("%lld ",ans[i][j]);
				puts("");
			}
			return;
		}
	}
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