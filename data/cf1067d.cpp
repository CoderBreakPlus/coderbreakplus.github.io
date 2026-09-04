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
	}M,T[40];
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
		M[0][0]=0, M[0][1]=0, M[0][2]=1;
		f[0]=0;
		ll i=0;
		for(int w=1;w<=sz;w++){
			T[0][0][0]=1-p[s[w]],T[0][1][0]=p[s[w]]*mx,T[0][2][0]=h[s[w]];
			T[0][1][1]=1, T[0][2][1]=1;
			T[0][2][2]=1;
			for(int x=1;x<40;x++)T[x]=T[x-1]*T[x-1];

			db slope = (h[s[w+1]]-h[s[w]])/(p[s[w+1]]-p[s[w]]);

			for(int x=39;x>=0;x--)
				if(i+(1ll<<x)<=t){
					Mat tmp=M*T[x];
					db k=mx*(i+(1ull<<x))-tmp[0][0];
					if(w==sz||slope<-k){
						i+=(1ull<<x);
						M=tmp;
					}
				}
			Mat tmp=M;
			db k=mx*i-tmp[0][0];
			if(i<t && (w==sz||slope<-k)){
				i++;
				M=tmp*T[0];
			}
		}
		printf("%.10Lf\n",M[0][0]);
	}
}
void procedure(){
	scanf("%d%lld",&n,&t);
	for(int i=1;i<=n;i++){
		scanf("%d%d%Lf",&a[i],&b[i],&p[i]);
		chkmax(mx, p[i]*b[i]);
	}
	brute::main();
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