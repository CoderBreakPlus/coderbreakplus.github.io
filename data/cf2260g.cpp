// created time: 2026-09-09 10:02:11
#include<bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/hash_policy.hpp>
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
const int N = 200000;
int fac[N+5],inv[N+5];
void math_init(){
	fac[0]=inv[0]=1;
	for(int i=1;i<=N;i++) fac[i]=1ll*fac[i-1]*i%mod;
	inv[N]=qpow(fac[N],mod-2);
	for(int i=N-1;i>=1;i--) inv[i]=1ll*inv[i+1]*(i+1)%mod;
}
inline int binom(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[y]%mod*inv[x-y]%mod;
}
inline int perm(int x,int y){
	if(x<0 || y<0 || x<y) return 0;
	return 1ll*fac[x]*inv[x-y]%mod;
}

int n,vis[N+5],pure[N+5],siz[N+5];
vector<int>fac1[N+5];
vector<int>fac2[N+5];

__gnu_pbds::gp_hash_table<ll,int>mp;

int cf[10000005],val[10000005],luvf;
ll rl[10000005];

void procedure(){
	n=read();
	if(n==1){ puts("1"); return; }
	int ans = 1, tot = 0;

	for(int w=1;w<n;w++)
		for(auto x: fac2[w])for(auto y: fac2[w+1])if(x+y>2&&__gcd(x,y)==1){
			ll i=(ll)x*y;
			int id=mp[i];
			if(!id){
				cf[id=mp[i]=++luvf]=(((siz[x]+siz[y])&1)?1:mod-1);
				rl[luvf]=i,val[luvf]=1;
			}
			if(w%i==0||(w+1)%i==0) continue;
			if(__gcd((ll)w+1,i)==2) val[id]=499122178ull*val[id]%mod;
			else addmod(val[id]+=val[id]);
		}

	for(int i=1;i<=luvf;i++){
		addmod(ans+=mod-cf[i]);
		ans=(ans+(ull)cf[i]*val[i]%mod*perm(n,n/rl[i]))%mod;
	}
	printf("%d\n", ans);
}
int main(){
	#ifdef LOCAL
		assert(freopen("test.in","r",stdin));
		assert(freopen("test.out","w",stdout));
	#endif
	ll T=1;
	for(int i=2;i<=N;i++)if(!vis[i])
		for(int j=2*i;j<=N;j+=i)
			vis[j]=1;

	for(int i=1;i<=N;i++){
		pure[i]=1;
		for(int j:fac1[i]){
			if(j*j>i)break;
			if(j>1&&i%(j*j)==0){ pure[i]=0; break; }
		}
		for(int j=i;j<=N;j+=i)
			fac1[j].pb(i);
	}
	for(int i=1;i<=N;i++)if(pure[i]){
		// cout<<"go for "<<i<<endl;
		siz[i]=lg2((int)fac1[i].size());
		for(int j=i;j<=N;j+=i)
			fac2[j].pb(i);
	}
	math_init();
	while(T--) procedure();
	return 0;
}