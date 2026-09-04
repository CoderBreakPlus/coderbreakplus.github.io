// created time: 2026-09-04 07:48:23
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
typedef long double db;
int n; ll t;
int a[100005],b[100005]; db p[100005];

db mx,ans;

namespace brute{
	db f[10000005],h[100005];
	struct Mat{
		db a[3][3];
		db* operator[](int x){ return a[x]; }
		const db* operator[](int x)const{ return a[x]; }
		Mat(){ memset(a,0,sizeof(a)); }
	}T;
	Mat operator* (const Mat &A, const Mat &B){
		Mat C;
		for(int i:{0,1,2})for(int j:{0,1,2})for(int k:{0,1,2})
			C[i][k]+=A[i][j]*B[j][k];
		return C;
	}

	int s[100005],sz;
	bool check(int i,int j,int k){
		return (h[j]-h[i])*(p[k]-p[j])>(h[k]-h[j])*(p[j]-p[i]);
	}

	void main(){
		for(int i=1;i<=n;i++) s[i]=i,h[i]=p[i]*a[i];
		sort(s+1,s+n+1,[](int x,int y){ return p[x]==p[y]?h[x]>h[y]:p[x]<p[y]; });
		sz=0;
		for(int i=1;i<=n;i++)
			if(p[s[i]]!=p[s[sz]]) s[++sz]=s[i];
		int tsz=sz; sz=0;
		for(int i=1;i<=tsz;i++){
			while(sz>=2 && !check(s[sz-1],s[sz],s[i])) --sz;
			s[++sz]=s[i];
		}

		f[0]=0;
		int w=1;
		for(ll i=1;i<=t;i++){
			// mx*(i-1)-f[i-1]
			double k=mx*(i-1)-f[i-1];
			while(w<sz&&(h[s[w+1]]-h[s[w]])/(p[s[w+1]]-p[s[w]])>=-k)++w;
			int j=s[w];
			f[i]=f[i-1]+p[j]*k+h[j];
			cout<<i<<" j="<<j<<" dp = "<<fixed<<setprecision(10)<<f[i]<<endl;
		}

		printf("%.10Lf\n",f[t]);
	}
}
void procedure(){
	scanf("%d%lld",&n,&t);
	for(int i=1;i<=n;i++){
		scanf("%d%d%Lf",&a[i],&b[i],&p[i]);
		chkmax(mx, p[i]*b[i]);
	}
	if(t<=1e7){
		brute::main();
		return;
	}

	for(int i=1;i<=n;i++){
		db exp=t-(1-pow(1-p[i],t))/p[i];
		chkmax(ans, exp*mx+a[i]*(1-pow(1-p[i],t)));
	}
	printf("%.10Lf\n",ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.ans","w",stdout));
	#endif
	ll T=1;
	// math_init();
	while(T--) procedure();
	return 0;
}