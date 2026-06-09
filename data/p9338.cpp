// created time: 2026-06-09 09:35:37
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
char s[2000005];
int c[2000005],tim[2000005];

int n,k;
ll dp[2000005]; int p[2000005];

struct Calc{
	int l,r; ll cur;
	Calc(){ l=r=cur=0; }
	void fuck_check(){
		int con=0;
		for(int i=l+1;i<=r;i++)con+=max(0,c[i]-l);
		if(cur!=con){
			cout<<"query "<<l<<" "<<r<<endl;
			cout<<con<<" and "<<cur<<endl;
			exit(0);
		}
	}
	void addr(){
		++r,cur+=max(0,c[r]-l);
		// fuck_check();
	}
	void delr(){
		cur-=max(0,c[r]-l),--r;
		// fuck_check();
	}
	void addl(){
		cur-=max(0,c[l+1]-l);
		l++;
		cur-=max(0,r-max(l+1,tim[l])+1);
		// fuck_check();
	}
	void dell(){
		cur+=max(0,r-max(l+1,tim[l])+1);
		l--;
		cur+=max(0,c[l+1]-l);
		// fuck_check();
	}
	ll calc(int ql,int qr){
		while(ql<l) dell(); while(qr>r) addr();
		while(ql>l) addl(); while(qr<r) delr();
		return cur;
	}
}A,B;

ll v;
inline void checkA(int i,int j){
	ll val=dp[i]+A.calc(i,j)+v;
	if(val<dp[j])dp[j]=val,p[j]=i;
}
inline void checkB(int i,int j){
	ll val=dp[i]+B.calc(i,j)+v;
	if(val<dp[j])dp[j]=val,p[j]=i;
}
void divide(int l,int r){
	if(l+1==r)return;
	int mid=(l+r)>>1;
	for(int i=p[l];i<=p[r];i++)checkA(i,mid);
	divide(l,mid);
	for(int i=l+1;i<=mid;i++)checkB(i,r);
	divide(mid,r);
}
pair<ll,int> solve(ll v){
	::v=v;
	dp[0]=p[0]=0;A=B=Calc();
	for(int i=1;i<=n;i++)dp[i]=1e18,p[i]=0;

	// for(int i=1;i<=n;i++){
	// 	for(int j=0;j<i;j++)checkA(j,i);
	// }
	checkA(0,n),divide(0,n);
	int cur=n,cnt=0;
	while(cur)cnt++,cur=p[cur];
	return {dp[n],cnt};
}
void procedure(){
	n=read(),k=read();
	scanf("%s",s+1); int tmp=0,tot=0;
	for(int i=1;i<=2*n;i++){
		s[i]-='A';
		if(!s[i])c[++tmp]=tot;
		tot+=s[i];
	}

	for(int i=0;i<=n;i++)tim[i]=n+1;
	for(int i=n;i>=1;i--)tim[c[i]]=i;
	for(int i=n-1;i>=0;i--)
		chkmin(tim[i],tim[i+1]);

	ll l=0,r=(ll)n*n;
	while(l+1<r){
		ll mid=(l+r+1)>>1;
		if(solve(mid).se>=k) l=mid;
		else r=mid;
	}
	if(l==r){
		printf("%lld\n",solve(l).fi-k*l);
	}else{
		printf("%lld\n",max(solve(l).fi-k*l,solve(r).fi-k*r));
	}
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