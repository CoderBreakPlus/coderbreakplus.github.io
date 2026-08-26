// created time: 2026-08-26 11:20:42
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

struct Frac{
	ull x,y;
	Frac(ull w=0){ x=w,y=1; }
	Frac(ull X,ull Y){
		ull D=__gcd(X,Y);
		x=X/D,y=Y/D;
	}
};

inline Frac& operator+= (Frac &A, const Frac &B){ return A=Frac(A.x*B.y+A.y*B.x,A.y*B.y); }
inline Frac operator+ (Frac A, const Frac &B){ return A+=B; }
inline Frac& operator-= (Frac &A, const Frac &B){ return A=Frac(A.x*B.y-A.y*B.x,A.y*B.y); }
inline Frac operator- (Frac A, const Frac &B){ return A-=B; }
inline Frac& operator*= (Frac &A, const Frac &B){ return A=Frac(A.x*B.x,A.y*B.y); }
inline Frac operator* (Frac A, const Frac &B){ return A*=B; }

int n,m,a[30],b[30],e[1<<8];
ull f[1<<8][30],h[1<<8][30],g[10][1<<8][30],C[30][30];

Frac ex[30];
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++){
		a[i]=read()-1,b[i]=read()-1;
		e[(1<<a[i])|(1<<b[i])]++;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<(1<<n);j++)
			if((j>>i)&1)e[j]+=e[j^(1<<i)];

	for(int i=1;i<(1<<n);i++){
		for(int x=0;x<=e[i];x++)f[i][x]=h[i][x]=C[e[i]][x];

		int x=__builtin_ctz(i),res=i^(1<<x);
		for(int j=res;j;j=(j-1)&res)
			for(int p=0;p<=e[j];p++)
			for(int q=0;q<=e[i^j];q++)
				f[i][p+q]-=h[j][p]*f[i^j][q];

		// cout<<"i="<<i<<endl;
		// for(int x=0;x<=e[i];x++){
		// 	if(f[i][x]) cout<<x<<" f="<<f[i][x]<<endl;
		// }
	}
	g[0][0][0]=1;
	for(int i=1;i<=n;i++)
		for(int j=1;j<(1<<n);j++)for(int k=0;k<=e[j];k++){
			int x=__builtin_ctz(j),res=j^(1<<x);
			for(int s=res;;s=(s-1)&res){
				for(int p=0;p<=min(k,e[s]);p++)
					g[i][j][k]+=g[i-1][s][p]*f[j^s][k-p];
				if(!s)break;
			}
		}

	for(int i=0;i<=m;i++){
		// cout<<"e="<<i<<endl;
		for(int j=1;j<=n;j++){
			ex[i]+=Frac(j*g[j][(1<<n)-1][i],C[m][i]);
			// cout<<"add "<<j*g[j][(1<<n)-1][i]<<" / "<<C[m][i]<<endl;
		}
	}

	Frac Ans;
	for(int i=0;i<=m;i++){
		Frac cf;
		if(i==m) cf=Frac(-(ull)m,m+1);
		else cf=Frac(1,m+1);
		Ans+=ex[i]*cf;
	}
	printf("%llu/%llu\n",Ans.x,Ans.y);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	for(int i=0;i<30;i++){
		C[i][0]=1;
		for(int j=1;j<=i;j++)
			C[i][j]=C[i-1][j]+C[i-1][j-1];
	}
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}