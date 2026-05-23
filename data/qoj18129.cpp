// created time: 2026-05-23 09:18:10
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef __int128 LL;
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

LL floor_sum(LL n, LL m, LL a, LL b) {
    LL ans = 0;
    while (true) {
        if (a >= m) { ans += n * (n - 1) / 2 * (a / m); a %= m; }
        if (b >= m) { ans += n * (b / m); b %= m; }
        LL ym = (a * n + b) / m;
        if (ym == 0) break;
        LL xm = ym * m - b;
        ans += (n - (xm + a - 1) / a) * ym;
        LL oa = a;
        b = (oa - xm % oa) % oa; a = m; m = oa; n = ym;
    }
    return ans;
}
LL n,m,a[35];
bool check(LL x){
	LL k=x/m;
	for(int i=0;i<n;i++)
		if(floor_sum(k,(LL)1<<i,m,x%m)<a[i])return 0;
	return 1;
}
void procedure(){
	n=read(),m=read();
	LL H=0;
	for(int i=0;i<n;i++){
		a[i]=read();
		H+=((LL)a[i]<<i);
	}
	if(!H){puts("0");return;}
	for(int i=n-2;i>=0;i--)
		a[i]+=2*a[i+1];

	LL l=m,r=m+H,ans=r;
	while(l<=r){
		LL mid=(l+r)>>1;
		if(check(mid)){
			ans=mid;
			r=mid-1;
		}else l=mid+1;
	}
	vector<char>ch;
	while(ans)ch.pb(ans%10+'0'),ans/=10;
	reverse(ch.begin(),ch.end());
	for(int x:ch) putchar(x);puts("");
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