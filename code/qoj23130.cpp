// created time: 2026-10-08 12:57:58
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

int n,d;
int E[2005][2005],ans[2005][2005],hd[2005];
int seq[4000005],tl;
void dfs(int x){
	while(hd[x]<n){
		int y=++hd[x];
		if(E[x][y]||x==y)continue;
		E[x][y]=E[y][x]=1;
		dfs(y);
	}
	seq[++tl]=x;
}
void procedure(){
	n=read(),d=read();
	for(int i=1;i<=n;i++){
		hd[i]=0;
		for(int j=1;j<=n;j++)E[i][j]=ans[i][j]=0;
	}
	if(n&1){
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++) putchar('0'+(j-i<=n/2));
		puts("");
	}else{
		if((~d&1) || d>n/2){
			puts("NO");
			return;
		}
		int N=n/2;
		for(int i=1;i<=n;i++)hd[i]=0;
		for(int i=1;i<=N;i++){
			for(int j=i;j<i+d;j++){
				int t=(j-1)%N+1+N;
				ans[i][t]=1;
				E[i][t]=E[t][i]=1;
			}
		}
		tl=0;
		dfs(1);
		// for(int i=1;i<=tl;i++) cout<<seq[i]<<" "; cout<<endl;
		for(int i=2;i<=tl;i++){
			ans[seq[i-1]][seq[i]]=1;
		}
		if(d==N){
			tl=0;
			dfs(N+1);
			for(int i=2;i<=tl;i++){
				ans[seq[i-1]][seq[i]]=1;
			}	
		}
		for(int i=1;i<=n;i++)
			for(int j=i+1;j<=n;j++){
				// if(ans[i][j]) cout<<i<<"->"<<j<<endl;
				putchar(ans[i][j]+'0');
			}
		puts("");
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