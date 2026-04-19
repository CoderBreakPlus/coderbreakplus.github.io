// created time: 2026-04-18 09:57:07
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

int n,v;
char s[250005],t[250005];

void procedure(){
	n=read();
	scanf("%s%s",s+1,t+1);
	v=read();

	set<int>s1, s2, t1, t2;

	int mn = n+1, mx = 0;
	int mn1 = n+1, mx1 = 0;

	int low1 = 0, low2 = 0;
	for(int i=1;i<=n;i++){
		if(s[i]=='2'){
			mn = min(mn, i);
			t1.emplace(i);
		}
		if(s[i]=='1'){
			mn1 = min(mn1, i);
			if(i>=v) s1.emplace(i);
			else low1 ++;
		}
	}

	int c=0;
	for(int i=1;i<=n;i++){
		if(t[i]=='2'){
			mx = max(mx, i);
			t2.emplace(i);
			c++;
		}
		if(t[i]=='1'){
			mx1 = max(mx1, i);
			if(i>=v) s2.emplace(i);
			else low2 ++;
			c++;
		}
	}
	// cout<<"c="<<c<<endl;
	if(c == 1 && mn1 < mx1){
		// cout<<mn1<<" < "<<mx1<<endl;
		puts("Yes");
		return;
	}
	if((mn < mx || (mn1 < mx1 && mx1 >= v)) && low2 <= 1){
		puts("Yes");
		return;
	}



	int pair = 0;
	for(auto x: s2){
		auto it = s1.upper_bound(x);
		if(it != s1.end()) s1.erase(it), pair ++;
	}

	int dou = 0;
	for(auto x: t2){
		auto it = t1.upper_bound(x);
		if(it != t1.end()) t1.erase(it), dou ++;
	}

	pair += min((int)s2.size() - pair, dou);

	if(low1 - pair <= 1){
		puts("Yes");
	}else puts("No");
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