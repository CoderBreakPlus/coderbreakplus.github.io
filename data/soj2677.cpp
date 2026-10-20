// created time: 2026-10-20 15:23:32
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

string Alice(int n,int k,string s){
	int c[2]={0,0};
	for(int i=0;i<n;i++) c[s[i]-'0']++;
	int r=n;
	while(r>0 && min(c[0],c[1])>k)
		c[s[--r]-'0']--;

	static int stk[20000005],lost[20000005];

	int tp=0,tl=0;
	for(int i=0;i<r;i++){
		if(s[i]=='0')stk[++tp]=i;
		else if(tp){
			s[i]^=1;
			s[stk[tp--]]^=1;
		}else{
			lost[++tl]=i;
		}
	}
	reverse(lost+1,lost+tl+1);
	while(tp && tl) s[lost[tl--]]^=1, s[stk[tp--]]^=1;
	return s;
}
string Bob(int n,int k,string s){
	int c[2]={0,0};
	for(int i=0;i<n;i++) c[s[i]-'0']++;
	int r=n;
	while(r>0 && min(c[0],c[1])>k)
		c[s[--r]-'0']--;

	static int stk[20000005],lost[20000005];
	int tp=0,tl=0;
	for(int i=0;i<r;i++){
		if(s[i]=='1')stk[++tp]=i;
		else if(tp){
			s[i]^=1;
			s[stk[tp--]]^=1;
		}else{
			lost[++tl]=i;
		}
	}
	reverse(lost+1,lost+tl+1);
	while(tp && tl) s[lost[tl--]]^=1, s[stk[tp--]]^=1;
	return s;
}