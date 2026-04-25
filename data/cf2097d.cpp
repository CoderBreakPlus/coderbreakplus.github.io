// created time: 2026-04-24 19:36:59
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

int n,m;char s[1000005],t[1000005];

void procedure(){
	n=read(); 
	m=(n&-n); n/=m;
	swap(n,m);
	// cout<<"n="<<n<<" m="<<m<<endl;
	scanf("%s%s",s,t);
	vector<vector<int>>a(n,vector<int>(m)),b(n,vector<int>(m));
	for(int i=0;i<n*m;i++)a[i/m][i%m]=s[i]-'0',b[i/m][i%m]=t[i]-'0';

	// cout<<"done"<<endl;
	int p=0;
	for(int i=0;i<m;i++){
		int q=p;
		while(q<n&&!a[q][i])q++;
		// cout<<"q="<<q<<endl;
		if(q>=n)continue;
		if(p!=q)swap(a[p],a[q]);
		for(int j=0;j<n;j++)
			if(j!=p&&a[j][i])for(int k=i;k<m;k++)a[j][k]^=a[p][k];
		p++;
	}
	// cout<<"done2"<<endl;
	p=0;
	for(int i=0;i<m;i++){
		int q=p;
		while(q<n&&!b[q][i])q++;
		if(q>=n)continue;
		if(p!=q)swap(b[p],b[q]);
		for(int j=0;j<n;j++)
			if(j!=p&&b[j][i])for(int k=i;k<m;k++)b[j][k]^=b[p][k];
		p++;
	}
	for(int i=0;i<n;i++)
		for(int j=0;j<m;j++)if(a[i][j]!=b[i][j]){puts("No");return;}
	puts("Yes");
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