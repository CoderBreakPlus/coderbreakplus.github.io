// created time: 2026-06-22 07:40:26
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

int n,m,a[500005],b[500005];
ull va[1000005],val[1000005],vb[1000005];
int ca[1000005],cb[1000005];

int lp[1000005],rp[1000005],dp[1000005];
bool check(int l,int r){
	// cout<<"check "<<l<<" "<<r<<endl;
	if(l==r)return 1;
	return (ca[l-1]==ca[l]||ca[r-1]==ca[r]);
}
void procedure(){
	n=read(),m=read();
	for(int i=1;i<=m;i++)va[i]=vb[i]=ca[i]=cb[i]=0;
	for(int i=1;i<=n;i++){
		a[i]=read(),b[i]=read();
		val[i]=rnd();
		va[a[i]]^=val[i],ca[a[i]]++;
		vb[b[i]]^=val[i],cb[b[i]]++;
	}
	for(int i=1;i<=n;i++)
		if(!vb[a[i]]){ puts("NO"); return; }
	
	for(int i=1;i<=m;i++)va[i]^=va[i-1],vb[i]^=vb[i-1],ca[i]+=ca[i-1],cb[i]+=cb[i-1];
	for(int i=1;i<=m;i++)vb[i]^=va[i];

	int l=1;
	while(l<=m){
		while(l<=m&&cb[l]==cb[l-1]) l++;
		if(l>m)break;
		int r=l; while(r<m&&cb[r+1]!=cb[r]) r++;

		// cout<<l<<"->"<<r<<endl;
		if(vb[r]^vb[l-1]){
			puts("NO");
			return;
		}
		if(ca[r]-ca[l-1]!=cb[r]-cb[l-1]){
			puts("NO");
			return;
		}

		map<ull,int>mp;

		if(cb[r]-cb[l-1]==r-l+1){
			int lst=l;
			dp[l-1]=1;
			for(int i=l;i<=r;i++){
				dp[i]=0;
				if(vb[i]==vb[i-1])dp[i]=dp[i-1];

				if(ca[i-1]==ca[i]){
					dp[i]|=!!mp[vb[i]];
					if(dp[i-1]) mp[vb[i-1]]|=1;
				}else{
					dp[i]|=mp[vb[i]]&1;
					if(dp[i-1]) mp[vb[i-1]]|=2;
				}
				// for(int j=l;j<=i;j++){
				// 	if(vb[i]^vb[j-1])continue;
				// 	dp[i]|=(dp[j-1]&check(j,i));
				// }
			}
			if(!dp[r]){
				puts("NO");
				return;
			}
		}
		l=r+1;
	}
	puts("YES");
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