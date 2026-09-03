// created time: 2026-09-03 08:27:40
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
const int dx[4]={1,-1,0,0};
const int dy[4]={0,0,1,-1};

int n,m,q,a[5005][5005],ans[5005][5005];
pair<int,int> ord[5005*5005];

void procedure(){
	n=read(),m=read(),q=read();
	for(int i=1;i<=n;i++)
		for(int j=1;j<=m;j++)a[i][j]=read(), ord[(i-1)*m+j]={i,j};
	
	sort(ord+1,ord+n*m+1,[&](pair<int,int> A,pair<int,int> B){
		auto [i,j]=A;
		auto [k,l]=B;
		return a[i][j]>a[k][l];
	});

	for(int s=1;s<=n*m;s++){
		auto [i,j]=ord[s];

		ans[i][j]=0;
		for(int d=0;d<4;d++){
			int x=i+dx[d],y=j+dy[d];
			if(x>n||y>m||x<1||y<1)continue;
			if(a[x][y]<a[i][j])continue;
			ans[i][j]|=(!ans[x][y]);
		}
	}

	while(q--){
		int x=read(),y=read();
		printf("%d\n",ans[x][y]);
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