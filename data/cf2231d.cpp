// created time: 2026-06-04 15:46:50
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

char s[200005];
ll n,a[200005],b[200005],c[200005],pos[200005],t;
void procedure(){
	n=read();
	scanf("%s",s+1);
	for(int i=1;i<=n;i++)a[i]=read();

	t=0;
	c[0]=-1e18;
	for(int i=1;i<=n;i++){
		c[i]=read();
		if(c[i]!=c[i-1]){
			pos[++t]=i;
		}
	}
	pos[t+1]=n+1;

	for(int i=1;i<=t;i++){
		int l=pos[i], r=pos[i+1]-1;
		// filling to keep 
		// cout<<l<<" "<<r<<endl;
		if(r==n || s[r+1]=='0'){
			for(int j=l;j<=r;j++){
				if(s[j]=='0'){
					if(j==l) a[j]=c[j]-b[j-1];
					else a[j]=-1e17-b[j-1];
				}
				b[j]=b[j-1]+a[j];
			}
		}else{
			int pos=-1; ll sum=0;
			for(int j=r+1;j>=l;j--){
				if(s[j]=='0'){
					pos=j;
					break;
				}
				sum+=a[j];
			}
			for(int j=l;j<=r;j++){
				if(s[j]=='0'){
					if(j==l) a[j]=c[j]-b[j-1];
					else{
						ll goal=-1e17;
						if(j==pos) goal=c[r+1]-sum;
						a[j]=goal-b[j-1];
					}
				}
				b[j]=b[j-1]+a[j];
			}
		}
	}
	// for(int i=1;i<=n;i++)cout<<a[i]<<" ";cout<<endl;
	ll mx=-2e18;
	for(int i=1;i<=n;i++){
		chkmax(mx,b[i]);
		if(mx!=c[i]){
			puts("No");
			return;
		}
	}
	puts("Yes");
	for(int i=1;i<=n;i++)printf("%lld ",a[i]);
	puts("");
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