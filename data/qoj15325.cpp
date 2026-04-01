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
const ll mod = 998244353;
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

int n,a[505],f[505][505],fh[505][505],ff[505][505],h[505][505],g[2][505][505],gl[2][505][505],gr[2][505][505];

int mn[505][505],mx[505][505],mn2[505][505],mx2[505][505],pos[505];

void procedure(){
	n=read();
	for(int i=1;i<=n;i++) a[i]=read(),pos[a[i]]=i;

	for(int i=1;i<=n;i++){
		set<int>s={a[i]};
		set<int,greater<int>>t={a[i]};
		mn[i][i]=mx[i][i]=a[i];
		for(int j=i+1;j<=n;j++){
			s.emplace(a[j]),t.emplace(a[j]);
			mn[i][j]=*s.begin(), mn2[i][j]=*next(s.begin());
			mx[i][j]=*t.begin(), mx2[i][j]=*next(t.begin());
		}
	}
	// h: ways to move
	for(int i=1;i<=n;i++) g[0][i][i]=g[1][i][i]=gr[0][i][i]=gr[1][i][i]=gl[0][i][i]=gl[1][i][i]=1;
	for(int x=2;x<=n;x++)
		for(int l=1,r=x;r<=n;l++,r++){
			{
				bool o=0;
				int v1=pos[mn[l][r]], v2=pos[mx[l][r]]; if(v1>v2) swap(v1,v2),o^=1;

				for(int p=v1;p<v2;p++)
					ff[l][r]=(ff[l][r]+1ull*g[o][l][p]*gr[o^1][p+1][r])%mod;

				f[l][r]=ff[l][r];
				for(int p=l;p<r;p++)
					f[l][r]=(f[l][r]+1ull*ff[l][p]*fh[p+1][r])%mod;
				h[l][r]=(0LL+f[l][r]+h[l][r-1]+h[l+1][r]-h[l+1][r-1]+mod)%mod;

				addmod(fh[l][r]=f[l][r]+fh[l+1][r]);
			}

			{
				bool o=0;
				int v1=pos[mn2[l][r]], v2=pos[mn[l][r]]; if(v1>v2) swap(v1,v2),o^=1;
				// calc g

				if(!o){
					for(int q=v1+1;q<=v2;q++)
						g[0][l][r]=(g[0][l][r]+1ull*gl[0][l][q-1]*(ff[q][r]+(q==r)))%mod;
				}else{
					for(int p=v1;p<v2;p++)
						g[0][l][r]=(g[0][l][r]+1ull*(ff[l][p]+(l==p))*gr[0][p+1][r])%mod;
				}
				for(int p=pos[mn[l][r]];p<=r;p++)
					gl[0][l][r] = (gl[0][l][r] + 1ull * (h[p+1][r]+1) * g[0][l][p]) % mod;
				for(int p=l;p<=pos[mn[l][r]];p++)
					gr[0][l][r] = (gr[0][l][r] + 1ull * (h[l][p-1]+1) * g[0][p][r]) % mod;
			}

			{
				bool o=0;
				int v1=pos[mx2[l][r]], v2=pos[mx[l][r]]; if(v1>v2) swap(v1,v2),o^=1;
				// calc g
				if(!o){
					for(int q=v1+1;q<=v2;q++)
						g[1][l][r]=(g[1][l][r]+1ull*gl[1][l][q-1]*(ff[q][r]+(q==r)))%mod;
				}else{
					for(int p=v1;p<v2;p++)
						g[1][l][r]=(g[1][l][r]+1ull*(ff[l][p]+(l==p))*gr[1][p+1][r])%mod;
				}
				for(int p=pos[mx[l][r]];p<=r;p++)
					gl[1][l][r] = (gl[1][l][r] + 1ull * (h[p+1][r]+1) * g[1][l][p]) % mod;
				for(int p=l;p<=pos[mx[l][r]];p++)
					gr[1][l][r] = (gr[1][l][r] + 1ull * (h[l][p-1]+1) * g[1][p][r]) % mod;
			}
		}
	printf("%d\n", (h[1][n]+1)%mod);
}
int main(){
	#ifdef LOCAL
		assert(freopen("input.txt","r",stdin));
		assert(freopen("output.txt","w",stdout));
	#endif
	ll T=1;
	// math_init();
	// NTT::init();
	while(T--) procedure();
	return 0;
}