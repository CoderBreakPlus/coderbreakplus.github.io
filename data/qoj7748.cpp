// created time: 2026-07-09
#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
typedef pair<ll,ll> Pr;
#define fi first
#define se second
#define mkp make_pair
#define pb emplace_back
// #define mid ((l+r)>>1)
#define popcnt __builtin_popcountll
const ll mod = 998244353;
inline ll read(){
	ll x=0, f=1; char ch=getchar();
	while(ch<'0' || ch>'9') { if(ch=='-') f=-1; ch=getchar(); }
	while(ch>='0' && ch<='9') x=x*10+ch-'0', ch=getchar();
	return x*f;
}
inline ll lg2(ll x){ return 63^__builtin_clzll(x); }
inline ll qpow(ll a,ll b){
	ll ans=1, base=a;
	while(b){
		if(b&1) ans=ans*base%mod;
		base=base*base%mod; b>>=1;
	}
	return ans;
}
void init(){ }
ll n,m,w[150005],qz[150005],z[150005],p[150005];
ll pre[150005], tr[150005], bor[150005];
ll ex[25][150005], zhy[150005];
char s[150005], t[150005];
ll query(ll l,ll r){
	ll p=lg2(r-l+1);
	return max(ex[p][l], ex[p][r-(1<<p)+1]);
}
void procedure(){
	n=read(), m=read();
	scanf("%s%s", s+1, t+1);
	for(ll i=1;i<=n;i++) w[i]=read(),qz[i]=qz[i-1]+w[i];
	z[1]=m;	
	ll zl = 0, zr = 0;
	for(ll i=2;i<=n;i++){
		if(i <= zr) z[i] = min(z[i-zl+1], zr-i+1);
		while(z[i] <= n-i && s[1+z[i]] == s[i+z[i]]) z[i]++;
		if(i+z[i]-1 > zr) zl = i, zr = i+z[i]-1;
	}
	zl = 0, zr = 0;
	for(ll i=1;i<=n;i++){
		if(i <= zr) p[i] = min(z[i-zl+1], zr-i+1);
		while(i+p[i] <= n && s[1+p[i]] == t[i+p[i]]) p[i]++;
		if(i+p[i]-1 > zr) zl = i, zr = i+p[i]-1;
	}

	// for(ll i=1;i<=n;i++){
	// 	cout<<p[i]<<" ";
	// }
	// cout<<endl;
	tr[1] = pre[1] = w[1];
	for(ll i=2;i<=n;i++){
		bor[i]=bor[i-1];
		while(bor[i] && s[bor[i]+1] != s[i]) bor[i]=bor[bor[i]];
		if(s[bor[i]+1] == s[i]) bor[i]++;
		tr[i] = tr[bor[i]] + w[i];
		pre[i] = pre[i-1] + tr[i];
	}
	for(ll i=1;i<=n;i++){
		ex[0][i] = i+p[i]-1;
		zhy[i] = zhy[i-1] + qz[p[i]];
	}
	for(ll i=1;i<=lg2(n);i++)
		for(ll j=1;j<=n-(1<<i)+1;j++)
			ex[i][j] = max(ex[i-1][j], ex[i-1][j+(1<<(i-1))]);
	for(ll i=1;i<=m;i++){
		ll l=read(), r=read();

		ll L=l, R=r, ans=l-1;
		while(L<=R){
			ll mid=(L+R)>>1;
			if(query(l,mid)<=r){
				ans=mid;
				L=mid+1;
			}else R=mid-1;
		}
		// cout<<"divide: "<<l<<"->"<<ans<<" and "<<ans+1<<"->"<<r<<endl;
		printf("%lld\n", zhy[ans] - zhy[l-1] + pre[r-ans]);
	}
}
int main(){
	#ifdef LOCAL
		assert(freopen("input.txt","r",stdin));
		assert(freopen("output.txt","w",stdout));
	#endif
	ll T=1;
	init();
	while(T--) procedure();
	return 0;
}
