// created time: 2026-09-07 15:21:33
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
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }
double p;
int n,T,jc[1005],jc2[1005],ans[1005];
char s[1005];

bool query(int l,int r){
	printf("Q ");
	for(int i=0;i<n;i++) putchar('0'+(l<=i&&i<=r));
	puts(""); fflush(stdout);

	#ifdef LOCAL
		for(int i=l;i<=r;i++)
			if(ans[i]) return 1;
		return 0;
	#endif

	char x[5];
	if(scanf("%s",x)==EOF) exit(0);
	return x[0]=='P';
}
void answer(){
	s[n]='\0';
	// cout<<"A "<<s<<endl;
	printf("A %s\n",s); fflush(stdout);
	char x[5];
	if(!(cin>>x)) exit(0);
	assert(x[0]=='C');
}
void procedure(){
	int i=0;
	for(int i=0;i<n;i++){
		s[i]='0';
		#ifdef LOCAL
			ans[i]=(1.0*rng(1,1000)/1000<=p);
		#endif
	}

	if(p==1){
		for(int i=0;i<n;i++) s[i]='1';
		answer(); return;
	}
	if(p==0){
		for(int i=0;i<n;i++) s[i]='0';
		answer(); return;
	}

	// for(int i=0;i<n;i++) cout<<ans[i]; cout<<endl;
	while(i<n){
		int res=jc2[n-i];
		if(!query(i,i+jc2[n-i]-1)){i+=jc2[n-i];continue;}

		while(res>1){
			if(!query(i,i+jc[res]-1)) i+=jc[res],res-=jc[res];
			else res=jc[res];
		}
		s[i]='1';
		i++;
	}
	answer();
}

double qz[1005];
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	scanf("%d%lf%d",&n,&p,&T);
	#define db long double
	for(int i=2;i<=n;i++){
		// cout<<"i="<<i<<endl;

		db cur=1;
		db ans=1e9;

		qz[0]=1;
		for(int j=1;j<=i;j++)qz[j]=qz[j-1]*(1-p);
		db pro=1-qz[i];


		for(int j=1;j<i;j++){
			if(fabs(1.9*(qz[j]-qz[i])-pro)<ans){
				ans=fabs(1.9*(qz[j]-qz[i])-pro);
				jc[i]=j;
			}
		}
	}
	// for(int i=2;i<=n;i++) cout<<jc[i]<<" "; cout<<endl;
	// exit(0);
	for(int i=1;i<=n;i++){
		db pro=1;

		db cur=1;
		db ans=1e9;
		for(int j=1;j<=i;j++){
			cur*=(1-p);
			if(fabs(2*cur-pro)<ans){
				ans=fabs(2*cur-pro);
				jc2[i]=j;
			}
		}
	}
	// math_init();
	while(T--) procedure();
	return 0;
}