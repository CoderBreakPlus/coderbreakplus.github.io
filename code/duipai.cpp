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

void procedure(){
	int T = 1000;
	for(int t=1;t<=T;t++){
		system("./gen");
		system("./brute");
		system("./cf1181e2");
		if(!system("diff -Zq test.out test.ans")){
			cout<<"AC"<<endl;
		}else{
			cout<<"WA"<<endl;
			exit(0);
		}

		// system("./gen");
		// if(system("./brute")){
		// 	cout<<"WA"<<endl;
		// 	exit(0);
		// }else
		// 	cout<<"AC"<<endl;
	}
}
int main(){
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}
