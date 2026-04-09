// created time: 2026-04-09 07:39:44
// https://qoj.ac/contest/1924/problem/10115
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

ll n,m,k,vis[36];
int code(char ch){
	if(isdigit(ch))return ch-'0';
	else return ch-'A'+10;
}
void procedure(){
	n=read(),k=read(),m=read();
	for(int i=0;i<n;i++)vis[i]=1;
	while(m--){
		char ch=getchar();
		while(!(isdigit(ch)||('A'<=ch&&ch<='Z'))) ch=getchar();
		vis[code(ch)]=0;
		// cout<<"banned "<<ch<<endl;
	}
	int b=0;
	for(int i=0;i<n;i++)b+=vis[i];
	// cout<<"b="<<b<<endl;
	vector<char>ch;
	while(k){
		int x=k%b;
		for(int i=0;i<n;i++){
			if(vis[i]&&!x){
				if(i>=10) ch.pb(i-10+'A');else ch.pb(i+'0');
			}
			x-=vis[i];
		}
		k/=b;
	}
	reverse(ch.begin(),ch.end());
	for(auto x:ch)putchar(x);puts("");
	// cout<<"fine"<<endl;
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}