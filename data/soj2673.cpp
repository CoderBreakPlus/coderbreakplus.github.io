// created time: 2026-10-14 07:03:57
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
template<typename T>inline void addplus(T a,T b){ if((a+=b)>=mod)a-=mod; return a; }
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

int n,a[1<<20],b[1<<20],pop[1<<20],cf[21];
struct Pair{
	int a,b;
	Pair(){ a=b=0; }
	Pair(int A,int B){ a=A,b=B; }
}wa[1<<20], wb[1<<20];
Pair operator* (const Pair &A,const Pair &B){
	return Pair((ull)A.a*B.a%mod, ((ull)A.a*B.b+(ull)A.b*B.a)%mod);
}
Pair& operator+= (Pair &A,const Pair &B){ addmod(A.a+=B.a),addmod(A.b+=B.b); return A; }
Pair operator+ (Pair A,const Pair &B){ return A+=B; }

Pair& operator-= (Pair &A,const Pair &B){ addmod(A.a+=mod-B.a),addmod(A.b+=mod-B.b); return A;}
Pair operator- (Pair A,const Pair &B){ return A-=B; }

void fwt_bit(Pair *f,int m){
	m=(1<<m);
	for(int i=0;i<(1<<n);i+=(m<<1))
		for(int j=0;j<m;j++) f[i+m+j]+=f[i+j];
}
void add_bit(Pair *f,int m){
	m=(1<<m);
	for(int i=0;i<(1<<n);i+=(m<<1))
		for(int j=0;j<m;j++)
			f[i+m+j].b=(0ull+f[i+m+j].b+f[i+m+j].a+mod-f[i+j].a)%mod;
}
int v,tot[41][1<<20];

int poly[41][41],tmp[41];

void procedure(){
	n=read();
	for(int i=0;i<(1<<n);i++)a[i]=read(),pop[i]=__builtin_popcount(i);
	for(int i=0;i<(1<<n);i++)b[i]=read();
	int V=2*n;
	for(v=0;v<=V;v++){
		for(int i=0;i<=n;i++)cf[i]=qpow(v,i);
		for(int i=0;i<(1<<n);i++){
			wa[i]=Pair((ull)a[i]*cf[pop[i]]%mod,0);
			wb[i]=Pair((ull)b[i]*cf[pop[i]]%mod,0);
		}
		for(int i=0;i<n;i++)fwt_bit(wa,i),fwt_bit(wb,i);
		for(int i=1;i<n;i++){
			add_bit(wb,i-1);
			int m=1<<i;
			for(int j=0;j<(1<<n);j+=(m<<1))
				for(int k=0;k<m;k++){
					Pair t1=(wa[j+m+k]-wa[j+k]);
					Pair tmp=t1*wb[j+m+k];
					addmod(tot[v][j+m+k]+=tmp.b);
				}
		}
		for(int m=1;m<(1<<n);m<<=1)
			for(int i=0;i<(1<<n);i+=(m<<1))
			for(int j=0;j<m;j++)addmod(tot[v][i+m+j]+=mod-tot[v][i+j]);
	}
	for(int i=0;i<=V;i++){
		poly[i][0]=1;
		int prod=1;
		for(int j=0;j<=V;j++)if(j!=i){
			prod=(ull)prod*(i+mod-j)%mod;
			memcpy(tmp,poly[i],sizeof(tmp));
			for(int k=0;k<=V;k++)poly[i][k]=(ull)poly[i][k]*(mod-j)%mod;
			for(int k=0;k<V;k++)addmod(poly[i][k+1]+=tmp[k]);
		}
		prod=INV(prod);
		for(int k=0;k<=V;k++)
			poly[i][k]=(ull)poly[i][k]*prod%mod;
	}
	for(int i=0;i<(1<<n);i++){
		int out=0;
		for(int v=0;v<=V;v++)
			out=(out+(ull)tot[v][i]*poly[v][pop[i]])%mod;
		printf("%d ",out);
	}
	puts("");
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