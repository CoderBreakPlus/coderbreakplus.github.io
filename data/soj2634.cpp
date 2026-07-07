// created time: 2026-07-07 08:10:26
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

int n, T[8], a[1<<21], b[1<<21], c[1<<21];

const int L=3;
struct Poly{
	int a[L];
	int& operator [](int i) { return a[i]; }
	Poly(){ memset(a,0,sizeof(a)); }
	Poly(vector<int> b){
		b.resize(L);
		for(int i=0; i<L; i++) addmod(a[i]=b[i]+mod);
	}
};
Poly operator+ (Poly A, Poly B){ for(int i=0;i<L;i++) addmod(A[i]+=B[i]); return A; }
Poly operator- (Poly A, Poly B){ for(int i=0;i<L;i++) addmod(A[i]+=mod-B[i]); return A; }
Poly operator* (Poly A, Poly B){
	Poly C;
	for(int i=0;i<L;i++)
		for(int j=0;i+j<L;j++) C[i+j]=(C[i+j]+(ull)A[i]*B[j])%mod;
	return C;
}

void extract(int M[2][2],int *u,int *v){
	u[0]=M[0][0],u[1]=M[1][0];
	v[0]=M[0][0],v[1]=M[0][1];
	// if(M[0][0]||M[1][0]){
	// 	u[0]=M[0][0],u[1]=M[1][0];
	// 	if(M[0][0]||M[0][1]) 
	// 		v[0]=M[0][0],v[1]=M[0][1];
	// 	else
	// 		v[0]=M[1][0],v[1]=M[1][1];
	// }else{
	// 	u[0]=M[0][1],u[1]=M[1][1];
	// 	v[0]=0,v[1]=1;
	// }
}
bool equality(int a,int b,int p,int c,int d,int q,int &x,int &y){
	int det=((ull)a*d+(ull)(mod-b)*c)%mod; det=INV(det);
	if(!det) return 0;
	int A=((ull)p*d+(ull)(mod-b)*q)%mod;
	int B=((ull)a*q+(ull)(mod-p)*c)%mod;
	x=(ull)A*det%mod, y=(ull)B*det%mod;
	return 1;
}
void solve(int U[2][2],int V[2][2],vector<int>D,int &x,int &y){
	int cf[4][2];
	for(int i=0;i<4;i++)for(int j:{0,1})
		cf[i][j]=(ull)U[j][i>>1]*V[j][i&1]%mod;

	for(int i=0;i<4;i++)
		for(int j=i+1;j<4;j++)
			if(equality(cf[i][0],cf[i][1],D[i],cf[j][0],cf[j][1],D[j],x,y)) return;
}
void fwt(int *a,int M[2][2]){
	for(int m=1;m<(1<<n);m<<=1)
		for(int i=0;i<(1<<n);i+=(m<<1))
			for(int j=0;j<m;j++){
				int p=a[i+j], q=a[i+m+j];
				a[i+j] = ((ull)M[0][0]*p + (ull)M[0][1]*q) % mod;
				a[i+m+j] = ((ull)M[1][0]*p + (ull)M[1][1]*q) % mod;
			}
}
void procedure(){
	n=read();
	for(int i=0;i<8;i++) T[i]=read();

	int M[2][2][2] = {{{T[0],T[2]},{T[4],T[6]}},{{T[1],T[3]},{T[5],T[7]}}};
	int U[2][2], V[2][2], W[2][2];

	Poly R = Poly({M[0][0][0],-M[1][0][0]})*Poly({M[0][1][1],-M[1][1][1]})
			-Poly({M[0][0][1],-M[1][0][1]})*Poly({M[0][1][0],-M[1][1][0]});

	int A = R[2], B = R[1], C = R[0];
	int Ms[2][2][2];

	if(A){
		int delta = qpow(((ull)B*B+(ull)(mod-A)*C*4)%mod,(mod+1)/4);
		int iv = INV(2*A);
		int x[2]={(ull)(2*mod-B-delta)*iv%mod,(ull)(mod-B+delta)*iv%mod};
		for(int o:{0,1})for(int i:{0,1})for(int j:{0,1})
			Ms[o][i][j]=(M[0][i][j]+(ull)(mod-M[1][i][j])*x[o])%mod;
	}else{
		int x = (ull)(mod-C)*INV(B)%mod;
		for(int i:{0,1})for(int j:{0,1}){
			Ms[0][i][j]=(M[0][i][j]+(ull)(mod-M[1][i][j])*x)%mod;
			Ms[1][i][j]=M[1][i][j];
		}
	}

	for(int o:{0,1}) extract(Ms[o],U[o],V[o]);

	solve(U,V,{T[0],T[2],T[4],T[6]},W[0][0],W[0][1]);
	solve(U,V,{T[1],T[3],T[5],T[7]},W[1][0],W[1][1]);

	for(int i=0;i<(1<<n);i++) a[i]=read();
	for(int i=0;i<(1<<n);i++) b[i]=read();
	fwt(a,U), fwt(b,V);
	for(int i=0;i<(1<<n);i++) c[i]=(ull)a[i]*b[i]%mod;
	fwt(c,W);
	
	for(int i=0;i<(1<<n);i++) printf("%d ",c[i]);
	puts("");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	procedure();
	return 0;
}