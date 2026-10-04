// created time: 2026-10-04 08:22:57
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
int n,a[1005],q,l[100005],r[100005],x[100005];
int f[4][1005][1005],pw[100005],ans;
void procedure(){
	n=read();
	for(int i=1;i<=n;i++)a[i]=read();
	q=read();
	for(int i=1;i<=q;i++){
		l[i]=read(),r[i]=read(),x[i]=read();
	}
	pw[0]=1;
	for(int i=1;i<=q+1;i++)addmod(pw[i]=2*pw[i-1]);

	for(int i=0;i<7;i++)for(int j=0;j<7;j++){
		memset(f,0,sizeof(f));
		for(int o=1;o<=q;o++){
			// 00
			int s00=0;
			f[s00][1][n]++;
			f[s00][1][r[o]]--;
			f[s00][l[o]][n]--;
			f[s00][l[o]][r[o]]++;
			f[s00][1][l[o]-1]++;
			f[s00][r[o]+1][n]++;
			// 10
			int s10=((x[o]>>j)&1)<<1;
			f[s10][1][r[o]]++;
			f[s10][1][l[o]-1]--;
			f[s10][l[o]][r[o]]--;
			// 01
			int s01=(x[o]>>i)&1;
			f[s01][l[o]][n]++;
			f[s01][r[o]+1][n]--;
			f[s01][l[o]][r[o]]--;
			// 11
			int s11=s10|s01;
			f[s11][l[o]][r[o]]++;
		}
		for(int v=0;v<4;v++){
			for(int l=1;l<=n;l++)
				for(int r=1;r<=n;r++)f[v][l][r]+=f[v][l-1][r];
			for(int l=1;l<=n;l++)
				for(int r=n;r>=1;r--)f[v][l][r]+=f[v][l][r+1];
		}

		for(int l=1;l<=n;l++)
			for(int r=l;r<=n;r++){
				int b0=(a[l]>>i)&1;
				int b1=(a[r]>>j)&1;
				int cf=(ull)(1<<i+j)*l%mod*(n-r+1)%mod*(1+(l!=r))%mod;

				int count=f[0][l][r]+max(0,f[1][l][r]-1)+max(0,f[2][l][r]-1)+f[3][l][r];

				int ban[2]={0,0};
				if(!f[1][l][r]) ban[b0]=1;
				if(!f[2][l][r]) ban[b1]=1;
				if(ban[0]&&ban[1])continue;
				if(!f[3][l][r]){
					if(!ban[0]){
						ans=(ans+(ull)cf*pw[count])%mod;
					}
					continue;
				}
				if(ban[0]||ban[1])count--;
				ans=(ans+(ull)cf*pw[count])%mod;
			}
	}
	printf("%d\n",ans);
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