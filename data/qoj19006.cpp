// created time: 2026-09-03 10:29:19
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
const int dx[4]={0,0,1,-1};
const int dy[4]={1,-1,0,0};
int n,m,a[505][505],cur[505][505],cnt[505][505];

void procedure(){
	n=read(),m=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[i][j]=read();

	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)
			for(int k:{0,1,2,3}){
				int x=i+dx[k],y=j+dy[k];
				if(x>n||y>m||x<1||y<1)continue;
				cnt[x][y]++;
			}

	int ans=0;
	while(1){
		bool flg=0;
		for(int i=1;i<=n;i++)
			for(int j=1;j<=m;j++){
				if(cur[i][j]<a[i][j]){
					flg=1;
					int d=a[i][j]-cur[i][j];
					int opt=(d+cnt[i][j])/(1+cnt[i][j]);

					ans += opt;
					// cout<<"opt "<<i<<","<<j<<" = "<<opt<<endl;
					cur[i][j]+=opt*(1+cnt[i][j]);
					for(int k:{0,1,2,3}){
						int x=i+dx[k],y=j+dy[k];
						cur[x][y]-=opt;
					}
				}
			}
		// for(int i=1;i<=n;i++){
		// 	for(int j=1;j<=m;j++) cout<<cur[i][j]<<" "; cout<<endl;
		// }
		if(!flg)break;
	}
	printf("%d\n", ans);
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