// created time: 2026-09-17 11:28:21
#include"gap.h"
#include<bits/stdc++.h>
#ifdef LOCAL
#include"grader.cpp"
#endif
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

ll findGap(int T,int N){
	vector<ll>S;
	ll L=0,R=1e18;
	if(T==1){
		while(N>0){
			MinMax(L,R,&L,&R);
			S.pb(L),S.pb(R);
			L++,R--;
			N-=2;
		}
	}else{
		// cerr<<"sb"<<endl;
		MinMax(L,R,&L,&R); S={L,R};
		if(N>2){
			ll V=(R-L+N-2)/(N-1);
			L++,R--;
			while(L<=R){
				ll x,y;
				MinMax(L,min(L+V,R),&x,&y);
				if(~x) S.pb(x),S.pb(y);
				L=min(L+V,R)+1;
			}
		} 
	}
	sort(S.begin(),S.end());

	// for(int x: S) cerr<<x<<" "; cout<<endl;
	ll ans=0;
	for(int i=1;i<S.size();i++){
		chkmax(ans,S[i]-S[i-1]);
	}
	return ans;
}