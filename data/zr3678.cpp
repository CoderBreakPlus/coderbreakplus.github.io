// created time: 2026-11-03 09:30:04
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

int n,m;
bool vis[1<<20],f[1<<20];

bool check(int v0,int v1){
	// cout<<"check "<<v0<<","<<v1<<endl;
	// for(int i=0;i<(1<<m);i++)if(vis[i])
	// 	for(int j=0;j<(1<<m);j++)if(vis[j]){
	// 		int OR=i|j,AND=i&j;
	// 		// cout<<OR<<","<<AND<<endl;
	// 		if((OR&v0)==v0&&(AND&v1)==v1)return 1;
	// 	}
	// cout<<"v0="<<v0<<" v1="<<v1<<endl;
	for(int i=v1;i<(1<<m);i=((i+1)|v1)){
		// for(int j=0;j<(1<<m);j++)if(vis[j]){
		// 	int need=((~i)&v0)|v1;
		// 	if((need|j)==j)return 1;
		// }
		if(vis[i]&&f[(~i)&v0|v1])return 1;
	}
	return 0;
}
void procedure(){
	n=read(),m=read();
	memset(vis,0,sizeof(bool)<<m);
	for(int i=1;i<=n;i++)vis[read()]=1;
	int v0=0,v1=0,out=0;

	if(m==0){
		puts("0");
		return;
	}
	memcpy(f,vis,sizeof(bool)<<m);
	for(int i=0;i<m;i++)
		for(int j=0;j<(1<<m);j++)if((j>>i)&1)
			f[j^(1<<i)]|=f[j];

	int x=m-1;
	while(x>=0){
		int ans=x+1;
		for(int i=0;i<=x;i++){
			if(check(v0+(1<<x+1)-(1<<i),v1|(1<<i))){
				ans=i;
				break;
			}
		}
		for(int i=ans;i<=x;i++)out|=(1<<i);

		for(int i=ans+1;i<=x;i++)v0|=(1<<i);
		if(ans<=x)v1|=(1<<ans);

		x=ans-2;
	}
	printf("%d\n",out<<1);
}
int main(){
	assert(freopen("xor.in","r",stdin));
	assert(freopen("xor.out","w",stdout));
	ll T=read();
	// math_init();
	while(T--) procedure();
	return 0;
}