// created time: 2026-04-04 09:32:56
// J. Sum of max of iai
// https://qoj.ac/contest/3575/problem/17722
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
inline ll INV(ll x){ return qpow(x, mod-2); }

struct Mod
{
    ll m, p;
    void init(int pp) { m = ((__int128)1 << 64) / pp; p = pp; }
    ll operator ()(ll x)
    {
        return x - ((__int128(x) * m) >> 64) * p;
    }
} node;

int N,a[10005];
struct Frac{
	int x,y,c0;
	Frac(){ x=0,y=1,c0=0; }
	Frac(int X){ if(!X) x=1,y=1,c0=1; else x=X,y=1,c0=0; }
	Frac(int X,int Y,int C0){x=X,y=Y,c0=C0; }
	int val(){ if(c0) return 0; return 1ull*x*INV(y)%mod; }
}s, tot;

inline Frac operator* (const Frac &A,const Frac &B){
	return Frac(node(1ull*A.x*B.x),node(1ull*A.y*B.y),A.c0+B.c0);
}
inline Frac operator+ (const Frac &A,const Frac &B){
	return Frac(node(1ull*A.x*B.y+1ull*A.y*B.x),node(1ull*A.y*B.y),0);
}
inline Frac operator/ (const Frac &A,const Frac &B){
	return Frac(node(1ull*A.x*B.y),node(1ull*A.y*B.x),A.c0-B.c0);
}
vector<int>wait[10005];
inline int add(int x){ return x>=mod?x-mod:x; }

void procedure(){
	N=read(),mod=read();
	node.init(mod);
	s=1;
	for(int i=1;i<=N;i++){
		s=s*Frac((a[i]-(N-i)+mod)%mod);
	}
	for(int i=1;i<=N;i++){
		wait[i-1].pb(i);
	}
	for(int v=1,k=0;v<=N*N;v++,k=(k+1)%N){
		vector<int>tmp=wait[k];wait[k].clear();
		for(auto t: tmp) {
			s=s/Frac(add(a[t]-(N-t)+mod));
			a[t]++;
			s=s*Frac(add(a[t]-(N-t)+mod));
			if(a[t]<N) wait[(k+t)%N].pb(t);
		}
		int cf=(v==N*N?N*N:mod-1);
		Frac S = s * cf;
		if(!S.c0) tot=tot+S;
	}
	printf("%d\n", tot.val());
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