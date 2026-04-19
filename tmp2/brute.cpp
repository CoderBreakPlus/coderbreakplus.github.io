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
const int K = 8;

int f[1<<K][1<<K][K+1];


bool dfs(int a,int b,int z){

	// auto trans = [&](int a,int b,int z,int A,int B,int Z){
	// 	f[a][b][z] |= dfs(A,B,Z);
	// 	if(f[a][b][z]){
	// 		for(int i=0;i<n;i++)if((a>>i)&1)putchar(s[i]);else putchar('0'); putchar(' ');
	// 		for(int i=0;i<n;i++)if((b>>i)&1)putchar(t[i]);else putchar('0'); putchar(' ');
	// 		cout<<z<<" trans to ";
	// 		for(int i=0;i<n;i++)if((A>>i)&1)putchar(s[i]);else putchar('0'); putchar(' ');
	// 		for(int i=0;i<n;i++)if((B>>i)&1)putchar(t[i]);else putchar('0'); putchar(' ');
	// 		cout<<z<<endl;
	// 		return 1;
	// 	}
	// };
	if(~f[a][b][z]){
		return f[a][b][z];
	}
	if(!a || !b){
		// for(int i=0;i<n;i++)if((a>>i)&1)putchar(s[i]);else putchar('0'); putchar(' ');
		// for(int i=0;i<n;i++)if((b>>i)&1)putchar(t[i]);else putchar('0'); putchar(' ');
		// cout<<z<<endl;
		return 1;
	}
	if(__builtin_popcount(a)==1){
		if(z==n) return 1;
		// for(int i=0;i<n;i++)if((a>>i)&1)putchar(s[i]);else putchar('0'); putchar(' ');
		// for(int i=0;i<n;i++)if((b>>i)&1)putchar(t[i]);else putchar('0'); putchar(' ');
		// cout<<z<<endl;

		int p=lg2(a);
		if(s[p]==t[z] && p>z) return 1;
	}

	f[a][b][z]=0;
	if(z==n){ // a have to out
		for(int p=0;p<n;p++)if((a>>p)&1)
			for(int q=p+1;q<n;q++)if((b>>q)&1)
				if(s[p]==t[q] && (t[q]=='2' || q>=v)){
					f[a][b][z]|=dfs(a^(1<<p),b^(1<<q),q);
				}
		for(int p=0;p<n;p++)if((a>>p)&1)
			if(s[p]=='2' || p>=v){
				f[a][b][z]|=dfs(a^(1<<p),b,n);
			}
	}else{
		if(__builtin_popcount(b)==1) return 1;
		for(int p=z+1;p<n;p++)if(((a>>p)&1) && s[p]==t[z])
			for(int q=p+1;q<n;q++)if((b>>q)&1)
				if(s[p]==t[q] && (t[q]=='2' || q>=v)){
					f[a][b][z]|=dfs(a^(1<<p),b^(1<<q),q);
				}
		for(int p=z+1;p<n;p++)if(((a>>p)&1) && s[p]==t[z])
			if(s[p]=='2' || p>=v) f[a][b][z]|=dfs(a^(1<<p),b,n); // a out

		for(int q=0;q<n;q++)if((b>>q)&1)
			if(t[q]=='2' || q>=v) f[a][b][z]|=dfs(a,b^(1<<q),q);
	}
	// if(f[a][b][z]){
	// 	for(int i=0;i<n;i++)if((a>>i)&1)putchar(s[i]);else putchar('0'); putchar(' ');
	// 	for(int i=0;i<n;i++)if((b>>i)&1)putchar(t[i]);else putchar('0'); putchar(' ');
	// 	cout<<z<<endl;
	// }
	return f[a][b][z];
}
int calc(vector<int>vec){
	int s=0;for(auto x:vec)s|=(1<<x);
	return s;
}
void procedure(){
	memset(f,-1,sizeof(f));
	n=read();
	scanf("%s%s",s,t);
	v=read()-1;

	int ss=0,st=0;
	for(int i=0;i<n;i++){
		if(s[i]!='0')ss|=(1<<i);
	}
	for(int i=0;i<n;i++){
		if(t[i]!='0')st|=(1<<i);
	}
	puts(dfs(ss,st,n)?"Yes":"No");
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}