// created time: 2026-10-15 10:46:03
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
int mod;
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

namespace brute{
	int n;
	struct Mod
	{
	    ll m, p;
	    void init(int pp) { m = ((__int128)1 << 64) / pp; p = pp; }
	    ll operator ()(ll x)
	    {
	        return x - ((__int128(x) * m) >> 64) * p;
	    }
	} node;
	struct Mat{
		int a[505][505];
		Mat(){ memset(a,0,sizeof(a)); }
		int* operator[](int x){ return a[x]; }
		const int* operator[](int x)const{ return a[x]; }
		void print(){
			for(int i=0;i<n;i++){
				for(int j=0;j<n;j++)printf("%d ",a[i][j]);
				puts("");
			}
		}
	}E;
	Mat operator*(const Mat &A,const Mat &B){
		Mat C;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				for(int k=0;k<n;k++)
					C[i][k]=node(C[i][k]+(ull)A[i][j]*B[j][k]);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				C[i][j]=(C[i][j]%mod+mod)%mod;
		return C;
	}
	vector<int> factor(int p){
		vector<int> ret;
		for(int i=2;i*i<=p;i++){
			if(p%i==0){
				ret.pb(i);
				while(p%i==0)p/=i;
			}
		}
		if(p>1)ret.pb(p);
		return ret;
	}
	void solve(int N,int p){
		n=N,mod=p; node.init(mod);
		vector<int> tmp=factor(p-1);
		int g;
		for(g=2;;g++){
			bool flg=1;
			for(int x:tmp)if(qpow(g,(p-1)/x)==1){ flg=0;break; }
			if(flg)break;
		}
		int out=0;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++){
				E[i][j]=qpow(g,3*(i+n*j));
				if(i==j)addmod(out+=E[i][j]);
			}
		assert(out);
		int cf=g*INV(out)%mod;

		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)
				E[i][j]=(ull)cf*E[i][j]%mod;
		E.print();
		Mat E2=E*E; E2.print();
		Mat E3=E2*E; E3.print();

		vector<int>vec;
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)assert(0<=E[i][j]&&E[i][j]<mod),vec.pb(E[i][j]);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)assert(0<=E2[i][j]&&E2[i][j]<mod),vec.pb(E2[i][j]);
		for(int i=0;i<n;i++)
			for(int j=0;j<n;j++)assert(0<=E3[i][j]&&E3[i][j]<mod),vec.pb(E3[i][j]);
		sort(vec.begin(),vec.end());
		assert(unique(vec.begin(),vec.end()) == vec.end());
	}
	void main(){
		int n=read(),m=read();
		solve(n,m);
	}
}
void procedure(){
	brute::main();
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