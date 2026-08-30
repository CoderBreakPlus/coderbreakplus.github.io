// created time: 2026-02-28
#pragma GCC optimize("Ofast,no-stack-protector,unroll-loops,fast-math")
#pragma GCC target("sse,sse2,sse3,sse4,popcnt,abm,mmx,avx,avx2")
#pragma GCC optimize(3,"Ofast","inline")
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> P;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
const int mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
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
inline ll INV(ll x){ return qpow(x, mod-2); };

int n,m;

int pos[505],l[505][505],r[505][505],C[505][505];
int f[505][505][505], g[505];

inline void add(int &a, ull b){ a=(a+b)%mod; }

ull tmp[505];
const ull V=16ull*mod*mod;
void procedure(){
	n=read(),m=read();

	for(int i=0;i<=n;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			addmod(C[i][j]=C[i-1][j]+C[i-1][j-1]);
	}
	for(int i=1;i<=m;i++){
		int x=read(),y=read();
		pos[x]=y;
	}
	g[0]=1;
	for(int i=1;i<=n;i++)
		for(int j=0;j<i;j++) add(g[i],1ull*g[j]*g[i-j-1]%mod);

	for(int x=1;x<=n;x++){
		int mn=1e9, mx=-1e9;
		for(int y=x;y<=n;y++){
			if(pos[y]){
				mn=min(mn,pos[y]);
				mx=max(mx,pos[y]);
			}
			l[x][y]=mn, r[x][y]=mx;
		}
	}

	for(int x=1;x<=n+1;x++)
		for(int z=0;z<=n+1;z++) f[x][x-1][z]=1;
	for(int x=n;x>=1;x--)
		for(int y=x;y<=n;y++){
			int len=y-x+1;
			int L=max(1,r[x][y]-len+1),R=min(n-len+1,l[x][y]);

			memset(tmp,0,sizeof(tmp));

			if(l[x][y]>r[x][y]){
				for(int z=L;z<=R;z++) f[x][y][z]=g[len];
			}else{
				if(pos[x]){
					int p=pos[x];
					for(int z=L;z<=R;z++){
						add(f[x][y][z],1ull*f[x+1][x+p-z][z]*f[x+p-z+1][y][p+1]%mod);
					}
				}else{
					for(int t=0;t<len;t++){
						int *F=f[x+1][x+t], *G=f[x+t+1][y];
						for(int z=L;z<=R;z++){
							tmp[z]+=1ull*F[z]*G[z+t+1];
						}
						if(!(t&15))
							for(int z=L;z<=R;z++) tmp[z]%=mod;
					}
					for(int z=L;z<=R;z++) f[x][y][z]=tmp[z]%mod;
				}
			}
		}

	printf("%d\n", f[1][n][1]);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}