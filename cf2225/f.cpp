// created time: 2026-04-25 10:18:34
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
#define popcnt __builtin_popcountll
inline ll read(){
	ll x=0, f=1; ll ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
mt19937_64 rnd(chrono::steady_clock::now().time_since_epoch().count());
ll rng(ll x,ll y){ return x+rnd()%(y-x+1); }
const ull mod = (ull)1e18+3;
ull base = rng(1e8,1e9), pw[1000005];

ll n,l,k;
char s[1000005];
ull hsh[1000005];

ull gethash(ll l,ll r){
	return (hsh[r]+(__int128)(mod-hsh[l-1])*pw[r-l+1])%mod;
}
bool comp(ll l1,ll r1,ll l2,ll r2){
	ll m1=r1-l1+1,m2=r2-l2+1,m=min(m1,m2);
	ll L=1,R=m,x=0;
	while(L<=R){
		ll mid=(L+R)>>1;
		if(gethash(l1,l1+mid-1)==gethash(l2,l2+mid-1)){
			x=mid;
			L=mid+1;
		}else R=mid-1;
	}
	return x==m?m1<m2:s[l1+x]<s[l2+x];
}
void procedure(){
	n=read(),l=read(),k=read();
	scanf("%s",s+1);
	if(l*k>n){
		puts("NO");
		return;
	}
	puts("YES");

	pw[0]=1;
	for(ll i=1;i<=n;i++)pw[i]=(__int128)pw[i-1]*base%mod;
	for(ll i=1;i<=n;i++)hsh[i]=((__int128)hsh[i-1]*base+s[i])%mod;

	ll yl=1,yr=0;
	for(ll i=1;i<=n;i++){
		if(k==1&&i!=1)continue;
		if(i-1<l&&i!=1)continue;
		ll res=k-(i-1)/l-1;
		res=max(res,0ll);
		ll xl=i,xr=n-res*l;
		if(xr-xl+1>=l && comp(yl,yr,xl,xr))yl=xl,yr=xr;
	}
	for(ll i=yl;i<=yr;i++)putchar(s[i]);
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