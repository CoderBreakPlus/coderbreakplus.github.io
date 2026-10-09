// created time: 2026-10-09 07:44:51
#pragma GCC optimize("Ofast","unroll-loops")
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
inline ull lg2(ull x){ return 63^__builtin_clzll(x); }
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

using ull = unsigned long long;

static inline ull mix(ull x) {
	x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
	x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
	x = x ^ (x >> 31);
	return x;
}

static inline ull next(ull &x) {
	return x = mix(x + 0x9e3779b97f4a7c15ull);
}

int q;
ull seed,lf[205],rh[205];
int id;

const int B=256;

struct Opt{
	int o; ull l,r,x;
	Opt(){ }
	Opt(int O,ull L,ull R,ull X){ o=O,l=L,r=R,x=X; }
};
struct Love{
	Opt T[B];
	int hd,sz;
	inline void ins(const Opt &x){
		T[(hd+sz)&(B-1)]=x;
		++sz;
		if(sz>B) sz--,hd=((hd+1)&(B-1));
	}
	inline ull qry(ull pos){
		ull L=0,R=-1;
		int w=0;
		for(int i=sz-1;i>=0;i--){
			auto [o,l,r,x]=T[(hd+i)&(B-1)];
			if(!(l<=pos&&pos<=r))continue;

			if(!o) chkmin(R,mix(x+pos));
			else chkmax(L,mix(x+pos));
			if(L>=R){ 
				return !o ? L : R;
			}
		}
		return L;
	}
}T[205];
int tid;
int getid(ull x){
	if(x<(1ull<<63)) return lg2(max(1ull,x));
	return 125-lg2(max(1ull,~x));
}
void procedure() {
	cin>>q>>seed;
	for(int i=0;i<63;i++){
		int w=i;
		lf[w]=w?rh[w-1]+1:0;
		rh[w]=lf[w]+(1ull<<max(1,i))-1;
	}
	for(int i=62;i>=0;i--){
		int w=125-i;
		lf[w]=rh[w-1]+1;
		rh[w]=lf[w]+(1ull<<max(1,i))-1;
	}

	while(q--){
		ull op=min(2ull,next(seed)&3ull);
		if(op<=1){
			ull l=next(seed),r=next(seed),x=next(seed);
			if(l>r) swap(l,r);
			int bl=getid(l),br=getid(r);
			if(bl==br){
				T[bl].ins(Opt(op,l,r,x));
			}else{
				T[bl].ins(Opt(op,l,rh[bl],x));
				for(int i=bl+1;i<br;i++)
					T[i].ins(Opt(op,lf[i],rh[i],x));
				T[br].ins(Opt(op,lf[br],r,x));
			}
		}else{
			ull p=next(seed);
			seed^=T[getid(p)].qry(p);
		}
	}
	cout<<seed<<"\n";
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	cin.tie(nullptr) -> sync_with_stdio(false);
	ll T=1;
	while(T--) procedure();
	return 0;
}